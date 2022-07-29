# codewars-riscv64

An experiment to try to add RISCV64 support to Codewars

## Prerequisites

The container host must support [QEMU user-mode emulation](https://www.qemu.org/docs/master/user/main.html). Install the statically linked binaries for QEMU user-mode emulation **on the container host**, e.g. on Ubuntu 22.04:

```bash
$ sudo apt update && sudo apt install qemu-user-static
```

## Usage

```bash
$ ./bin/run
```

Specify a container engine (default: `docker`) with environment variable `CONTAINER_ENGINE`. E.g. with Podman:

```bash
$ CONTAINER_ENGINE=podman ./bin/run
```

Specify an example under the `examples/` directory to run (default: `multiply`) by passing a command-line argument. E.g. to run the example under `examples/multiply-failing/`:

```bash
$ ./bin/run multiply-failing
```

## Examples

- `multiply` (default): Example of `multiply` function with fixed and random tests
- `multiply-failing`: Like `multiply`, but with a failing implementation

## Building

```bash
$ docker build --platform linux/riscv64 -t ghcr.io/codewars/riscv64:latest .
```

## License

[MIT](./LICENSE)
