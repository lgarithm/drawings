source tests/builtin/builtin-model-test.sh

display=2kf
show_model test_plane_1
show_model test_plane_1 -m 'sphere(3,(0,0,4))' -o output/p-with-s.bmp
