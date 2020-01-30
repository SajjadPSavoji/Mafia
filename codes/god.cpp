#include "god.hpp"

using namespace std;
void command_split(string command_line , vector<string> &command_splited)
{
	string delimiter=" ";
	size_t pos = 0;
	string token;

	while ((pos = command_line.find(delimiter)) != std::string::npos) {
	    token = command_line.substr(0, pos);
	    command_splited.push_back(token);
	    command_line.erase(0, pos + delimiter.length());
	}
	command_splited.push_back(command_line);
}
void get_command(string command_line , vector<string> &command_splited)
{
	command_splited.clear();
	command_split(command_line , command_splited);
}
void execute_command(vector<string> &command_splited ,God& god)
{
	if      (command_splited[0] == CREAT_ROOM) 		   god.create_room(command_splited);
	else if (command_splited[0] == SWITCH_ROOM) 	   god.switch_room(command_splited); 
	else if (command_splited[0] == JOIN) 		  	   god.join(command_splited); 
	else if (command_splited[0] == VOTE) 		       god.vote(command_splited); 
	else if (command_splited[0] == END_VOTE) 	       god.end_vote(command_splited); 
	else if (command_splited[0] == DETECT) 		       god.detect(command_splited); 
	else if (command_splited[0] == HEAL) 		       god.heal(command_splited);
	else if (command_splited[0] == SILENT) 		       god.silent(command_splited); 
	else if (command_splited[0] == GET_ROOM_STATE)     god.get_room_state(command_splited); 
	else
	{
		throw Exp("invalid command :"+command_splited[0]);
	}
}
void God::if_game_ended_in_current_room()
{
	if(current_room->game_ended == true)
		throw Exp("game ended in this room");
}
int God::search_room(string room_name)
{
	for (int i = 0; i < rooms.size(); ++i)
	{
		if(rooms[i]->get_name()== room_name)
			return i;
	}
		return rooms.size();
}
void God::creat_room_command_len_check(vector<string> command_splited)
{
	if(command_splited.size() < 4)
		throw Exp("creat room command has at least 4 arguments");
	if(command_splited.size()%2)
		throw Exp("all roles must have number");
}
void God::details_validity(std::vector<std::string> &command_splited)
{
	for (int i = 2; i < command_splited.size(); i+=2)
	{
		if(
			command_splited[i]!= MAFIA_STR_DASH &&
			command_splited[i]!= VILLAGER_STR_DASH &&
			command_splited[i]!= DOCTOR_STR_DASH &&
			command_splited[i]!= IMMORTAL_STR_DASH &&
			command_splited[i]!= DETECTIVE_STR_DASH &&
			command_splited[i]!= SILENCER_STR_DASH &&
			command_splited[i]!= GOD_FATHER_STR_DASH &&
			command_splited[i]!= JOKER_STR_DASH
		  )
			throw Exp("invalid role was given");
	}
}
void God::create_room(vector<string> &command_splited)
{
	creat_room_command_len_check(command_splited);
	string new_room_name=command_splited[1];
	if(search_room(new_room_name)== ROOM_NOT_FOUND)
	{
		RoomDetail new_room_detail;
		details_validity(command_splited);
		new_room_detail.set_details(command_splited);
		new_room_detail.validity();
		Room* new_room=new Room(new_room_name , new_room_detail);
		rooms.push_back(new_room);	
		current_room=new_room;
	}
	else 
		throw Exp("a room already exist by the name :"+new_room_name);
}
void God::switch_room(vector<string> &command_splited)
{
	if(
		command_splited.size()!=SWITCH_ROOM_COMMAND_SIZE ||
		search_room(command_splited[1])== ROOM_NOT_FOUND 
	  )
		throw Exp("Invalid room name");
	else 
		current_room=rooms[search_room(command_splited[1])];
}
void God::join(vector<string> &command_splited)
{
	if(current_room == NULL)
		throw Exp("no room created yet");
	if_game_ended_in_current_room();
	if(command_splited.size() < JOIN_COMMAND_LEN_MIN)
		throw Exp("vote command gets at least 2 arguments!");
	command_splited.erase(command_splited.begin());
	current_room->join_players(command_splited);
}
void God::vote(vector<string> &command_splited)
{
	if(current_room == NULL)
		throw Exp("no room created yet");
	if(command_splited.size()!= VOTE_COMMAND_LEN)
		throw Exp("vote command gets 3 argument!");
	if_game_ended_in_current_room();
	command_splited.erase(command_splited.begin());
	current_room->vote(command_splited);
}
void God::end_vote(vector<string> &command_splited)
{
	if(current_room == NULL)
		throw Exp("no room created yet");
	if(command_splited.size()!= END_VOTE_COMMAND_LEN)
		throw Exp("End_vote command gets 1 argument!");
	if_game_ended_in_current_room();
	current_room->end_vote();
}
void God::detect(vector<string> &command_splited)
{
	if(current_room == NULL)
		throw Exp("no room created yet");
	if(command_splited.size()!= DETECT_COMMAND_LEN)
		throw Exp("End_vote command gets 3 argument!");
	if_game_ended_in_current_room();
	command_splited.erase(command_splited.begin());
	current_room->detect(command_splited[0],command_splited[1]);	
}
void God::heal(vector<string> &command_splited)
{
	if(current_room == NULL)
		throw Exp("no room created yet");
	if(command_splited.size()!= HEAL_COMMAND_LEN)
		throw Exp("Heal command gets 3 argument!");
	if_game_ended_in_current_room();
	command_splited.erase(command_splited.begin());
	current_room->heal(command_splited[0],command_splited[1]);
}
void God::silent(std::vector<std::string> &command_splited)
{
	if(current_room == NULL)
		throw Exp("no room created yet");
	if(command_splited.size()!= SILENT_COMMAND_LEN)
		throw Exp("Silent command gets 3 argument!");
	if_game_ended_in_current_room();
	command_splited.erase(command_splited.begin());
	current_room->silent(command_splited[0],command_splited[1]);
}
void God::get_room_state(std::vector<std::string> &command_splited)
{
	if(current_room == NULL)
		throw Exp("no room created yet");
	if(command_splited.size()!= GET_ROOM_STATE_COMMAND_LEN)
		throw Exp("Silent command gets 1 argument!");
	if_game_ended_in_current_room();
	current_room->get_room_state();
}
God::~God()
{
	for (int i = 0; i < rooms.size(); ++i)
	{
		delete rooms[i];
	}
}

