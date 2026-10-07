FROM ubuntu:24.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       build-essential \
       valgrind \
       gdb \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work

CMD ["bash"]
