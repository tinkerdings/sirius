@echo off

mkdir build
attrib +r build\*.gitignore
del /S /Q build\*
attrib -r build\*.gitignore
pushd build

cl -FC -Zi ..\win32_sirius.cpp user32.lib gdi32.lib

popd
