REST = src/game.cpp src/snake.cpp -o build/snake -std=c++11 -lncurses -Wextra -Werror

run_mac: snake_mac
	./build/snake
snake_mac: src/snake.cpp
	mkdir -p build
	g++ src/platform/macos.cpp $(REST)

run_linux: snake_linux
	./build/snake
snake_linux: src/snake.cpp
	mkdir -p build
	g++ src/platform/linux.cpp $(REST)

run_win: snake_win
	./build/snake
snake_win: src/snake.cpp
	if not exist build mkdir build
	g++ src/platform/win.cpp src/game.cpp src/snake.cpp -o build/snake -std=c++11 -Wextra -Werror

clean:
	rm build/snake
