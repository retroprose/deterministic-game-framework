all: compile link clean

compile:
	g++ -I_sfml_include/include -Iinclude -c src/*.cpp

link:
	g++ -std=c++17 -m32 *.o -o bin/main -L_sfml_include/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del *.o
	