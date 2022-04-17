CC = gcc

solution:
	$(CC) solution.c -o solution -lm -lpthread 
	

clean:
	rm -f solution *.o 
