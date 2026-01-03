CFLAGS = -Wall -Wextra
BUILD = build

all: $(BUILD)/3drender

build:
	mkdir -p $(BUILD)

build/3drender: $(BUILD)/main.o 
# 	echo "Linking and finalizing"
	gcc $(CFLAGS) $(BUILD)/main.o -o $(BUILD)/3drender -lm `sdl2-config --cflags --libs`
	chmod +x $(BUILD)/3drender
# 	./$(BUILD)/final

$(BUILD)/main.o: main.c
# 	echo "Compiling main.c"
	gcc $(CFLAGS) -c main.c -o $(BUILD)/main.o

clean:
# 	echo "Removing build files..."
	rm -rf $(BUILD)/*
