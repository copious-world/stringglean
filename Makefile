CFLAGS=-Wall -Wextra -pedantic -O3 -I/usr/local/include/ -std=c++17
#
#LDFLAGS=-lstdc++fs
.PHONY: all clean

all : bin/stringglean bin/hashreplacer bin/clear_empty_lines bin/template_to_static


bin/stringglean : obj/stringglean.o
	${CXX} $^ -o $@ ${LDFLAGS}


bin/hashreplacer : obj/hashreplacer.o
	${CXX} $^ -o $@ ${LDFLAGS}


bin/clear_empty_lines : obj/clear_empty_lines.o
	${CXX} $^ -o $@ ${LDFLAGS}


bin/template_to_static : obj/template_to_static.o
	${CXX} $^ -o $@ ${LDFLAGS}


obj/%.o : %.cpp
	bash tools/builddirs.sh
	${CXX} -c $^ ${CFLAGS} -o $@ 


clean : 
	-rm -f obj/*.o bin/*
