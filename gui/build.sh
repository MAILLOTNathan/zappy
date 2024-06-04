cd ege
git pull
cd ..
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . $1