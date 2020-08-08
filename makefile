all: src/main.cpp
	  mkdir build
	  g++ -o build/SnekSnek -lsfml-graphics -lsfml-system -lsfml-window -Iinclude/ src/*.cpp

  clean:
	rm -r build/
