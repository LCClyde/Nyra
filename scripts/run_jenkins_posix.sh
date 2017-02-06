#!/usr/bin/env bash

cd ${HOME}/Nyra
./scripts/install_deps_posix.sh > jenkins_deps.log
cmake . > jenkins_cmake.log
make > jenkins_make.log
ctest > jenkins_ctest.log

