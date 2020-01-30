#include "player.hpp"

using namespace std;

#define IMMORTAL_LIFE 2

std::ostream& operator<< (std::ostream& out , Role role)
{
		 if(role == Mafia)           cout << MAFIA_;    
 	else if(role == Villager)        cout << VILLAGER_;    
 	else if(role == Joker)           cout << JOKER_;       
 	else if(role == Silencer)        cout << SILENCER_;    
 	else if(role == GodFather)       cout << GODFATHER_;   
 	else if(role == Detective)       cout << DETECTIVE_;   
 	else if(role == Doctor)          cout << DOCTOR_;      
 	else if(role == Immortal)        cout << IMMORTAL_; 
 	return out;  
}
std::ostream& operator<< (std::ostream& out , Player* player)
{
	cout << player->name << PLAYER_ANNUONCE <<player->get_role();
	return out;
}
std::ostream& operator<< (std::ostream& out , std::vector<Player*> players)
{
	for (int i = 0; i < players.size(); ++i)
	{
		cout<<players[i]<<endl;
	}
	return out;
}
bool Player::can_vote_at_night()
{
	if( 
		role == Mafia ||
		role ==GodFather||
		role == Silencer
	  )
		return true;
	return false;
}