del bin\*.obj
del bin\test.exe
tcc -ml -nbin -etest.exe -Isrc src\test.c src\vec2.c src\mat3.c src\transf.c src\graphic.c src\image.c 

