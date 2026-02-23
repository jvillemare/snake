UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
    PLATFORM = src/platform/linux.cpp
else ifeq ($(UNAME), Darwin)
    PLATFORM = src/platform/macos.cpp
else ifeq ($(UNAME), Windows)
    PLATFORM = src/platform/win.cpp
endif

run: snake
	./build/snake

snake: src/snake.cpp
	g++ $(PLATFORM) src/game.cpp src/snake.cpp -o build/snake -std=c++11 -lncurses -Wextra -Werror

clean:
	rm build/snake
