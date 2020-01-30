#ifndef GOD_HEADER_GUARD
#define GOD_HEADER_GUARD

#include <vector>

#include "room.hpp"
#include "exception.hpp"

#define CREAT_ROOM "Create_room"
#define SWITCH_ROOM "Switch_room"
#define JOIN "Join"
#define VOTE "Vote"
#define END_VOTE "End_vote"
#define DETECT "Detect"
#define HEAL "Heal"
#define SILENT "Silent"
#define GET_ROOM_STATE "Get_room_state"

#define ROOM_NOT_FOUND rooms.size()
#define SWITCH_ROOM_COMMAND_SIZE 2
#define CREATE_ROOM_COMMAND_MIN 2
#define VOTE_COMMAND_LEN 3
#define END_VOTE_COMMAND_LEN 1
#define DETECT_COMMAND_LEN 3
#define HEAL_COMMAND_LEN 3
#define SILENT_COMMAND_LEN 3
#define GET_ROOM_STATE_COMMAND_LEN 1
#define JOIN_COMMAND_LEN_MIN 2

class God
{
public:
	God(std::string _name):name(_name){}
	~God();
	void doo(){}
	int search_room(std::string room_name);
	void create_room(std::vector<std::string> &command_splited);
	void switch_room(std::vector<std::string> &command_splited);
	void join(std::vector<std::string> &command_splited);
	void vote(std::vector<std::string> &command_splited);
	void end_vote(std::vector<std::string> &command_splited);
	void detect(std::vector<std::string> &command_splited);
	void heal(std::vector<std::string> &command_splited);
	void silent(std::vector<std::string> &command_splited);
	void get_room_state(std::vector<std::string> &command_splited);
	void if_game_ended_in_current_room();
	void creat_room_command_len_check(std::vector<std::string> command_splited);
	void details_validity(std::vector<std::string> &command_splited);
private:
	std::string name;
	std::vector<Room*> rooms;
	Room* current_room=NULL;
	
};
void command_split(std::string command_line , std::vector<std::string> &command_splited);
void get_command(std::string command_line , std::vector<std::string> &command_splited);
void execute_command(std::vector<std::string> &command_splited ,God& god);
#endif