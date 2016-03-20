source tests/builtin/builtin-model-test.sh

display=$medium
show_model test_plane_1
show_model test_plane_1 -m 'sphere(3,(0,0,4))' -o outupt/p-with-s.bmp
