source tests/render/render-test.sh

$cmd -c "$front" \
     -d 2kf \
     -m 'floor' \
     -m 'sphere(3, (-4,0,3))' \
     -m 'sphere(3, (4,0,3))' \
     -l "light((0,0,100), $red)" \
     -l "light((-10,-10,100), $green)" \
     -l "light((10,-10,100), $blue)" \
     -n 2 \
     -o output/1.bmp
