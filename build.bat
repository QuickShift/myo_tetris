@echo off

set Defines=-DUSE_MYO=0

IF NOT EXIST build mkdir build
pushd build

del *.pdb > NUL 2> NUL

cl -nologo -Zi -FC /std:c++latest /I ..\ /I ..\include ..\*.cpp /Fe: myo_tetris ..\lib\SDL2main.lib ..\lib\SDL2.lib ..\lib\SDL2_image.lib ..\lib\SDL2_ttf.lib ..\lib\myo64.lib shcore.lib /link -incremental:no -opt:ref /SUBSYSTEM:CONSOLE

popd
