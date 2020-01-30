#ifndef ROOM_HEADER_GUARD
#define ROOM_HEADER_GUARD

#include <iostream>
#include <algorithm>

#include "room_detail.hpp"
#include "player.hpp"
#include "villager.hpp"
#include "mafia.hpp"
#include "godfather.hpp"
#include "silencer.hpp"
#include "doctor.hpp"
#include "detective.hpp"
#include "immortal.hpp"
#include "joker.hpp"

#define DAY "Day"
#define NIGHT "Night"
#define SPACE " "
#define DIED "Died"
#define MAFIA_TRY_TO_KILL "Mafia try to kill"
#define KILLED "Killed"
#define SILENCED "Silenced"
#define MAFIA_STR "Mafia"
#define VILLAGER_STR "Villager"
#define EQUAL "="
#define PLAYER_NOT_FOUND_IN_ROOM detail.players.size()
#define PLAYER_POINTER_NOT_FOUND_IN_ROOM players.size()
#define VOTER_NOT_FOUND votes.size()
#define VOTEE_NOT_FOUND vote_count.size()
#define DETECTIVE_NOT_ASKED detectives_asked.size()
#define DOCTOR_NOT_HEALED doctors_healed.size()
#define SILENCER_NOT_SILENTED silencers_silented.size()
#define NEXT_DAY day_number+1
#define THIS_NIGHT 	night_number

enum DON
{
	Day,
	Night
};

class Room
{
public:
	Room(std::string _name,RoomDetail _detail):detail(_detail),name(_name){};
	~Room();
	std::string get_name(){return name;}
	bool enough_vote_to_set_target();
	void clear_memories();
	void set_mafia_target(Player* target);
	void join_players(std::vector<std::string> &new_players);
	void start_game();
	void next_round();
	bool is_game_ended();
	void is_night_over();
	void push_roles_to_all_roles(std::vector<Role> &all_roles);
	void randomly_assign_players();
	void announce_mafia_target(Player* target);
	void vote(std::vector<std::string> &new_vote);
	void vote_day(std::vector<std::string> &new_vote);
	void vote_night(std::vector<std::string> &new_vote);
	void if_game_has_started();
	void if_player_alive(std::string user_name);
	void if_user_joined(std::string user_name);
	int search_voter(std::string voter_name);
	int search_player(std::string player_name);
	Player* player_with_mejority_votes();
	void kill(Player* victim);
	void announce_dead(Player* dead_player);
	void end_vote();
	int alive_mafias();
	int alive_silencers();
	int alive_doctors();
	int alive_detectives();
	int alive_villagers();
	void if_any_vote();
	void if_night();
	void if_day();
	void if_detective_alive(std::string detective_name);
	void can_detect(std::string detective_name);
	int search_tasks(std::string name,std::vector<std::string> tasks);
	void if_detectve_already_asked(std::string detective);
	void detect(std::string detective,std::string suspect);
	void if_doctor_alive(std::string doctor_name);
	void if_person_alive(std::string patient_name);
	void can_heal(std::string doctor_name);
	void if_doctor_already_healed(std::string doctor_name);
	void heal(std::string doctor,std::string patient);
	void if_silencer_alive(std::string silencer_name);
	void can_silent(std::string silencer_name);
	void if_silencer_already_silented(std::string silencer_name);
	void silent(std::string silencer,std::string person);
	void attack_target(Player* target);
	void announce_killed_at_night();
	void announce_silenced_at_night();
	void get_room_state();
	void if_night_vote_ended();
	void if_detect_ended();
	void if_heal_ended();
	void silent_conditions(std::string silencer, std::string person);
	void heal_conditions(std::string doctor, std::string patient);
	void detect_conditions(std::string detective ,std::string suspect);
	friend class God;
private:
	std::string name;
	RoomDetail detail;
	std::vector<Player*> players;
	DON don=Night;
	int day_number=0;
	int night_number=0;
	std::vector<std::pair<std::string,std::string>> votes;
	std::vector<std::string> doctors_healed;
	std::vector<std::string> detectives_asked;
	std::vector<std::string> silencers_silented;
	std::vector<Player*> mafia_targets;
	bool game_ended=false;
};
std::ostream& operator<< (std::ostream& out , DON don);
#endif