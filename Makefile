CFLAGS = -std=c++98 -Wall -ansi -gstabs -c

all: mytest.out sorted_driver.out

mytest.out: sorted.o mytest.o iterator_ex.o
	g++ -gstabs sorted.o mytest.o iterator_ex.o -o mytest.out

sorted_driver.out: sorted_driver.o sorted.o iterator_ex.o
	g++ -gstabs sorted_driver.o sorted.o iterator_ex.o -o sorted_driver.out

sorted_driver.o: sorted_driver.cpp sorted.cpp sorted.h
	g++ $(CFLAGS) sorted_driver.cpp
mytest.o: mytest.cpp sorted.cpp sorted.h
	g++ $(CFLAGS) mytest.cpp
sorted.o: sorted.cpp sorted.h
	g++ $(CFLAGS) sorted.cpp
iterator_ex.o: iterator_ex.cpp iterator_ex.h
	g++ $(CFLAGS) iterator_ex.cpp

clean:
	rm -f *.o *~ *.out
submit:
	cp sorted.h sorted.cpp mytest.cpp iterator_ex.h iterator_ex.cpp  ~/cs202proj/proj5/

