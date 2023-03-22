| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# _METR4810 Project_

## Setting up ESP-IDF
Follow this guide, link down the bottom for either mac/linux and windows.
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html

## Guide for setting up in vscode
After previous step can then setup in Vscode for intellisense etc.
https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md

## Note:
After setting up project this METR4810 project should be cloned into your esp folder or equivalent name.
In my esp folder I have:

```
esp
├── esp-idf
├── hello_world
└── METR4810_ESP_Code           This is the folder this repository should be cloned into.
```



## How to use example project
A recommended way is to follow the instructions on a [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).


## Example folder contents

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.
