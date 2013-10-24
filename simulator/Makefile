CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c robot-api.c simulator.c robot.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=simulator
INCLUDE=
LIBS = -lglut -lGL -lGLU -lpthread -lm

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o $(INCLUDE) $@

clean:
	rm -f $(OBJECTS)

