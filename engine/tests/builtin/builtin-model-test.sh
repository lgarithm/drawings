cmd=build/demo/builtin/builtin_examples_main.out

front='((0, -20, 0), (0, 0, 0), (0, 0, 1))'
back='((0, 20, 0), (0, 0, 0), (0, 0, 1))'
top='((0, 0, 20), (0, 0, 0), (0, 1, 0))'
bottom='((0, 0, -20), (0, 0, 0), (0, -1, 0))'

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
         -c "$3" \
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
