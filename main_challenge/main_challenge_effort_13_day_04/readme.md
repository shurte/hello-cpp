## VS Code settings

```json
{
    "terminal.integrated.defaultProfile.windows": "Command Prompt",
    "C_Cpp.default.compilerPath": "c:/_programs/msys64/ucrt64/bin/g++",
    "launch": {
        "version": "0.2.0",
        "configurations": [  
            {
                "name": "My Debug",
                "type": "cppdbg",
                "request": "launch",
                "program": "${workspaceFolder}/main.exe",
                "MIMode": "gdb",
                "miDebuggerPath": "c:/_programs/msys64/ucrt64/bin/gdb.exe",
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
    },
    "editor.fontFamily": "'Fira Code', monospace, Consolas, 'Courier New'",
    "terminal.integrated.profiles.windows": {
        "PowerShell": {
            "source": "PowerShell",
            "icon": "terminal-powershell"
        },
        "Command Prompt": {
            "path": [
                "${env:windir}\\Sysnative\\cmd.exe",
                "${env:windir}\\System32\\cmd.exe"
            ],
            "args": ["/K", "setup.bat"],
            "icon": "terminal-cmd"
        },
        "Git Bash": {
            "source": "Git Bash"
        }
    }
}
```