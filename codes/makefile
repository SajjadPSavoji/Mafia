all: ca3.o
ca3.o: main.o room.o room_detail.o god.o exception.o player.o villager.o detective.o doctor.o silencer.o
	g++ main.o room.o room_detail.o god.o exception.o player.o villager.o detective.o doctor.o silencer.o -o ca3.o
main.o: main.cpp
	g++ -c main.cpp
room.o: room.cpp room.hpp
	g++ -c room.cpp room.hpp
room_detail.o: room_detail.cpp room_detail.hpp
	g++ -c room_detail.cpp room_detail.hpp
god.o: god.cpp god.hpp
	g++ -c god.cpp god.hpp
exception.o: exception.cpp exception.hpp
	g++ -c exception.cpp exception.hpp
player.o: player.cpp player.hpp
	g++ -c player.cpp player.hpp
villager.o: villager.cpp villager.hpp
	g++ -c villager.cpp villager.hpp
detective.o: detective.cpp detective.hpp
	g++ -c detective.cpp detective.hpp
doctor.o: doctor.cpp doctor.hpp
	g++ -c doctor.cpp doctor.hpp
silencer.o: silencer.cpp silencer.hpp
	g++ -c silencer.cpp silencer.hpp
clean: 
	rm -r *.o
	rm -r *.gch