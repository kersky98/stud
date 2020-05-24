#!/bin/sh
LANG=C
LANGUAGE=C

prj_name=decorator

BUILD_DIR=decorator_build

if [ $# = 1 ]; then
  if [ -d $BUILD_DIR ]; then
    rm -r -f $BUILD_DIR
    if [ ! -d $BUILD_DIR ]; then
      echo "[info] Cleaning previous object directory '$BUILD_DIR'"
    else
      echo "[info] Can't cleaning previous object directory '$BUILD_DIR'"
    fi
  fi
fi

mkdir -p $BUILD_DIR || exit 1

cd $BUILD_DIR || exit 1

cmake ../ -DCMAKE_BUILD_TYPE=Debug -G"Eclipse CDT4 - Unix Makefiles"

make || exit 1

date
