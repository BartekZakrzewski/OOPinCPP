#include <string>
#include <utility>

class Song {
public:
  Song(std::string title, std::string author, int album) {
    title_ = title;
    author_ = author;
    album_ = album;
    id_ = ++count_;
  }
  Song(const Song &other) {
    title_ = other.title_;
    author_ = other.author_;
    album_ = other.album_;
    id_ = ++count_;
  }
  Song &operator=(const Song &) = default;
  virtual ~Song() { --count_; }
  static int count() { return count_; }

protected:
  std::string title_, author_;
  int album_, id_;

private:
  static int count_;
};

class Album {
public:
  Album(std::string title, std::string author)
      : title_(std::move(title)), author_(std::move(author)) {
    ++count_;
  }
  Album(const Album &other) : title_(other.title_), author_(other.author_) {
    ++count_;
  }
  Album &operator=(const Album &) = default;
  virtual ~Album() { --count_; }

protected:
  std::string title_, author_;

private:
  static int count_;
};
