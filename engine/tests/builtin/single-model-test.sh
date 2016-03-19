cmd=build/demo/builtin/a.out

large=4096X4096
medium=2048X2048
small=1024X1024
cam='((0,-30,5), (0,0,0), (0,0,1))'
red='(.5,0,0)'
green='(0,.5,0)'
blue='(0,0,.5)'
grey='(.7,.7,.7)'
display=$medium

show_model(){
    $cmd -c "$cam" \
         -d "$display" \
         -l "light((0,0,50), (.1,.1,.1))" \
         -l "light((-20,-20,20), $red)" \
         -l "light((-20,20,20), $green)" \
         -l "light((20,-20,20), $blue)" \
         -l "light((20,20,20), $grey)" \
         -n 1 \
         -o output/sm.$1.01.bmp \
         $@
}
