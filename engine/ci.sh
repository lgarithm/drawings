#!/bin/sh

set -e

now(){ date +%s; }

main(){
    echo -e "\x1b[1;43mConfiguring\x1b[m"
    ./configure
    
    echo -e "\x1b[1;43mBuilding\x1b[m"
    make all
    
    echo -e "\x1b[1;43mRunning basic checks\x1b[m"
    make check
    
    echo -e "\x1b[1;43mRunning demos\x1b[m"
    ./tests/all-tests.sh
}

ci(){
    rm -fr build
    begin=$(now)
    date > ci-begin.log
    main
    date > ci-end.log
    end=$(now)
    duration=$((end - begin))
    
    echo -e "\x1b[1;42mTook ${duration}s\x1b[m"
    echo -e "\x1b[1;32mSUCCESS\x1b[m"
}

ci | tee ci.log
