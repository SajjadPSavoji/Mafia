#ifndef ROOM_DETAIL_HEADER_GUARD
#define ROOM_DETAIL_HEADER_GUARD
#include <iostream>
#include <vector>
#include <sstream>

#include "exception.hpp"

#define MAFIA_STR_DASH "-Mafia"
#define VILLAGER_STR_DASH "-Villager"
#define DOCTOR_STR_DASH "-Doctor"
#define IMMORTAL_STR_DASH "-RouinTan"
#define DETECTIVE_STR_DASH "-Detective"
#define SILENCER_STR_DASH "-Silencer"
#define GOD_FATHER_STR_DASH "-GodFather"
#define JOKER_STR_DASH "-Joker"

class RoomDetail
{
public:
	void set_mafia(int new_value);
	void set_villager(int new_value);
	void set_joker(int new_value);
	void set_detective(int new_value);
	void set_doctor(int new_value);
	void set_immortal(int new_value);
	void set_god_father(int new_value);
	void set_silencer(int new_value);

	int get_mafia(){return mafia;}
	int get_villager(){return villager;}
	int get_joker(){return  joker;}
	int get_detective(){return detective;}
	int get_doctor(){return doctor;}
	int get_immortal(){return immortal;}
	int get_god_father(){return god_father;}
	int get_silencer(){return silencer;}

	void set_details(std::vector<std::string> &command_splited);

	void roles_be_posetive();
	void god_father_unique(std::string &msg);
	void villagers_greater_than_mafia(std::string &msg);
	void conservation_of_villagers(std::string &msg);
	void conservation_of_mafia(std::string &msg);
	void validity();
	int  player_sum();
	void can_join(std::vector<std::string> &new_players);
	bool enough_players();
	void add_player(std::string new_player);
	int search_player(std::string player_name);
	friend class Room;

private:
	int mafia=0;
	int villager=0;
	int joker=0;
	int detective=0;
	int doctor=0;
	int immortal=0;
	int god_father=0;
	int silencer=0;
	std::vector<std::string> players;
	
};

int str_to_int(std::string int_str);

#endif