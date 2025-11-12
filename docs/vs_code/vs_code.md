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

### Properties
Properties for C++ (`/.vscode/c_cpp_properties.json`) :
```json
  {
    "env": {
      "myIncludePath": ["${workspaceFolder}/include", "${workspaceFolder}/src"],
      "myDefines": ["DEBUG", "MY_FEATURE=1"]
    },
    "configurations": [
      {
        "name": "Win32",
        "compilerPath": "c:/_programs/MinGW/bin/g++.exe",
        "intelliSenseMode": "gcc-x64",
        "includePath": ["${myIncludePath}", "c:/_programs/MinGW/include"],
        "defines": ["${myDefines}", "_WINDOWS"],
        "cStandard": "c17",
        "cppStandard": "c++20",
        "windowsSdkVersion": "10.0.19041.0",
        "browse": {
          "path": ["${myIncludePath}", "${workspaceFolder}"]
        }
      }
    ],
    "version": 4,
    "enableConfigurationSquiggles": true
  }
```


### Options
Options for VS Code (`/.vscode/settings.json`) :
```json
{
    "explorer.confirmDragAndDrop": false,
    "explorer.confirmDelete": false,
    "files.autoSave": "onFocusChange",
    "terminal.integrated.profiles.windows": {
        "terminal": {
            "path": "${env:windir}/System32/cmd.exe",
            "args": [
                "/k",
                "c:/_programs/MinGW/set_distro_paths.bat"
            ]
        }
    },
    "terminal.integrated.defaultProfile.windows": "terminal"
}
```

### Tasks

Configuration for building (`/.vscode/tasks.json`):  
```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "build",
            "command": "D:\\programms\\mingw64\\bin\\g++.exe",
            "args": [
                "-O0",
                "-g",
                "-std=c++20",
                "${file}",
                "-o",
                "${fileDirname}/build/${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "g++: build active file."
        }
    ],
    "version": "2.0.0"
}
```
Using:
- Open a *.cpp file to compile.  
- Press `Ctrl + Shift + P` to call the console.  
- Type `tasks build` to run the task.  

### Debug

Launch a *.cpp file in debug mode (`/.vscode/launch.json`)(depends on the task `build`):  
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Run the active *.cpp file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/build/${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "preLaunchTask": "build",
            "miDebuggerPath": "c:/_programs/MinGW/bin/gdb.exe"
        }
    ]
}
```
Using:
- Open a *.cpp file to compile.  
- Press `Ctrl + Shift + P` to call the console.  
- Type `debug` and chose a debug task.  

### Keybindings
- Default:
  - Ctrl+K -> Ctrl+O : Open Folder;
  - Ctrl+K -> Ctrl+S : Keyboard Shortcuts;
  - Ctrl+K -> V : Open Preview on Side;
  - Ctrl+Shift+V : Open Preview;
- Customized:
  - Ctrl+F -> Ctrl+T : Focus Terminal;

### Plug-ins
- Plug-ins for VS Code: 
  - C/C++, 
  - Test Explorer UI, 
  - C++ TestMate, 
  - CMake, 
  - CMake Tools, 
  - Doxygen Documentation Generator.
 
[Back](#vs-code)
