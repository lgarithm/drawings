cmd=build/bin/example1_main

front='((0,-50,16), (0,0,20), (0,0,1))'
lc='(.4, .2, .1)'

$cmd -a 90 \
-c "$front" \
-d wxga \
-l "light((-3,-3,19), $lc)" \
-l "light((-3,3,19), $lc)" \
-l "light((3,-3,19), $lc)" \
-l "light((3,3,19), $lc)" \
-m 'sphere(2, (-10, 0, 5))' \
-n 3 \
-o output/tr.01.bmp \
test_room
