BUILD_DIR=build/$(uname -s)

cmd=$BUILD_DIR/bin/r2d2_main

cam='((-10,-35, 15), (0,0,0), (0,0,1))'
grey='(.7,.7,.7)'

view(){
    $cmd -c "$cam" \
    -d 4kf \
    -l "light((0,0,50), (.1,.1,.1))" \
    -l "light((-20,-20,20), $grey)" \
    -l "light((-20,20,20), $grey)" \
    -l "light((20,-20,20), $grey)" \
    -l "light((20,20,20), $grey)" \
    -n 6 \
    -o output/r2d2.$1.01.bmp $@
}
