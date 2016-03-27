cmd=build/demo/example1/a.out

front='((0,-20,5), (0,0,0), (0,0,1))'

$cmd -a 90 \
     -c "$front" \
     -d xga \
     -l 'light((0,0,50), (1,0,0))' \
     -l 'light((15,30,10), (.1,.8,0))' \
     -l 'light((-7,-5, 15), (0,.5,.2))' \
     -m 'floor' \
     -m 'plane((-10, 0, 5), (1, 0, 0))' \
     -m 'plane((20, 0, 0), (-1, 0, 0))' \
     -m "plane((0, 20, 0), (0,-1,0))" \
     -n 3 \
     -o output/example.bmp example_1
