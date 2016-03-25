source tests/render/render-test.sh

cam='((0, -30, 0), (0,0,0), (0,0,1))'
lc='(.1, .1, .1)'

$cmd -c "$cam" \
     -d 2kf \
     -m 'sphere(4, (0,0,8)) @ dc(green), rf=0' \
     -m 'sphere(4, (-7,0,-2)) @ dc(blue)' \
     -m 'sphere(4, (7,0,-2)) @ rf=1' \
     -m 'plane((-10, 0, 0), (1, 0, 1))' \
     -m 'plane((0, 20, 0), (0, -1, 0)) @ dc(blue)' \
     -l "light((20,0,35), $lc)" \
     -l "light((30,0,30), $lc)" \
     -l "light((5, -10, 5), $lc)" \
     -n 6 \
     -o output/4.bmp
