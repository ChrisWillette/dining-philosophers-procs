#chris willette
#cs360 hw6 (philo)

CC = gcc
CFLAGS = -g -std=c11 -Wall -Wextra -pedantic
RANDOM = /encs_share/cs/class/cs360

philo: main.o gRandom.o
	$(CC) $(CFLAGS) gRandom.o main.o -o philo

main.o: philo.c
	$(CC) $(CFLAGS) -I$(RANDOM)/include philo.c -o main.o

gRandom.o: random.c random.h
	$(CC) $(CLAGS) -I$(RANDOM)/include $(RANDOM)/src/random.c -o gRandom.o

clean:
	-rm -rf *.o philo
