#! /bin/bash

set +ex

pushd linux
unzip ./*.zip
rm -f *.zip
popd

pushd osx
unzip ./*.zip
rm -f *.zip
popd

pushd windows
unzip ./*.zip
rm -f *.zip
popd