__start__: obj __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -iquote inc
LDFLAGS=-Wall
LIBS=-lpthread

interp: obj/main.o obj/xmlinterp.o obj/LibInterface.o obj/Scene.o obj/Set4LibInterfaces.o obj/InterpProgram.o obj/Configuration.o obj/Sender.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/LibInterface.o obj/Scene.o obj/Set4LibInterfaces.o obj/InterpProgram.o obj/Sender.o obj/Configuration.o obj/xmlinterp.o -ldl -lxerces-c  ${LIBS}

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/main.o: src/main.cpp inc/InterpProgram.hh inc/Configuration.hh inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/Set4LibInterfaces.o: src/Set4LibInterfaces.cpp inc/Set4LibInterfaces.hh
	g++ -c ${CPPFLAGS} -o obj/Set4LibInterfaces.o src/Set4LibInterfaces.cpp

obj/InterpProgram.o: src/InterpProgram.cpp inc/InterpProgram.hh
	g++ -c ${CPPFLAGS} -o obj/InterpProgram.o src/InterpProgram.cpp

obj/Scene.o: src/Scene.cpp inc/Scene.hh
	g++ -c ${CPPFLAGS} -o obj/Scene.o src/Scene.cpp

obj/Configuration.o: src/Configuration.cpp inc/Configuration.hh
	g++ -c ${CPPFLAGS} -o obj/Configuration.o src/Configuration.cpp

obj/Sender.o: src/Sender.cpp inc/Sender.hh
	g++ -c ${CPPFLAGS} -o obj/Sender.o src/Sender.cpp


clean:
	rm -f obj/* interp core*
	rm -fr obj/* xmlinterp4config core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
