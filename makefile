EASTWEST_INC=-I/usr/include/libxml2 -I${HOME}/incl
EASTWEST_LIB=-L${HOME}/lib/
EASTWEST_FLA=-lxml2 -lz -lpthread -lm -lcurses -lWriteLog -ldl

all:main clean

main:main.c EastWest.o
	cc -o main main.c EastWest.o $(EASTWEST_INC) $(EASTWEST_LIB) $(EASTWEST_FLA)
EastWest.o:EastWest.c EastWest.h
	cc -g -c EastWest.c $(EASTWEST_INC)
test.so:test.c EastWest.h EastWest.o 
	cc test.c EastWest.o -fPIC -shared -o test.so $(EASTWEST_INC) $(EASTWEST_LIB) $(EASTWEST_FLA)
clean:
	rm -f *.o
