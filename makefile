LIBS = -lpthread

fp: deque.o run.o main.o fight.o stats.o fighter.o
	gcc -g -o fp deque.o fighter.o run.o main.o fight.o stats.o $(LIBS)

main.o: main.c defs.h
	gcc -g -c main.c $(LIBS)

deque.o: deque.c defs.h
	gcc -g -c deque.c $(LIBS)

fighter.o: fighter.c defs.h
	gcc -g -c fighter.c $(LIBS)

run.o: run.c defs.h
	gcc -g -c run.c $(LIBS)

fight.o: fight.c defs.h
	gcc -g -c fight.c $(LIBS)

stats.o: stats.c defs.h
	gcc -g -c stats.c $(LIBS)

clean:
	rm -f fp *.o


