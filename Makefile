_files = main.cpp dool.cpp operators.cpp button.cpp files.cpp tile.cpp utilities.cpp
files = $(addprefix $(CURRENT_DIRECTORY), $(_files))

RAYLIB_PATH=C:\raylb\raylib
COMPILER_PATH=C:\raylib\mingw\bin
CC=$(COMPILER_PATH)\g++

# comment out -Wl,-subsystem,windows to enable console
CFLAGS=C:\raylib\raylib\src\raylib.rc.data -s -static -Os -std=c++11 -Wall -Iexternal -DPLATFORM_DESKTOP -Wl,-subsystem,windows
LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32

Release:
	$(CC) -o main.exe $(files) $(CFLAGS) $(LDFLAGS)
	main.exe
