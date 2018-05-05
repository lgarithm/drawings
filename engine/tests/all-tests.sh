set -ex
mkdir -p output
./tests/bb8/all.sh
./tests/r2d2/all.sh
./tests/builtin/all.sh
./tests/render/all.sh
./tests/examples/all.sh
