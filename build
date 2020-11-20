#! /bin/zsh

echo "building linux";
mkdir -p ./cmbuild;
cd ./cmbuild;
cmake ..;
make -j$(nproc);
cd ..;
echo "linux build done";
echo "building windows";
mkdir -p ./winbuild;
cd ./winbuild;
CFLAGS="-I/usr/local/x86_64-w64-mingw32/include" CXXFLAGS="-I/usr/local/x86_64-w64-mingw32/include" LDFLAGS="-L/usr/local/x86_64-w64-mingw32/lib" cmake -DCMAKE_TOOLCHAIN_FILE=../mingw.cmake -DWIN32=True -DXAUDIO2_FOUND=False ..;
make -j$(nproc);
cd ..;
echo "windows build done";
echo "all builds done";
