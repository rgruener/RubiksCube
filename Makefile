rubiks.exe: rubiks.o cube.o piece.o face.o InitShader.o
	g++ -o rubiks.exe rubiks.o cube.o piece.o face.o InitShader.o -lGLEW -lglut -lGL -lXmu -lX11 -lm -I./include

rubiks.o: rubiks.cpp
	g++ -c rubiks.cpp -I./include

cube.o: cube.cpp cube.h
	g++ -c cube.cpp -I./include

piece.o: piece.cpp piece.h
	g++ -c piece.cpp -I./include

face.o: face.cpp face.h
	g++ -c face.cpp -I./include

InitShader.o: InitShader.cpp
	g++ -c InitShader.cpp -I./include

clean:
	rm -f *.exe *.o *.stackdump *~ *.swp *.swo *.swn
