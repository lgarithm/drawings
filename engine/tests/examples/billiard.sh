BUILD_DIR=build/$(uname -s)

cmd=$BUILD_DIR/bin/billiard_main

$cmd && mv output.bmp output/
