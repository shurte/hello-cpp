# Template for a c++ project

 - [Environment](#environment)
 - [VS Code](#vs-code)
 - [Make](#make)
 - [CMake](#cmake)
 - [Pure C++](#pure-c++)

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
    - [wxWidget](development/cpp/wxwidgets.md);
    - UWP;
    - C++ Builder;
    - imGui;
    - [SFML](#SFML);
    - SDL;
- Online compilers
    - [Wandbox](https://wandbox.org/)
    - [Compiler Explorer](https://godbolt.org/)
    - [Coliru](https://coliru.stacked-crooked.com/)
 
[Home](#template-for-a-c++-project)

## VS Code
### From scratch
- open a new folder as a new workspace
- create a `setup.bat` file to set the environment
    ```cmd
    set PATH=%PATH%;c:/_programs/msys64/ucrt64/bin
    :: here "c:/_programs/msys64/ucrt64/bin" is the folder that contains "g++.exe" to compile c++ files
    set PATH=%PATH%;c:/_programs/cmake-4.0.1-windows-x86_64/bin
    :: here "c:/_programs/cmake-4.0.1-windows-x86_64/bin" is the folder that contains "cmake" to use CMake in the workspace
    ```
- set some terminal settings in the workspace settings (CTRL + P -> type ">Preference ...")
    ```
    {
        "terminal.integrated.profiles.windows": {
            "Command Prompt: {
                "path": ["cmd"],
                "args": ["/K", "setup.bat"],
                // here "setup.bat" is the name of the *.bat-file that defines the environment for the workspace
                "icon": "terminal-cmd"
            }
        }
    }
    ```
- create a simple `main.cpp` file
    ```cpp
    #include <iostream>
    int main() {
        std::cout << "Hello" << '\n';
        return 0;
    }
    ```
- compile the `main.cpp` file and start the `main.exe` file from the terminal
    ```cmd
    g++ -g main.cpp -o main.exe
    :: "-g" is the option for gebugging
    main.exe
    :: Output : "Hello"
    ```
- create a simple `CMakeLists.txt` file
    ```cmake
    cmake_minimum_required(VERSION 4.0)
    project(Hello)
    file(GLOB SOURCES *.hpp *.cpp)
    # here "SOURCES" is a name for a CMake variable
    # it should be in capital letters because there are some issues if there are small and capital letters in the variable name
    add_executable(main ${SOURCES})
    # here "${SOURCES}" is just calling for the variable value
    ```
- compile the whole workspace with CMake
    ```cmd
    cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
    :: here "-S ." is the option that links to the current directory of the workspace where the sources of the project are located
    :: here "-B build" is the option that defines a directory where a CMake project will be created
    :: here '-G "MinGW Makefiles"' is the option that defines the sub-build system that will be used by CMake to build the project
    :: here '-DCMAKE_BUILD_TYPE=Debug' is the option that defines building in the debug mode (not release)
    ```
- add to the `settings.json` info about starting the application in the debug mode
    ```json
    "launch": {
        "version": "0.2.0",
        "configurations": [
            {
                "name": "My Debug",
                "type": "cppdbg",
                "request": "launch",
                "program": "${workspaceFolder}/main.exe",
                // here "${workspaceFolder}/main.exe" is the path to the file that should be started in the debug mode
                "MIMode": "gdb",
                "miDebuggerPath": "c:/_programs/mingw64/bin/gdb.exe",
                // here "c:/_programs/mingw64/bin/gdb.exe" is the path to the debugger executor
                "cwd": "${workspaceFolder}",
                "setupCommands": [
                    {
                        "description": "Enable pretty-printing for gdb",
                        "text": "-enable-pretty-printing",
                        "ignoreFailures": true
                    },
                    {
                     
                        "description": "Set Disassembly Flavor to Intel",
                        "text": "-gdb-set disassembly-flavor intel",
                        "ignoreFailures": true
                    }
                ]
            }
        ],
        "compounds": []
    }
    ```
- build the CMake project
    ```cmd
    cmake --build build
    :: here "--build" is the CMake option to start actually the build
    :: here "build" is the folder with the generated CMake project
    ```
- start the application from the command line:
    ```cmd
    build\main.exe
    ```
- start the application in the debug mode -> F5 (if you have correct defined the info about the debug mode in the `settings.json` file)
#### Options in settings.json 
- to define the path to a compiler
    ```json
    {
        "C_Cpp.default.compilerPath" : "<path to the compiler>" 
    }
    ```
- to define a start setup script
    ```json
    {
        "terminal.integrated.defaultProfile.windows": "Test Profile",
        "terminal.integrated.profiles.windows": {
            "Test Profile": {
                "path": [ "cmd" ],
                "args": [ "/K", "setup.bat" ]
                }
        }
    }
    ```
- to define a debug task 
    ```json
    "launch": {
        "version": "0.2.0",
        "configurations": [
            {
                "name": "My Debug",
                "type": "cppdbg",
                "request": "launch",
                "program": "${workspaceFolder}/main.exe",
                "MIMode": "gdb",
                "miDebuggerPath": "c:/_programs/mingw64/bin/gdb.exe",
                "cwd": "${workspaceFolder}",
                "setupCommands": [
                    {
                        "description": "Enable pretty-printing for gdb",
                        "text": "-enable-pretty-printing",
                        "ignoreFailures": true
                    },
                    {
                        "description": "Set Disassembly Flavor to Intel",
                        "text": "-gdb-set disassembly-flavor intel",
                        "ignoreFailures": true
                    }
                ]
            }
        ],
        "compounds": []
    }
    ```

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

## CMake
#### To define a default CMakeLists.txt
```
cmake_minimum_required(VERSION 3.22.0)
project(Hello VERSION 1.0.0 LANGUAGES CXX)
add_executable(main main.cpp)
```
#### To build:
```cmd
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. -G "MinGW Makefiles"
cmake --build .
main.exe
```
#### General workflow
1. Be sure that cmake is installed on your workstation:
```cmd
cmake --version
```
2. Go to the folder with cmake project. This folder should contain file CMakeLists.txt.
3. Create a folder where all of build files will be stored (for example 'build') (for Windows):
```cmd
mkdir build
```
4. Go to the folder:
```cmd
cd build
```
5. Run cmake command. This command creates a cmake build project according to the environment. In Windows and Linux build projects will look differently:
```
cmake ..
```
Two dots refer to the folder one level higher. In pur case this is the folder with cmake project.
6. Run cmake --build command for the current cmake build project:
```
cmake --build .
```
7. Run application:
```
Debug\\main.exe
```
##### How create a simple CMake project
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
##### How to add header file to CMake project
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
##### How to add source file to CMake project
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
## Pure C++
##### To create a simple .cpp main file:
```cpp
#include <iostream>

int main() {
    std::cout << "Hello." << '\n';
    return 0;
}
```

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
