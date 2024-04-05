all: tetris

tetris: main.o tetris.o figure.o graphicEngine.o
	g++ main.o tetris.o figure.o graphicEngine.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system

figure: g++ -c figure.cpp

main.o: main.cpp
	g++ -c main.cpp

tetris.o: tetris.cpp
	g++ -c tetris.cpp

figure.o: figure.cpp
	g++ -c figure.cpp

graphicsEngine.o: graphicsEngine.cpp
	g++ -c graphicsEngine.cpp

clean:
	rm -rf *.o tetris
