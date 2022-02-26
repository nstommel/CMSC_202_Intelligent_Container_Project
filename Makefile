CFLAGS = -std=c++98 -Wall -ansi -gstabs -c

all: mytest my_array_driver sorted_driver

mytest: sorted.o mytest.o iterator_ex.o
	g++ -gstabs sorted.o mytest.o iterator_ex.o -o mytest

sorted_driver: sorted_driver.o sorted.o iterator_ex.o
	g++ -gstabs sorted_driver.o sorted.o iterator_ex.o -o sorted_driver

# New objects
sorted_driver.o: sorted_driver.cpp sorted.cpp sorted.h
	g++ $(CFLAGS) sorted_driver.cpp
mytest.o: mytest.cpp sorted.cpp sorted.h
	g++ $(CFLAGS) mytest.cpp
sorted.o: sorted.cpp sorted.h
	g++ $(CFLAGS) sorted.cpp
iterator_ex.o: iterator_ex.cpp iterator_ex.h
	g++ $(CFLAGS) iterator_ex.cpp

# Old objects and executable

my_array_driver: my_array_driver.o my_array.o
	g++ -gstabs my_array_driver.o my_array.o -o my_array_driver
	
my_array_driver.o: my_array_driver.cpp my_array.h
	g++ $(CFLAGS) my_array_driver.cpp
my_array.o: my_array.cpp my_array.h
	g++ $(CFLAGS) my_array.cpp

clean:
	rm -f *.o *~ my_array_driver
submit:
	cp sorted.h sorted.cpp mytest.cpp iterator_ex.h iterator_ex.cpp  ~/cs202proj/proj5/

