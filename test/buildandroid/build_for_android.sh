#!/bin/bash
#ANDROID_NDK_HOME="/opt/Android/android-ndk-r16b"
ANDROID_NDK_HOME="/mnt/d/android-ndk-r20b"
mkdir -p android_build
rm -rf ./build
ln -s ./android_build ./build
cd android_build 
cmake .. \
	-DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
	-DANDROID_NDK=$ANDROID_NDK_HOME  \
	-DCMAKE_BUILD_TYPE=Release \
	-DANDROID_ABI="arm64-v8a" \
	-DANDROID_NATIVE_API_LEVEL=android-20 \
	-DANDROID_STL=c++_static
make
