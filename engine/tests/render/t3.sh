source tests/render/render-test.sh

$cmd -c "$front" \
     -d 2kf \
     -m 'sphere(4, (0,0,8))' \
     -m 'sphere(4, (-7,0,-2))' \
     -m 'sphere(4, (7,0,-2))' \
     -l "light((-20,0,35), $orange)" \
     -l "light((-30,0,30), $orange)" \
     -l "light((5, -10, 5), $orange)" \
     -n 6 \
     -o output/3.bmp
