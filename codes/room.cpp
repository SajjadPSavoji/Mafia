#include "room.hpp"
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
bool Room::is_game_ended()
{
	if(alive_mafias() == 0){
		cout<<"Victory!"<<endl;
		return true;
	}
	if(alive_mafias() >= alive_villagers())
	{
		cout<<"Loose!"<<endl;
		return true;
	}
	if(
		don == Day &&
		mafia_targets.size() && 
		mafia_targets[0]->role == Joker
	  )
	{
		cout<<"Do I look like a guy with a plan?"<<endl;
		return true;
	}
	return false;
}
void Room::set_mafia_target(Player* target)
{
	mafia_targets.push_back(target);
}
void Room::attack_target(Player* target)
{
	if(target->healed_night!=night_number)
		target->loose_life();
}
void Room::is_night_over()
{
	if(
		mafia_targets.size() == 1 &&
		silencers_silented.size() == alive_silencers() &&
		doctors_healed.size() == alive_doctors() &&
		detectives_asked.size() == alive_detectives() 
	  )
	{
		attack_target(mafia_targets[0]);
		if(!mafia_targets[0]->is_dead())
			mafia_targets.clear();
		next_round();
	}
}
void Room::push_roles_to_all_roles(vector<Role> &all_roles)
{
	for (int i = 0; i < detail.mafia - detail.god_father - detail.silencer; ++i)
	{
		all_roles.push_back(Mafia);
	}
	for (int i = 0; i < detail.villager - detail.detective - detail.doctor - detail.immortal ; ++i)
	{
		all_roles.push_back(Villager);
	}
	for (int i = 0; i < detail.joker; ++i)
	{
		all_roles.push_back(Joker);
	}
	for (int i = 0; i < detail.detective; ++i)
	{
		all_roles.push_back(Detective);
	}
	for (int i = 0; i < detail.doctor; ++i)
	{
		all_roles.push_back(Doctor);
	}
	for (int i = 0; i < detail.immortal; ++i)
	{
		all_roles.push_back(Immortal);
	}
	for (int i = 0; i < detail.god_father; ++i)
	{
		all_roles.push_back(GodFather);
	}
	for (int i = 0; i < detail.silencer; ++i)
	{
		all_roles.push_back(Silencer);
	}
}
Player* make_new_player(string name , Role role)
{
	Player* new_player;
		 
		 if(role == Mafia)      new_player = new MAFIA     (name , role);
	else if(role == Villager)   new_player = new VILLAGER  (name , role);
	else if(role == Joker)      new_player = new JOKER     (name , role);
	else if(role == Silencer)   new_player = new SILENCER  (name , role);
	else if(role == GodFather)  new_player = new GODFATHER (name , role);
	else if(role == Detective)  new_player = new DETECTIVE (name , role);
	else if(role == Doctor)     new_player = new DOCTOR    (name , role);
	else if(role == Immortal)   new_player = new IMMORTAL  (name , role);

	return new_player;

}
void Room::randomly_assign_players()
{
	srand(time(NULL));
	vector<Role> all_roles;
	push_roles_to_all_roles(all_roles);
	std::random_shuffle(all_roles.begin(), all_roles.end());
	for (int i = 0; i < all_roles.size(); ++i)
	{
		Player* new_player;
		new_player=make_new_player(detail.players[i],all_roles[i]); 
		players.push_back(new_player);
	}
}
std::ostream& operator<< (std::ostream& out , DON don)
{
	if(don == Day)
	{
		out<<DAY;
	}
	else if(don == Night)
	{
		out<<NIGHT;
	}
	return out;
}

void Room::clear_memories()
{
	votes.clear();
	doctors_healed.clear();
	detectives_asked.clear();
	silencers_silented.clear();
	mafia_targets.clear();
}
void Room::announce_killed_at_night()
{
	for (int i = 0; i < mafia_targets.size(); ++i)
	{
		cout<<KILLED<<SPACE<<mafia_targets[i]->name<<endl;
	}
}
void Room::announce_silenced_at_night()
{
	vector<string> silenced;
	for (int i = 0; i < players.size(); ++i)
	{
		if(players[i]->silenced_day == day_number && !players[i]->is_dead())
			silenced.push_back(players[i]->name);
	}
	sort(silenced.begin(),silenced.end());
	if(silenced.size())
		cout<<SILENCED;
	for (int i = 0; i < silenced.size(); ++i)
	{
		cout<<SPACE<<silenced[i];
	}
	if(silenced.size())
		cout<<endl;
}
void Room::next_round()
{
	if(!is_game_ended())
	{
		if(don == Day)
		{
			don = Night;
			night_number++;
			cout<<don<<SPACE<<night_number<<endl;
		}
		else if(don == Night)
		{
			don = Day;
			day_number++;
			cout<<don<<SPACE<<day_number<<endl;
			announce_killed_at_night();
			announce_silenced_at_night();
		}
		clear_memories();
	}
	else
	{
			game_ended=true;
	}
}
void Room::start_game()
{
	randomly_assign_players();
	cout<<players;
	next_round();
}
void Room::join_players(vector<string> &new_players)
{
	detail.can_join(new_players);
	for (int i = 0; i < new_players.size(); ++i)
	{
		detail.add_player(new_players[i]);
	}
	if(detail.enough_players())
		start_game();
}
void Room::if_game_has_started()
{
	if(day_number == 0)
		throw Exp("this room does not have enough players yet");
}
int Room::search_voter(string voter_name)
{
	for (int i = 0; i < votes.size(); ++i)
	{
		if(votes[i].first == voter_name)
			return i;
	}
	return votes.size();
}
int Room::search_player(std::string player_name)
{
	for (int i = 0; i < players.size(); ++i)
	{
		if(players[i]->name == player_name)
			return i;
	}
	return players.size();
}
bool sort_by_mejority(pair<string,int> a,pair<string,int> b)
{
	return(a.second > b.second);
}
int search_vote_count( vector<pair<string,int>> &vote_count,pair<string,string> a_vote)
{
	for (int i = 0; i < vote_count.size(); ++i)
	{
		if(vote_count[i].first == a_vote.second)
			return i;
	}
	return vote_count.size();
}
void count_vote(vector<pair<string,int>> &vote_count,pair<string,string> a_vote)
{
	int votee_index=search_vote_count(vote_count,a_vote);
	if(votee_index == VOTEE_NOT_FOUND){
		vote_count.push_back(pair<string,int>(a_vote.second,1));
	}
	else{
		vote_count[votee_index].second++;
	}
}
Player* Room::player_with_mejority_votes()
{
vector<pair<string, int>> vote_count;
	for (int i = 0; i < votes.size(); ++i)
	{
		count_vote(vote_count,votes[i]);
	}
	sort(vote_count.begin(),vote_count.end(),sort_by_mejority);
	vector<pair<string, int>> loosers;
	int max_vote=vote_count[0].second;
	for (int i = 0; i < vote_count.size(); ++i)
	{
		if(vote_count[i].second == max_vote)
			loosers.push_back(vote_count[i]);
	}
	srand(time(NULL));
	std::random_shuffle(loosers.begin(),loosers.end());
	return players[search_player(loosers[0].first)];
}
void Room::kill(Player* victim)
{
	victim->life=0;
}
void Room::announce_dead(Player* dead_player)
{
	cout<<DIED<<SPACE<<dead_player->name<<endl;
}
int Room::alive_mafias()
{
	int sum=0;
	for (int i = 0; i < players.size(); ++i)
	{
		if(players[i]->is_dead())
			continue;
		if(
			players[i]->role == Mafia||
			players[i]->role == Silencer||
			players[i]->role == GodFather
		  )
			sum++;
	}
	return sum;
}
int Room::alive_silencers()
{
	int sum=0;
	for (int i = 0; i < players.size(); ++i)
	{
		if(players[i]->is_dead())
			continue;
		if(
			players[i]->role == Silencer
		  )
			sum++;
	}
	return sum;
}
int Room::alive_doctors()
{
	int sum=0;
	for (int i = 0; i < players.size(); ++i)
	{
		if(players[i]->is_dead())
			continue;
		if(
			players[i]->role == Doctor
		  )
			sum++;
	}
	return sum;
}
int Room::alive_detectives()
{
	int sum=0;
	for (int i = 0; i < players.size(); ++i)
	{
		if(players[i]->is_dead())
			continue;
		if(
			players[i]->role == Detective
		  )
			sum++;
	}
	return sum;
}
void Room::vote_day(vector<string> &new_vote)
{
	int voter_index=this->search_player(new_vote[0]);
	int votee_index=this->search_player(new_vote[1]);
	if(players[voter_index]->silenced_day==day_number)
		throw Exp("This user has been silenced befor");
	voter_index=search_voter(new_vote[0]);
	if( voter_index == VOTER_NOT_FOUND ||
		votes[voter_index].second != new_vote[1]
	  )
			votes.push_back(pair<string,string>(new_vote[0],new_vote[1]));
}
bool Room::enough_vote_to_set_target()
{
	return votes.size() == alive_mafias();
}
void Room::announce_mafia_target(Player* target)
{
	cout<<MAFIA_TRY_TO_KILL<<SPACE<<target->name<<endl;
}
void Room::vote_night(vector<string> &new_vote)
{
	int voter_index=search_player(new_vote[0]);
	if(!players[voter_index]->can_vote_at_night())
		throw Exp("This user can not vote");
	voter_index=search_voter(new_vote[0]);
	if(voter_index == VOTER_NOT_FOUND)
			votes.push_back(pair<string,string>(new_vote[0],new_vote[1]));
	else
			votes[voter_index].second=new_vote[1];
	if (enough_vote_to_set_target())
	{
		Player* target=player_with_mejority_votes();
		set_mafia_target(target);
		announce_mafia_target(target);
		is_night_over();
	}
}
void Room::if_user_joined(string user_name)
{
	if(detail.search_player(user_name) == PLAYER_NOT_FOUND_IN_ROOM)
		throw Exp("User not joined");
}
void Room::if_player_alive(string user_name)
{
	if(players[this->search_player(user_name)]->is_dead())
		throw Exp("User already died");
}
void Room::if_detective_alive(string detective_name)
{
	if(players[this->search_player(detective_name)]->is_dead())
		throw Exp("User can not ask");
}
void Room::can_detect(string detective_name)
{
	if(players[this->search_player(detective_name)]->role != Detective)
		throw Exp("User can not ask");
}
void Room::vote(vector<string> &new_vote)
{

	if_game_has_started();
	if_user_joined(new_vote[0]);
	if_user_joined(new_vote[1]);
	if_player_alive(new_vote[0]);
	if_player_alive(new_vote[1]);
	if(don==Day)
		vote_day(new_vote);
	else 
		vote_night(new_vote);
}
void Room::if_any_vote()
{
	if(votes.size() == 0)
		throw Exp("no vote submitted");
}
void Room::end_vote()
{
	if_day();
	if_any_vote();
	Player* looser_of_election=player_with_mejority_votes();
	kill(looser_of_election);
	announce_dead(looser_of_election);
	mafia_targets.push_back(looser_of_election);
	next_round();
}
int Room::search_tasks(string name , vector<string> tasks)
{
	for (int i = 0; i < tasks.size(); ++i)
	{
		if(tasks[i]==name)
			return i;
	}
	return tasks.size();
}
void Room::if_detectve_already_asked(string detective)
{
	if(search_tasks(detective,detectives_asked) != DETECTIVE_NOT_ASKED)
		throw Exp("Detective has already asked");
}
void Room::if_night()
{
	if(don!= Night)
		throw Exp("this command is for night");
}
void Room::if_day()
{
	if(don!= Day)
		throw Exp("this command is for day");
}
void Room::if_doctor_alive(string doctor_name)
{
	if(players[this->search_player(doctor_name)]->is_dead())
		throw Exp("User can not heal");
}
void Room::if_person_alive(string patient_name)
{
	if(players[this->search_player(patient_name)]->is_dead())
		throw Exp("Person is dead");
}
void Room::can_heal(string doctor_name)
{
	if(players[this->search_player(doctor_name)]->role != Doctor)
		throw Exp("User can not heal");
}
void Room::if_doctor_already_healed(string doctor_name)
{
	if(search_tasks(doctor_name,doctors_healed) != DOCTOR_NOT_HEALED)
		throw Exp("Doctor has already healed");
}
void Room::if_silencer_alive(string silencer_name)
{
	if(players[this->search_player(silencer_name)]->is_dead())
		throw Exp("User can not silence");
}
void Room::can_silent(string silencer_name)
{
	if(players[this->search_player(silencer_name)]->role != Silencer)
		throw Exp("User can not silence");
}
void Room::if_silencer_already_silented(string silencer_name)
{
	if(search_tasks(silencer_name,silencers_silented) != SILENCER_NOT_SILENTED)
		throw Exp("Silencer has already silenced");
}
void Room::if_night_vote_ended()
{
	if(mafia_targets.size()!=1)
		throw Exp("all the mafias should vote first");
}
void Room::if_detect_ended()
{
	if(detectives_asked.size()!= alive_detectives())
		throw Exp("all the detectives should detect first");
}
void Room::if_heal_ended()
{
	if(doctors_healed.size() != alive_doctors())
		throw Exp("all the doctors should heal fisrt");
}
void Room::detect_conditions(std::string detective ,std::string suspect)
{
	if_game_has_started();
	if_night_vote_ended();
	if_user_joined(detective);
	if_user_joined(suspect);
	if_detective_alive(detective);
	if_person_alive(suspect);
	can_detect(detective);
	if_detectve_already_asked(detective);
}
void Room::detect(string detective,string suspect)
{
	detect_conditions(detective,suspect);
	players[search_player(detective)]->detect(players[search_player(suspect)]);
	detectives_asked.push_back(detective);
	is_night_over();
}
void Room::heal_conditions(std::string doctor, std::string patient)
{
	if_game_has_started();
	if_user_joined(doctor);
	if_user_joined(patient);
	if_night_vote_ended();
	if_detect_ended();
	if_doctor_alive(doctor);
	if_person_alive(patient);
	can_heal(doctor);
	if_doctor_already_healed(doctor);
}
void Room::heal(string doctor,string patient)
{
	heal_conditions(doctor,patient);
	players[search_player(doctor)]->heal(players[search_player(patient)],THIS_NIGHT);
	doctors_healed.push_back(doctor);
	is_night_over();
}
void  Room::silent_conditions(std::string silencer, std::string person)
{
	if_game_has_started();
	if_user_joined(silencer);
	if_user_joined(person);
	if_night_vote_ended();
	if_detect_ended();
	if_heal_ended();
	if_person_alive(person);
	if_silencer_alive(silencer);
	can_silent(silencer);
	if_silencer_already_silented(silencer);
}
void Room::silent(string silencer,string person)
{
	silent_conditions(silencer,person);
	players[search_player(silencer)]->silent(players[search_player(person)],NEXT_DAY);
	silencers_silented.push_back(silencer);
	is_night_over();
}
int Room::alive_villagers()
{
	int sum=0;
	for (int i = 0; i < players.size(); ++i)
	{
		if(players[i]->is_dead())
			continue;
		if(
			players[i]->role == Villager||
			players[i]->role == Doctor||
			players[i]->role == Detective||
			players[i]->role == Immortal
		  )
			sum++;
	}
	return sum;
}
void Room::get_room_state()
{
	cout<<MAFIA_STR<<SPACE<<EQUAL<<SPACE<<alive_mafias()<<endl;
	cout<<VILLAGER_STR<<SPACE<<EQUAL<<SPACE<<alive_villagers()<<endl;
}
Room::~Room()
{
	for (int i = 0; i < players.size(); ++i)
	{
		delete players[i];
	}
	for (int i = 0; i < mafia_targets.size(); ++i)
	{
		delete mafia_targets[i];
	}
}