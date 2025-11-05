# VS Code

- [From scratch](#from-scratch)
- [Options in _settings.json_](#options-in-settingsjson)

[Home](../readme.md)

## From scratch
- open a new folder as a new workspace
- create a _setup.bat_ file to set the environment
    ```cmd
    set PATH=%PATH%;c:/_programs/mingw64/bin
    :: here "c:/_programs/mingw64/bin" is the folder that contains "g++.exe" to compile c++ files
    set PATH=%PATH%;c:/_programs/cmake-4.0.1-windows-x86_64/bin
    :: here "c:/_programs/cmake-4.0.1-windows-x86_64/bin" is the folder that contains "cmake" to use CMake in the workspace
    ```
- set some terminal settings in the workspace settings (CTRL + P -> type ">Preference ...")
    ```json
    {
        "terminal.integrated.profiles.windows": {
			  "Command Prompt": {
				"path": ["cmd"],
                "args": ["/K", "setup.bat"],
                "icon": "terminal-cmd"
            }
        }
    }
    ```
- create a simple _main.cpp_ file
    ```cpp
    #include <iostream>
    int main() {
        std::cout << "Hello" << '\n';
        return 0;
    }
    ```
- compile the _main.cpp_ file and start the _main.exe_ file from the terminal
    ```cmd
    g++ -g main.cpp -o main.exe
    :: "-g" is the option for gebugging
    main.exe
    :: Output : "Hello"
    ```
- create a simple _CMakeLists.txt_ file
    ```cmake
    cmake_minimum_required(VERSION 4.0)
    project(Hello)
    add_executable(main main.cpp)
    ```
- compile the whole workspace with CMake
    ```cmd
    cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
    :: here "-S ." is the option that links to the current directory of the workspace where the sources of the project are located
    :: here "-B build" is the option that defines a directory where a CMake project will be created
    :: here '-G "MinGW Makefiles"' is the option that defines the sub-build system that will be used by CMake to build the project
    :: here '-DCMAKE_BUILD_TYPE=Debug' is the option that defines building in the debug mode (not release)
    ```
- add to the _settings.json_ info about starting the application in the debug mode
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

[Back](#vs-code)

## Options in _settings.json_ 
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

[Back](#vs-code)
