#!/bin/sh

set -e

BUILD_DIR=build/$(uname -s)

for t in $(find $BUILD_DIR/bin/*_test*); do
    echo $t
    $t
done
