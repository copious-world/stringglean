CFLAGS=-Wall -Wextra -pedantic -O3 -I/usr/local/include/ -I../API/mosquitto/lib -I../API/mosquitto/lib/cpp -std=c++17
#
#LDFLAGS=-lstdc++fs
.PHONY: all clean

all : stringglean hashreplacer clear_empty_lines subofpub template_to_static

stringglean : stringglean.o
	${CXX} $^ -o $@ ${LDFLAGS}


hashreplacer : hashreplacer.o
	${CXX} $^ -o $@ ${LDFLAGS}


clear_empty_lines : clear_empty_lines.o
	${CXX} $^ -o $@ ${LDFLAGS}


subofpub : subofpub.o
	${CXX} $^ -o $@ ${LDFLAGS}


template_to_static : template_to_static.o
	${CXX} $^ -o $@ ${LDFLAGS}



stringglean.o : stringglean.cpp
	${CXX} -c $^ ${CFLAGS} -o $@ 

hashreplacer.o : hashreplacer.cpp
	${CXX} -c $^ ${CFLAGS} -o $@ 

clear_empty_lines.o : clear_empty_lines.cpp
	${CXX} -c $^ ${CFLAGS} -o $@ 

subofpub.o : subofpub.cpp
	${CXX} -c $^ ${CFLAGS} -o $@ 

template_to_static.o : template_to_static.cpp
	${CXX} -c $^ ${CFLAGS} -o $@ 




clean : 
	-rm -f *.o stringglean

