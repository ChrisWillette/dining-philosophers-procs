#chris willette
#cs360 hw6 (philo)

CC = gcc
CFLAGS = -g -std=gnu99 -Wall -Wextra -pedantic


philo: philo.o random.o
	$(CC) $(CFLAGS) random.o philo.o -o philo -lm

philo.o: philo.c
	$(CC) $(CFLAGS) -c philo.c

random.o:
	$(CC) $(CLAGS) -c random.c -lm

clean:
	-rm -rf *.o philo
