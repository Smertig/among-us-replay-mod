<p align="center">
  <a href="https://store.steampowered.com/app/945360/Among_Us/"><img src="https://cdn.cloudflare.steamstatic.com/steam/apps/945360/header.jpg"></a>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License: MIT">
  <a href="https://github.com/Smertig/among-us-replay-mod/releases/latest"><img src="https://img.shields.io/github/v/release/Smertig/among-us-replay-mod.svg" alt="Latest Release"></a>
  <a href="https://github.com/Smertig/among-us-replay-mod/actions"><img src="https://github.com/Smertig/among-us-replay-mod/workflows/Build%20On%20Push/badge.svg" alt="GitHub Actions"></a>
  <img src="https://img.shields.io/github/downloads/smertig/among-us-replay-mod/total">
</p>

# Among Us Replay Mod</b>

This repository contains source code of Replay Mod for [Among Us](https://store.steampowered.com/app/945360/Among_Us/) PC version. This mod allows you to record every played game round and automatically save it. All the recorded rounds can be later _replayed_ using [Among Us Replayer](https://github.com/Smertig/among-us-replayer).

| Game version    | Mod version   |
|-----------------|---------------|
| v2020.6.9s      | 0.6.0 - 0.6.5 |
| v2020.9.22s     | 0.5.0 - 0.6.5 |
| v2020.10.8i     | 0.6.0 - 0.6.5 |
| v2020.10.22s    | 0.6.2 - 0.6.5 |
| v2020.11.4s     | 0.6.3 - 0.6.5 | 
| v2020.11.17s    | 0.6.4 - 0.6.5 |
| v2020.12.9s     | 0.6.5 - 0.6.5 |
| v2021.3.5s      | 0.7.0         |
| v2021.4.12s     | 0.7.1         |
| v2022.3.29s     | 0.8.0 - 0.8.1 |
| v2022.4.19e     | 0.8.1         |
| **v2022.6.21s** | **≥0.8.2**    |
| **v2022.6.22s** | **≥0.8.2**    |


## Usage

### Recording game

- Download `among-us-replay-mod.zip` from [latest release](https://github.com/Smertig/among-us-replay-mod/releases/latest) page
- Unpack it
- Run game
- Run `injector.exe`

:warning: **You should run `injector.exe` on every game restart.**

All the replays can be later found for **Steam** at `/Steam/steamapps/common/Among Us/replay` and  
for **Epic Games** at `/Epic Games/AmongUs/replay`

### Replaying game

- Check out [Among Us Replayer](https://github.com/Smertig/among-us-replayer) for detailed instruction

### Replay Demo

[Youtube](https://youtu.be/j3DKQzkoJLM)

## Development

:warning: This section is only for developers, you don't need all this stuff if you just want to use mod. 

### How To Build

Requirements:
- Windows
- C++20 compiler (tested on MSVC 16.7.5)
- CMake 3.17

```shell script
# 0. Clone repo *with submodules*
git clone --recursive https://github.com/Smertig/among-us-replay-mod
cd among-us-replay-mod

# 1. Create build directory
mkdir build
cd build

# 2. Configure CMake project
cmake .. -DCMAKE_BUILD_TYPE=Release -A Win32

# 3. Build project (both mod and injector)
cmake --build . --config Release

# 4. Check out build artifacts at 'among-us-replay-mod/build/Release' directory
```

### License

- MIT

### References

- ![](https://img.shields.io/github/stars/Neargye/magic_enum.svg?style=social) [magic_enum](https://github.com/Neargye/magic_enum) by [Neargye](https://github.com/Neargye)
- ![](https://img.shields.io/github/stars/fmtlib/fmt.svg?style=social) [fmtlib](https://github.com/fmtlib/fmt) by [vitaut](https://github.com/vitaut)
- ![](https://img.shields.io/github/stars/gabime/spdlog.svg?style=social) [spdlog](https://github.com/gabime/spdlog) by [gabime](https://github.com/gabime)
- ![](https://img.shields.io/github/stars/Smertig/rcmp.svg?style=social) [rcmp](https://github.com/Smertig/rcmp) by [Smertig](https://github.com/Smertig)
