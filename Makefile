files_game = main.cpp dool.cpp environment.cpp operators.cpp player.cpp button.cpp files.cpp
files_editor = editor.cpp dool.cpp environment.cpp operators.cpp player.cpp button.cpp files.cpp
files = $(addprefix $(CURRENT_DIRECTORY), $(files_game))
files_e = $(addprefix $(CURRENT_DIRECTORY), $(files_editor))

RAYLIB_PATH=C:\raylb\raylib
COMPILER_PATH=C:\raylib\mingw\bin
CC=$(COMPILER_PATH)\g++

# comment out -Wl,-subsystem,windows to enable console
CFLAGS=C:\raylib\raylib\src\raylib.rc.data -s -static -Os -std=c++11 -Wall -Iexternal -DPLATFORM_DESKTOP -Wl,-subsystem,windows
LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32

All:
	$(CC) -o main.exe $(files) $(CFLAGS) $(LDFLAGS)
	$(CC) -o level_test.exe $(files) $(CFLAGS) -DDEV_LEVEL_TEST $(LDFLAGS)
	$(CC) -o editor.exe $(files_e) $(CFLAGS) $(LDFLAGS)

Release:
	$(CC) -o main.exe $(files) $(CFLAGS) $(LDFLAGS)
	main.exe

Tester:
	$(CC) -o level_test.exe $(files) $(CFLAGS) -DDEV_LEVEL_TEST $(LDFLAGS)

Editor:
	$(CC) -o editor.exe $(files_e) $(CFLAGS) $(LDFLAGS)
