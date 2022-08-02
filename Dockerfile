FROM docker.io/library/ubuntu:22.04

RUN set -ex; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
        gcc \
        g++ \
        make \
        cmake \
        wget \
        ca-certificates \
    ; \
    apt-get autoremove -y; \
    apt-get clean; \
    rm -rf /var/lib/apt/lists/*;

RUN set -ex; \
    cd /tmp; \
    wget https://github.com/cgreen-devs/cgreen/archive/refs/tags/1.6.0.tar.gz; \
    tar xvf 1.6.0.tar.gz; \
    rm -vf 1.6.0.tar.gz; \
    cd cgreen-1.6.0; \
    make; \
    make install; \
    cd ..; \
    rm -rvf /tmp/cgreen-1.6.0;

ENV LD_LIBRARY_PATH=/usr/local/lib

RUN set -ex; \
    useradd -m codewarrior; \
    mkdir /workspace; \
    chown -R codewarrior: /workspace;
USER codewarrior
WORKDIR /workspace
