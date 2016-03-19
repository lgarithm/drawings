source tests/render/render-test.sh

top='((0,0,20), (0,0,0), (0,1,0))'
front='((0,-20,5), (0,0,0), (0,0,1))'
red='(1,0,0)'
green='(0,1,0)'
blue='(0,0,1)'
display=4096X4096

$cmd -c "$front" \
     -d $display \
     -m 'floor' \
     -m 'sphere(5, (-4,-5,5))' \
     -m 'sphere(3, (5,0,3))' \
     -l "light((0,0,50), (.6,.1,.1))" \
     -l "light((-10,-10,50), (.1,.6,.1))" \
     -l "light((10,-10,50), (.1,.1,.6))" \
     -n 6 \
     -o output/2.bmp
