source tests/render/render-test.sh

top='((0,0,20), (0,0,0), (0,1,0))'
front='((0,-20,5), (0,0,0), (0,0,1))'
red='(1,0,0)'
green='(0,1,0)'
blue='(0,0,1)'
orange='(1,.5,0)'
display=2048X2048

$cmd -c "$front" \
     -d $display \
     -m 'sphere(4, (0,0,8))' \
     -m 'sphere(4, (-7,0,-2))' \
     -m 'sphere(4, (7,0,-2))' \
     -l "light((-20,0,35), $orange)" \
     -l "light((-30,0,30), $orange)" \
     -l "light((5, -10, 5), $orange)" \
     -n 6 \
     -o output/3.bmp
