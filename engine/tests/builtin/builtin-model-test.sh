cmd=build/bin/builtin_main

cam='((0,-30,5), (0,0,0), (0,0,1))'
red='(.3, 0, 0)'
green='(0, .3, 0)'
blue='(0, 0, .3)'
grey='(.7, .7, .7)'
display=4kf

show_model(){
    $cmd -c "$cam" \
    -d $display \
    -l "light((0,0,50), (.1,.1,.1))" \
    -l "light((-20,-20,20), $red)" \
    -l "light((-20,20,20), $green)" \
    -l "light((20,-20,20), $blue)" \
    -l "light((20,20,20), $grey)" \
    -n 6 \
    -o output/m.$1.01.bmp \
    $@
}

view_model(){
    $cmd -a 60 \
    -c "$2(20)" \
    -d $display \
    -l "light((0,0,50), (.1,.1,.1))" \
    -l "light((-20,-20,20), $red)" \
    -l "light((-20,20,20), $green)" \
    -l "light((20,-20,20), $blue)" \
    -l "light((20,20,20), $grey)" \
    -l "light((-20,-20,-20), $red)" \
    -l "light((-20,20,-20), $green)" \
    -l "light((20,-20,-20), $blue)" \
    -l "light((20,20,-20), $grey)" \
    -m 'sphere(3, (-5, 5, 5))' \
    -n 6 \
    -o output/view.$1.$2.bmp \
    $1
}
