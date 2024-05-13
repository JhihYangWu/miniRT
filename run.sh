rm -rf build/
rm render.ppm
mkdir build/
cd build/
cmake ../
make
cd ../
./build/src/miniRT
open render.ppm
