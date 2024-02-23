#!/bin/bash

case "$1" in
  debug)
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
    ;;
  release)
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    ;;
  build)
    cmake --build build
    ;;
  run)
    ./build/nopf-server
    ;;
  brun)
    cmake --build build && ./build/nopf-server
    ;;
  *)
    echo "Invalid option. Please use: debug, release, build, run, or brun."
    ;;
esac