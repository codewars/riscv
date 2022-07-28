FROM docker.io/library/ubuntu:jammy

RUN set -ex; \
    apt-get update; \
    apt-get install -y --no-install-recommends gcc g++ binutils make cmake \
      wget ca-certificates;

WORKDIR /tmp

RUN set -ex; \
    wget https://github.com/cgreen-devs/cgreen/archive/refs/tags/1.6.0.tar.gz; \
    tar xvf 1.6.0.tar.gz; \
    rm -vf 1.6.0.tar.gz; \
    cd cgreen-1.6.0; \
    make; \
    make install;

ENV LD_LIBRARY_PATH=/usr/local/lib

RUN set -ex; \
    useradd -m codewarrior; \
    mkdir /workspace; \
    chown -R codewarrior: /workspace;
USER codewarrior
WORKDIR /workspace
