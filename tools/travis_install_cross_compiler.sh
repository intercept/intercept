#!/bin/bash

# This is a script that builds a mingw cross compiler for compiling windows
# binaries on linux.
# It uses mxe to compile the latest mingw with gcc7.
# It also assumes that /opt is a directory that is cached by Travis so it
# checks if the cross compiler has been built previously and does nothing if
# it is already there.
# Note: You have to use the x86_64 compiler to generate 64-bit binaries and
# i686 for 32-bit binaries, otherwise it won't work.

CROSS_COMPILER_PATH=/opt/mxe/usr/bin
export PATH="$PATH:${CROSS_COMPILER_PATH}"

CROSS_COMPILER_PRESENT=true
for f in \
    "${CROSS_COMPILER_PATH}/i686-w64-mingw32.static.posix-cmake" \
    "${CROSS_COMPILER_PATH}/i686-w64-mingw32.static.posix-gcc" \
    "${CROSS_COMPILER_PATH}/i686-w64-mingw32.static.posix-g++" \
    "${CROSS_COMPILER_PATH}/x86_64-w64-mingw32.static.posix-cmake" \
    "${CROSS_COMPILER_PATH}/x86_64-w64-mingw32.static.posix-gcc" \
    "${CROSS_COMPILER_PATH}/x86_64-w64-mingw32.static.posix-g++"
do
    if [ ! -f "$f" ]
    then
        CROSS_COMPILER_PRESENT=false
    fi
done

if [ $CROSS_COMPILER_PRESENT == true ]
then
    echo "Cross-compiler found, continuing..."
    exit 0
fi

echo "###################################################################################################";
echo "No cross-compiler found in the cached directory. Building it using MXE. This will take a long time!";
echo "###################################################################################################";

rm -rf /opt/mxe
git clone https://github.com/overfl0/mxe /opt/mxe
cd /opt/mxe

echo "Building..."
make -j 3 MXE_PLUGIN_DIRS=plugins/gcc7 MXE_TARGETS='x86_64-w64-mingw32.static.posix i686-w64-mingw32.static.posix' gcc

ls -l /opt/mxe/usr/bin/
