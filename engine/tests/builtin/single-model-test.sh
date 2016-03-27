cmd=build/demo/builtin/builtin_examples_main.out

cam='((0,-30,5), (0,0,0), (0,0,1))'
red='(.5,0,0)'
green='(0,.5,0)'
blue='(0,0,.5)'
grey='(.7,.7,.7)'

show_model(){
    $cmd -c "$cam" \
         -d 2kf \
         -l "light((0,0,50), (.1,.1,.1))" \
         -l "light((-20,-20,20), $red)" \
         -l "light((-20,20,20), $green)" \
         -l "light((20,-20,20), $blue)" \
         -l "light((20,20,20), $grey)" \
         -n 1 \
         -o output/sm.$1.01.bmp \
         $@
}
