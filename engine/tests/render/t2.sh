source tests/render/render-test.sh

$cmd -c "$front" \
     -d 4kf \
     -m 'floor' \
     -m 'sphere(5, (-4,-5,5))' \
     -m 'sphere(3, (5,0,3))' \
     -l "light((0,0,50), (.6,.1,.1))" \
     -l "light((-10,-10,50), (.1,.6,.1))" \
     -l "light((10,-10,50), (.1,.1,.6))" \
     -n 6 \
     -o output/2.bmp
