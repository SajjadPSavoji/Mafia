#include "room_detail.hpp"

#define PLAYER_NOT_FOUND players.size()

using namespace std;
void RoomDetail::set_mafia(int new_value){mafia=new_value;}
void RoomDetail::set_villager(int new_value){villager=new_value;}
void RoomDetail::set_joker(int new_value){joker=new_value;}
void RoomDetail::set_detective(int new_value){detective=new_value;}
void RoomDetail::set_doctor(int new_value){doctor=new_value;}
void RoomDetail::set_immortal(int new_value){immortal=new_value;}
void RoomDetail::set_god_father(int new_value){god_father=new_value;}
void RoomDetail::set_silencer(int new_value){silencer=new_value;}
int str_to_int(string int_str)
{
	stringstream mystream (int_str);
	int int_out;
	mystream>>int_out;
	return int_out;
}
void RoomDetail::conservation_of_mafia(string &msg)
{
	if(silencer + god_father > mafia)
	{
		msg+="mafia especial members > total mafia :\n";
		msg+="silencers(";
		msg+=to_string(silencer);
		msg+=") + god_fathers(";
		msg+=to_string(god_father);
		msg+=") > mafia(";
		msg+=to_string(mafia);
		msg+=")\n";
	}
}
void RoomDetail::conservation_of_villagers(string &msg)
{
	if(immortal+detective+doctor > villager){
		msg+="villagers especial members > total villagers :\n";
		msg+="immortals(";
		msg+=to_string(immortal);
		msg+=") + detectives (";
		msg+=to_string(detective);
		msg+=")+doctors(";
		msg+=to_string(doctor);
		msg+=") > villagers(";
		msg+=to_string(villager);
		msg+=")\n";
	}
}
void RoomDetail::villagers_greater_than_mafia(string &msg)
{
	if(mafia > villager)
	{
		msg+="mafia members > villager members :\n";
		msg+="mafia("+to_string(mafia)+") > villagers("+to_string(villager)+")\n";
	}
}
void RoomDetail::god_father_unique(string &msg)
{
	if(god_father>1)
	{
		msg+="only one mafia can be god father:\n";
		msg+="godfather =";
		msg+=to_string(god_father);
		msg+="\n";
	}
}
void RoomDetail::roles_be_posetive()
{
	if(
	 mafia<0 || villager<0 ||joker<0 || detective<0 || 
	 doctor<0 ||immortal<0 ||god_father<0 ||silencer<0 
	 )
		throw Exp("Game roles can not have negetive value");
}
void RoomDetail::validity()
{
	roles_be_posetive();
	string msg;
	conservation_of_mafia(msg);
	conservation_of_villagers(msg);
	villagers_greater_than_mafia(msg);
	god_father_unique(msg);
	
	if(!msg.empty())
		throw Exp(msg);
}
void RoomDetail::set_details(vector<string> &command_splited)
{
	for (int i = 2; i < command_splited.size(); i+=2)
	{
		if(command_splited[i] == MAFIA_STR_DASH)
			set_mafia(str_to_int(command_splited[i+1]));
		else if(command_splited[i] == VILLAGER_STR_DASH)
			set_villager(str_to_int(command_splited[i+1]));
		else if(command_splited[i] == DOCTOR_STR_DASH)
			set_doctor(str_to_int(command_splited[i+1]));
		else if(command_splited[i] == IMMORTAL_STR_DASH)
			set_immortal(str_to_int(command_splited[i+1]));
		else if(command_splited[i] == DETECTIVE_STR_DASH)
			set_detective(str_to_int(command_splited[i+1]));
		else if(command_splited[i] == SILENCER_STR_DASH)
			set_silencer(str_to_int(command_splited[i+1]));
		else if(command_splited[i] == GOD_FATHER_STR_DASH)
			set_god_father(str_to_int(command_splited[i+1]));
		else if(command_splited[i] == JOKER_STR_DASH)
			set_joker(str_to_int(command_splited[i+1]));
		else
			throw Exp("invalid role : "+ command_splited[i]);
	}
}
int RoomDetail::player_sum()
{
	return mafia+villager+joker;
}
void RoomDetail::can_join(vector<string> &new_players)
{
	if(new_players.size() + players.size() > player_sum())
		throw Exp("many users");
}
bool RoomDetail::enough_players()
{
	return (player_sum() == players.size());
}
int RoomDetail::search_player(std::string player_name)
{
	for (int i = 0; i < players.size(); ++i)
	{
		if(players[i]==player_name)
			return i;
	}
	return players.size();
}
void RoomDetail::add_player(string new_player)
{
	if(search_player(new_player)==PLAYER_NOT_FOUND)
		players.push_back(new_player);
	else
		cout<<"player name:"<<new_player<<"was duplicate"<<endl;
}
