FROM docker.io/library/ubuntu:22.04

RUN set -ex; \
    buildDeps='g++ make cmake wget ca-certificates'; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
        gcc \
        $buildDeps \
    ; \
    cd /tmp; \
    mkdir -p /tmp/cgreen; \
    wget https://github.com/cgreen-devs/cgreen/archive/refs/tags/1.6.0.tar.gz; \
    tar -xzf 1.6.0.tar.gz -C /tmp/cgreen --strip-components=1; \
    rm 1.6.0.tar.gz; \
    make -C /tmp/cgreen; \
    make -C /tmp/cgreen install; \
    apt-get purge -y --auto-remove $buildDeps; \
    apt-get clean; \
    rm -rf /var/lib/apt/lists/* /tmp/*;

ENV LD_LIBRARY_PATH=/usr/local/lib

RUN set -ex; \
    useradd -m codewarrior; \
    mkdir /workspace; \
    chown -R codewarrior: /workspace;
WORKDIR /workspace

# TODO Maintain reporter in a separate repo
COPY workspace/codewars_reporter.c .
COPY workspace/tests.c .

ENV QEMU_CPU=rv64,v=on,vext_spec=v1.0,zbkx=on,zk=on,zks=on

USER codewarrior
