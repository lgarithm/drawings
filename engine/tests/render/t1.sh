source tests/render/render-test.sh

top='((0,0,20), (0,0,0), (0,1,0))'
front='((0,-20,5), (0,0,0), (0,0,1))'
red='(1,0,0)'
green='(0,1,0)'
blue='(0,0,1)'
display=2048X2048

$cmd -c "$front" \
     -d $display \
     -m 'floor' \
     -m 'sphere(3, (-4,0,3))' \
     -m 'sphere(3, (4,0,3))' \
     -l "light((0,0,100), $red)" \
     -l "light((-10,-10,100), $green)" \
     -l "light((10,-10,100), $blue)" \
     -n 2 \
     -o output/1.bmp
