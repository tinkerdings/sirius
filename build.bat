@echo off

mkdir build
pushd build

cl -FC -Zi ..\perlin.cpp user32.lib gdi32.lib

popd
