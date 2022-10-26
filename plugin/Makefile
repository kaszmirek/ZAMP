

__start__: obj __lines_for_space__ ../libs/libInterp4Move.so
__start__: obj __lines_for_space__ ../libs/libInterp4Pause.so 
	@echo "  Tworzenie wtyczki zakonczone."
	@echo

obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++17 -Iinc -I../inc
LDFLAGS=-Wall -shared

__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo

../libs/libInterp4Move.so: obj/Interp4Move.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Move.so obj/Interp4Move.o
	@echo
	@echo "  Wtyczka dla polecenia 'Move' zostala utworzona."
	@echo

../libs/libInterp4Pause.so: obj/Interp4Pause.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Pause.so obj/Interp4Pause.o
	@echo
	@echo "  Wtyczka dla polecenia 'Pause' zostala utworzona."
	@echo


obj/Interp4Move.o: src/Interp4Move.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Move.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Move.o src/Interp4Move.cpp

obj/Interp4Pause.o: src/Interp4Pause.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Pause.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Pause.o src/Interp4Pause.cpp


clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
