#! /bin/bash

pushd $(dirname "${BASH_SOURCE[0]}")

zig cc --target=wasm32-wasi --sysroot ../deps/wasi-sysroot $@

popd