
#### SDL path
```
SDL2_PATH = C:\_development\sandbox\cpp\libs\SDL2-2.32.8\x86_64-w64-mingw32
```

#### Build
```
g++ -I  C:\_development\sandbox\cpp\libs\SDL2-2.32.8\x86_64-w64-mingw32/include/SDL2/ -O0 -g -std=c++20 -o build/main.exe main.cpp -LC:\_development\sandbox\cpp\libs\SDL2-2.32.8\x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows
```