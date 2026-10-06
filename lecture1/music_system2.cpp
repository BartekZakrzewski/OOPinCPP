// music_library.cpp
// Build: g++ -std=c++17 -Wall -Wextra music_library.cpp -o music && ./music
//
// Domain model
//   Person  <|-- Author      (writes lyrics)
//   Person  <|-- Composer    (writes music)
//   Song    <|-- VocalSong   (has an Author)       Song  = abstract base
//   Song    <|-- Instrumental                      Song  --> Composer (shared,
//   association) Album   *--  Song                              Album owns its
//   songs (composition) Library<T>                                     generic
//   registry (template)

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

// ---------------------------------------------------------------
// Duration: small VALUE TYPE with operator overloading
// ---------------------------------------------------------------
class Duration {
public:
  explicit Duration(int seconds = 0) : seconds_(seconds) {
    if (seconds < 0)
      throw std::invalid_argument("Duration cannot be negative");
  }
  int seconds() const { return seconds_; }

  Duration operator+(const Duration &rhs) const {
    return Duration(seconds_ + rhs.seconds_);
  }
  Duration &operator+=(const Duration &rhs) {
    seconds_ += rhs.seconds_;
    return *this;
  }
  bool operator<(const Duration &rhs) const { return seconds_ < rhs.seconds_; }

  friend std::ostream &operator<<(std::ostream &os, const Duration &d) {
    return os << d.seconds_ / 60 << ':' << std::setw(2) << std::setfill('0')
              << d.seconds_ % 60 << std::setfill(' ');
  }

private:
  int seconds_;
};

// ---------------------------------------------------------------
// Person: BASE CLASS (protected data, virtual destructor, static counter)
// ---------------------------------------------------------------
class Person {
public:
  Person(std::string name, int birthYear)
      : id_(++nextId_), name_(std::move(name)), birthYear_(birthYear) {}
  virtual ~Person() = default; // polymorphic base -> virtual dtor

  int id() const { return id_; }
  const std::string &name() const { return name_; }
  int birthYear() const { return birthYear_; }

  virtual std::string role() const = 0; // pure virtual -> Person is abstract
  virtual void
  print(std::ostream &os) const { // overridable behavior with default
    os << name_ << " (b. " << birthYear_ << ", " << role() << ")";
  }

  static int totalPeople() { return nextId_; } // static member function

  friend std::ostream &operator<<(std::ostream &os, const Person &p) {
    p.print(os); // virtual call through operator<<
    return os;
  }

private:
  static int nextId_; // static data: shared by all Persons
  int id_;
  std::string name_;
  int birthYear_;
};
int Person::nextId_ = 0;

// ---------------------------------------------------------------
// Author / Composer: INHERITANCE + OVERRIDE
// ---------------------------------------------------------------
class Author final : public Person { // final: cannot be derived from
public:
  Author(std::string name, int birthYear, std::string language)
      : Person(std::move(name), birthYear), language_(std::move(language)) {}

  std::string role() const override { return "author"; }
  const std::string &language() const { return language_; }

private:
  std::string language_;
};

class Composer final : public Person {
public:
  Composer(std::string name, int birthYear, std::string genre)
      : Person(std::move(name), birthYear), genre_(std::move(genre)) {}

  std::string role() const override { return "composer"; }
  void print(std::ostream &os) const override { // extend base behavior
    Person::print(os);
    os << " [" << genre_ << "]";
  }

private:
  std::string genre_;
};

// ---------------------------------------------------------------
// Song: ABSTRACT BASE with ASSOCIATION (shared_ptr) to people
// ---------------------------------------------------------------
class Album; // forward declaration

class Song {
public:
  Song(std::string title, Duration length, std::shared_ptr<Composer> composer)
      : title_(std::move(title)), length_(length),
        composer_(std::move(composer)) {
    if (!composer_)
      throw std::invalid_argument("A song needs a composer");
  }
  virtual ~Song() = default;

  // Copying a song would duplicate its identity and album link -> forbid it.
  Song(const Song &) = delete;
  Song &operator=(const Song &) = delete;

  const std::string &title() const { return title_; }
  Duration length() const { return length_; }
  const Composer &composer() const { return *composer_; }
  const Album *album() const { return album_; } // non-owning back-pointer

  virtual std::string
  credits() const = 0; // each kind of song credits differently
  virtual std::unique_ptr<Song>
  clone() const = 0; // "virtual copy constructor" idiom

protected:
  std::string title_;
  Duration length_;
  std::shared_ptr<Composer> composer_; // shared: many songs, one composer

private:
  friend class Album; // Album may set album_, nobody else
  const Album *album_ = nullptr;
};

class VocalSong : public Song {
public:
  VocalSong(std::string title, Duration length,
            std::shared_ptr<Composer> composer, std::shared_ptr<Author> author)
      : Song(std::move(title), length, std::move(composer)),
        author_(std::move(author)) {
    if (!author_)
      throw std::invalid_argument("A vocal song needs an author");
  }
  std::string credits() const override {
    return "words: " + author_->name() + ", music: " + composer_->name();
  }
  std::unique_ptr<Song> clone() const override {
    return std::make_unique<VocalSong>(title_, length_, composer_, author_);
  }

private:
  std::shared_ptr<Author> author_;
};

class Instrumental : public Song {
public:
  using Song::Song; // inherit constructors
  std::string credits() const override { return "music: " + composer_->name(); }
  std::unique_ptr<Song> clone() const override {
    return std::make_unique<Instrumental>(title_, length_, composer_);
  }
};

// ---------------------------------------------------------------
// Album: COMPOSITION (owns songs), move-only, iterator-friendly
// ---------------------------------------------------------------
class Album {
public:
  Album(std::string title, int year) : title_(std::move(title)), year_(year) {}

  // Songs hold a pointer back to this Album, so an Album must keep its address:
  // copying and moving are both disabled.
  Album(const Album &) = delete;
  Album &operator=(const Album &) = delete;

  Album &addSong(std::unique_ptr<Song> song) { // takes ownership
    song->album_ = this; // allowed because Album is a friend of Song
    songs_.push_back(std::move(song));
    return *this; // returning *this enables chaining
  }

  const Song &operator[](std::size_t i) const { // subscript operator
    return *songs_.at(i); // .at() throws std::out_of_range
  }
  std::size_t size() const { return songs_.size(); }
  const std::string &title() const { return title_; }
  int year() const { return year_; }

  Duration totalLength() const {
    return std::accumulate(
        songs_.begin(), songs_.end(), Duration{},
        [](Duration acc, const auto &s) { return acc + s->length(); });
  }

  auto begin() const { return songs_.begin(); } // makes range-for work
  auto end() const { return songs_.end(); }

  friend std::ostream &operator<<(std::ostream &os, const Album &a) {
    os << a.title_ << " (" << a.year_ << ") - " << a.size() << " tracks, "
       << a.totalLength() << '\n';
    int n = 1;
    for (const auto &s : a)
      os << "  " << n++ << ". " << std::left << std::setw(18) << s->title()
         << std::right << s->length() << "  " << s->credits() << '\n';
    return os;
  }

private:
  std::string title_;
  int year_;
  std::vector<std::unique_ptr<Song>> songs_;
};

// ---------------------------------------------------------------
// Library<T>: CLASS TEMPLATE, a generic registry that finds by name
// ---------------------------------------------------------------
template <typename T> class Library {
public:
  std::shared_ptr<T> add(std::shared_ptr<T> item) {
    items_.push_back(item);
    return item;
  }
  template <typename Pred> // member template
  std::vector<std::shared_ptr<T>> findIf(Pred pred) const {
    std::vector<std::shared_ptr<T>> out;
    std::copy_if(items_.begin(), items_.end(), std::back_inserter(out),
                 [&](const auto &p) { return pred(*p); });
    return out;
  }
  std::size_t size() const { return items_.size(); }

private:
  std::vector<std::shared_ptr<T>> items_;
};

// ---------------------------------------------------------------
// main: put it all together
// ---------------------------------------------------------------
int main() {
  // People live in generic libraries; songs share them via shared_ptr.
  Library<Author> authors;
  Library<Composer> composers;

  auto lyricist = authors.add(
      std::make_shared<Author>("Agnieszka Osiecka", 1936, "Polish"));
  auto poet =
      authors.add(std::make_shared<Author>("Jonathan Reyes", 1984, "English"));
  auto classic = composers.add(
      std::make_shared<Composer>("Seweryn Krajewski", 1947, "rock"));
  auto electro = composers.add(
      std::make_shared<Composer>("Mira Lindqvist", 1990, "electronic"));

  // Album owns its songs; calls chain thanks to "return *this".
  Album album("Night Sessions", 2024);
  album
      .addSong(std::make_unique<VocalSong>("Low Light", Duration(215), classic,
                                           lyricist))
      .addSong(std::make_unique<VocalSong>("Paper Boats", Duration(187),
                                           electro, poet))
      .addSong(
          std::make_unique<Instrumental>("Interlude", Duration(95), electro))
      .addSong(std::make_unique<VocalSong>("Last Tram", Duration(243), classic,
                                           poet));

  std::cout << album << '\n';

  // Polymorphism: Person::print dispatches to Author / Composer overrides.
  std::cout << "People:\n";
  std::vector<const Person *> everyone = {lyricist.get(), poet.get(),
                                          classic.get(), electro.get()};
  for (const Person *p : everyone)
    std::cout << "  " << *p << '\n';

  // Template search with a lambda predicate.
  auto veterans =
      composers.findIf([](const Composer &c) { return c.birthYear() < 1960; });
  std::cout << "\nComposers born before 1960: ";
  for (const auto &c : veterans)
    std::cout << c->name() << ' ';
  std::cout << "\n";

  // Back-pointer (association) and the shared_ptr reference count.
  std::cout << "\n'" << album[2].title() << "' belongs to '"
            << album[2].album()->title() << "'\n";
  // use_count = this local variable + the Library + one per song that
  // references her
  std::cout << "Mira Lindqvist is used by " << electro.use_count() - 2
            << " songs\n";

  // Virtual copy constructor: clone a song through a base reference.
  auto copy = album[0].clone();
  std::cout << "Clone of '" << copy->title() << "' has album = "
            << (copy->album() ? "set" : "none (not yet added to an album)")
            << '\n';

  // Encapsulation + exceptions: invalid state is rejected at construction.
  try {
    Album other("Broken", 2025);
    other.addSong(
        std::make_unique<Instrumental>("Ghost", Duration(60), nullptr));
  } catch (const std::invalid_argument &e) {
    std::cout << "Rejected: " << e.what() << '\n';
  }
  try {
    (void)album[99];
  } catch (const std::out_of_range &) {
    std::cout << "Rejected: track 99 does not exist\n";
  }

  std::cout << "Total people created: " << Person::totalPeople() << '\n';

  // Person p("x", 1);      // error: Person is abstract
  // Album b = album;       // error: Album is non-copyable
  return 0;
}
