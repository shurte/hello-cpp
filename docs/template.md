# Template for a c++ project

 - [Environment](#environment)
 - [Make](#make)
 - [CMake](#cmake)
 - [Pure C++](#pure-c)

[Home](readme.md)

## Environment
- PATH variable (for example, in setup.bat):
    ```cmd
    set PATH=%PATH%;c:/_programs/msys64/ucrt64/bin
    set PATH=%PATH%;c:/_programs/cmake-4.0.1-windows-x86_64/bin
    ```
- Commands to check
    ```cmd
    cmake --version
    g++ --version
    ```
- Compiler
    - MinGW - Minimalist GNU (GCC - GNU Compiler Collection) for Windows ?
        - [MinGW nuwen](https://nuwen.net/mingw.html)
- GUI frameworks to check
    - imGui;
    - [SFML](#SFML);
    - [SDL](#SDL);
- Online compilers
    - [Wandbox](https://wandbox.org/)
    - [Compiler Explorer](https://godbolt.org/)
    - [Coliru](https://coliru.stacked-crooked.com/)
 
[Home](#template-for-a-c-project)

## Make
- makefile
    ```make
    test:
        echo "test task"
    clean:
        cmd /c redir /q /s build
    all:
        cmd /c if exist build rmdir /q /s build
        cmd /c mkdir build
        g++ -O0 -g -std=c++20 -o build/main.exe *.cpp
    run:
        ./build/main.exe
    ```
- start from the command line:
    ```cmd
    make test clean all run
    ```

[Home](#template-for-a-c-project)

## CMake
### How create a simple CMake project
- Set BOOST_ROOT environment variable as directory with actual boost repository.
- Open the current project directory in VS Code.
- Create file _CMakeLists.txt_ in the project directory.
   - add section with boost library to the file;
   - add section with tests to the file;
- Create _tests_ directory in the project directory.
- Create file _CMakeLists.txt_ in the directory _tests_.
- Create file _stack_tests.cpp_ in the directory _tests_.
- Choose an active kit in VS Code (at the bottom of the IDE).
- Choose a target to build in VS Code (for example, _stack_test_ at the bottom of the IDE).
- Then you can build and run the unit tests.
### How to add header file to CMake project
- Add directory _inc_ to project directory;
- Add the following to _CMakeLists.txt_ in directory _tests_:
```cmd
target_include_directories(stack_test PUBLIC "${PROJECT_SOURCE_DIR}/inc")
```
- Add file _stack.h_ to directory _inc_;
- Add the following to file _stack_test.cpp_ in directory _tests_:
```cpp
#include "stack.h"
```
- Now you can add code to header _stack.h_ and use it in _stack_test.cpp_;
### How to add source file to CMake project
- Add directory _src_ to the project directory;
- Add file _CMakeLists.txt_ to the directory _src_;
- Add the following to _CMakeLists.txt_ in the project directory:
```cmake
add_subdirectory(src)
```
- Add file _stack.cpp_ to _src_;
- Add the following to _CMakeLists.txt_ in _src_:
```cmake
add_library(StackLib OBJECT "stack.cpp")
target_include_directories(StackLib PUBLIC "${PROJECT_SOURCE_DIR}/inc")
```
- After this you can add code to header and implementation file;
- Add the following to _CMakeLists.txt_ in _tests_:
```
target_link_libraries(stack_test StackLib)
```
- After this you can use source code in tests;

[Home](#template-for-a-c-project)

## Pure C++
### To create a simple .cpp main file:
```cpp
#include <iostream>

int main() {
    std::cout << "Hello." << '\n';
    return 0;
}
```

[Home](#template-for-a-c-project)

## SFML
- SFML uses MSVCRT;
- Use the MSVCRT version of [winlibs](https://winlibs.com/) (NOT UCRT);
- Compiling:
	```cmd
	set PATH=%PATH%;c:\_programs\mingw64\bin\
	g++ -Ilibs/sfml/include -o main main.cpp -Llibs/sfml/lib -lsfml-graphics -lsfml-system -lsfml-window
	```
- Hello World:
	```cpp
	#include <SFML\Graphics.hpp>
	#include <cassert>
	int main() {
	  sf::RenderWindow sfmlWin(sf::VideoMode(600, 360), "Hello World SFML Window");
	  sf::Font font;
	  //You need to pass the font file location
	  if (!font.loadFromFile("myfont.ttf")) {
	    return -1;
	  }
	  sf::Text message("Hello, World !", font);
	  while (sfmlWin.isOpen()) {
	    sf::Event e;
	    while (sfmlWin.pollEvent(e)) {
	      switch (e.type) {
	        case sf::Event::EventType::Closed:
	          sfmlWin.close();
	          break;
	        }
	      }
	      sfmlWin.clear();
	      sfmlWin.draw(message);
	      sfmlWin.display();
	  }
	  return 0;
	}
	```

[Home](#template-for-a-c-project)

## SDL
### Option 1
- Compiling
    ```cmd
    g++ -Ic:\_development\sandbox\cpp\sdl_example\lib\SDL\include\ main.cpp -o main.exe -Lc:\_development\sandbox\cpp\sdl_example\lib\SDL\lib -lSDL2
    ```
- Hello World
    ```cpp
    #include <iostream>
    #define SDL_MAIN_HANDLED
    #include "SDL2/SDL.h"
    int main(int argc, char ** argv) {
        try {
            SDL_Init(SDL_INIT_VIDEO);
            // Create an SDL Window
    		SDL_Window* Window = SDL_CreateWindow(
    			"Hello", // Window title
    			100,	// Top left x-coordinate of window
    			100,	// Top left y-coordinate of window
    			1024,	// Width of window
    			768,	// Height of window
    			0		// Flags (0 for no flags set)
    		);
    		
    		SDL_Event Event;
    		bool IsRunning = true;
    		
    		while (IsRunning) {
    			while (SDL_PollEvent(&Event)) {
    				switch (Event.type) {
    					// If we get an SDL_QUIT event, end loop
    					case SDL_QUIT:
    						IsRunning = false;
    						break;
    				}
    			}
    		}
    
            SDL_DestroyWindow(window);
            SDL_Quit();
    		return 0;
    	} catch (std::exception& Exception) {
    		std::cerr << "Exception:\n" << Exception.what() << "\n";
    	} catch (...) {
    		std::cerr << "An unknown exception appears.\n";
    	}
    }
    ```
### Option 2
- Compiling
    ```cmd
    g++ -Ic:\_development\sandbox\cpp\sdl_example\lib\SDL\include\ main.cpp -o main.exe -Lc:\_development\sandbox\cpp\sdl_example\lib\SDL\lib -lmingw32 -lSDL2main -lSDL2
    ```
- Hello World
    ```cpp
    #include <iostream>
    #include "SDL2/SDL.h"
    int main(int argc, char ** argv) {
        try {
            SDL_Init(SDL_INIT_VIDEO);
            // Create an SDL Window
    		SDL_Window* Window = SDL_CreateWindow(
    			"Hello", // Window title
    			100,	// Top left x-coordinate of window
    			100,	// Top left y-coordinate of window
    			1024,	// Width of window
    			768,	// Height of window
    			0		// Flags (0 for no flags set)
    		);
    		
    		SDL_Event Event;
    		bool IsRunning = true;
    		
    		while (IsRunning) {
    			while (SDL_PollEvent(&Event)) {
    				switch (Event.type) {
    					// If we get an SDL_QUIT event, end loop
    					case SDL_QUIT:
    						IsRunning = false;
    						break;
    				}
    			}
    		}
    
            SDL_DestroyWindow(window);
            SDL_Quit();
    		return 0;
    	} catch (std::exception& Exception) {
    		std::cerr << "Exception:\n" << Exception.what() << "\n";
    	} catch (...) {
    		std::cerr << "An unknown exception appears.\n";
    	}
    }
    ```

[Home](#template-for-a-c-project)
