cmd=build/demo/example1/a.out

top='((0,0,10), (0,0,0), (0,1,0))'
front='((0,-50,16), (0,0,20), (0,0,1))'

lc='(.4, .2, .1)'

cam="$front"
display=wxga

$cmd -a 90 \
     -c "$cam" \
     -d $display \
     -l "light((-3,-3,19), $lc)" \
     -l "light((-3,3,19), $lc)" \
     -l "light((3,-3,19), $lc)" \
     -l "light((3,3,19), $lc)" \
     -m 'sphere(2, (-10, 0, 5))' \
     -n 3 \
     -o output/tr.01.bmp \
     test_room
