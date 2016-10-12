# Building

## Linux

This guide requires at least *Debian 8 (Jessie)* or *Ubuntu 16.04 (Xenial)*.

**Step 1.**  
Install the toolchain.

```sh
sudo apt-get install build-essential
```

**Step 2.**  
Install the SDL2 development packages.

```sh
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

**Step 3.**  
Clone the Git repository.

```sh
git clone git@github.com:robhendriks/city-defence.git
```

**Step 4.**  
Create a new directory called *build* inside the project root directory, navigate to it and execute CMake.

```sh
mkdir build && cd $_
cmake ..
```

**Step 5.**  
Compile and run.

```sh
make && ./city_defence
```

## macOS

This guide requires at least *macOS 10.10 (El Capitan)*. We're also assuming you've got Xcode (including the command line tools) installed. 

**Step 1.**  
Install Homebrew.

```sh
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

**Step 2.**  
Install CMake and the SDL2 development packages.

```sh
brew install cmake sdl2 sdl2_image sdl2_ttf
```

*Continue at Step 3 ([Linux](#linux)).*


## Windows

1. Download and install **MinGW**
  * https://sourceforge.net/projects/mingw/files/latest/download?source=files
  * Selecteer minimaal de **mingw32-gcc-g++** en **mingw32-base** packages
  * Voeg **C:\MinGW\bin** toe aan de **PATH omgevingsvariabelen**
2. Download and install **CLion**
  * https://www.jetbrains.com/clion/download/#section=windows-version
  * Gebruik MinGW als de toolchain
3. Download de **SDL development libraries voor MinGW**
  * https://www.libsdl.org/release/SDL2-devel-2.0.4-mingw.tar
  * https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-mingw.tar.gz
  * https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.1-mingw.tar.gz
4. Open de gedownloade **SDL2-devel-2.0.4-mingw.tar**
  * Kopieer **i686-w64-mingw32/bin/SDL2.dll** naar **C:/Windows/SysWOW64**
  * Kopieer de map SDL2 van **i686-w64-mingw32/include** naar de include map van MinGW (**C:/MinGW/include**)
  * Kopieer de **.a files** van **i686-w64-mingw32/lib** naar de lib map van MinGW (**C:/MinGW/lib**)
7. Open de gedownloade **SDL2_ttf-devel-2.0.14-mingw.tar.gz**
  * Kopieer **.dll files** van **i686-w64-mingw32/bin/** naar **C:/Windows/SysWOW64**
  * Kopieer de **.h files** van **i686-w64-mingw32/include/SDL2** naar **C:/MinGW/include/SDL2**
  * Kopieer de **.a files** van **i686-w64-mingw32/lib** naar de lib map van MinGW (**C:/MinGW/lib**)
8. Open de gedownloade **SDL2_image-devel-2.0.1-mingw.tar.gz**
  * Kopieer **.dll files** van **i686-w64-mingw32/bin/** naar **C:/Windows/SysWOW64**
  * Kopieer de **.h files** van **i686-w64-mingw32/include/SDL2** naar **C:/MinGW/include/SDL2**
  * Kopieer de **.a files** van **i686-w64-mingw32/lib** naar de lib map van MinGW (**C:/MinGW/lib**)
6. Haal het git project binnen en run het
  * Selecteer rechtsbovenin **city_defence** (ipv Build All) 
