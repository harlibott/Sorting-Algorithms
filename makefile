executable: sort.o
	g++ sort.o -o main

run: main
	./main random.txt

sort.o: sort.cpp
	g++ -c sort.cpp

clean:
	rm *.o main
