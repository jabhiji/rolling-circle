# compiler used
CC = g++ 

# optional compile time flags (-O2, -O3 etc)
CFLAGS = -O3

EXE = ball.x

## Build targets

# root target (builds the final executable)

$(EXE):	main.o \
	drawCircle.o \
	createVertexArray.o
	$(CC) main.o drawCircle.o createVertexArray.o -o $(EXE) -framework OpenGL -framework Cocoa -framework IOKit -L /usr/local/lib -lglfw

# compile dependencies

main.o: main.h main.cpp
	$(CC) $(CFLAGS) -I /usr/local/include -c main.cpp -o main.o

drawCircle.o: drawCircle.h drawCircle.cpp
	$(CC) $(CFLAGS) -I /usr/local/include -c drawCircle.cpp -o drawCircle.o

createVertexArray.o: createVertexArray.h createVertexArray.cpp
	$(CC) $(CFLAGS) -c createVertexArray.cpp -o createVertexArray.o

clean:
	/bin/rm -f *.o

veryclean:
	/bin/rm -f *.o *.x
