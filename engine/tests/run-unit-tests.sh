#!/bin/sh

set -e

for t in $(find build/bin/*_test*); do
    echo $t
    $t
done
