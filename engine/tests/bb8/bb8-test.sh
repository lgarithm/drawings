cmd=build/demo/bb8/a.out

top='((0,0,10), (0,0,0), (0,1,0))'
front='((0,-30,15), (0,0,0), (0,0,1))'
cam='((-10,-35, 15), (0,0,0), (0,0,1))'
red='(.5,0,0)'
green='(0,.5,0)'
blue='(0,0,.5)'
grey='(.7,.7,.7)'
display=4096X4096

view(){
    $cmd -c "$cam" \
         -d "$display" \
         -l "light((0,0,50), (.1,.1,.1))" \
         -l "light((-20,-20,20), $grey)" \
         -l "light((-20,20,20), $grey)" \
         -l "light((20,-20,20), $grey)" \
         -l "light((20,20,20), $grey)" \
         -n 6 \
         -o output/bb8.$1.01.bmp $@
}
