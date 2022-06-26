#! /bin/bash

pushd $(dirname "${BASH_SOURCE[0]}")

clang --target=wasm32-unknown-wasi --sysroot ../deps/wasi-sysroot $@

popd