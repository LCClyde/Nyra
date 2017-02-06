#!/usr/bin/env bash

cd ${HOME}/Nyra
./scripts/install_deps_posix.sh
cmake .
make
ctest

