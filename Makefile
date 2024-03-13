all: compile link

compile:
	g++ -Isfml/include -Iinclude -c src/*.cpp

link:
	g++ -std=c++17 -m32 *.o -o main -Lsfml/lib -lsfml-graphics -lsfml-window -lsfml-system
	
	