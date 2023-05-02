CC = gcc
DEPS = mode1.h mode2.h
OFILES = main.o init.o trains.o schedules.o linkedlist.o moving_advanced.o controlled_passenger.o moving_basics.o passenger_creation.o
LINKS = -l SDL2 -l SDL2_image -l fmod 
all: start
.PHONY : all clean

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< 
 
exec: $(OFILES)
	$(CC) $(OFILES) -o exec $(LINKS) 

start: exec
	./exec

clear:
	rm -f *.o
	rm exec

