#ifndef PLAYER_HEADER_GUARD
#define PLAYER_HEADER_GUARD

#include <iostream>
#include <vector>

#define MAFIA_ "Mafia"
#define VILLAGER_ "Villager"
#define JOKER_ "Joker"
#define SILENCER_ "Silencer"
#define GODFATHER_ "GodFather"
#define DETECTIVE_ "Detective"
#define DOCTOR_ "Doctor"
#define IMMORTAL_ "Immortal"
#define PLAYER_ANNUONCE " is "

enum Role
{
	Mafia,
	Villager,
	Joker,
	Silencer,
	GodFather,
	Detective,
	Doctor,
	Immortal
};

class Player
{
public:
	Player (std::string _name , Role _role):name(_name),role(_role){}

	void set_life(int new_life){life=new_life;}

	Role get_role(){return role;}
	int get_healed_night(){return healed_night;}
	int get_silenced_day(){return silenced_day;}

	void get_healed(int night_number){healed_night=night_number;}
	void get_silenced(int day_number){silenced_day=day_number;}

	virtual bool is_mafia()=0;
	virtual void detect(Player* suspect){}
	virtual void heal(Player* patient , int night_number){}
	virtual void silent(Player* person , int next_day){}
	bool is_dead(){return life == 0;}
	bool is_alive(){return life > 0;}
	
	void loose_life(){life--;}
	bool can_vote_at_night();
	friend class Room;
	friend std::ostream& operator<< (std::ostream& out , Player* player);
	friend std::ostream& operator<< (std::ostream& out , std::vector<Player*> players);

protected:
	Role role;
	std::string name;
	int life = 1;
	int healed_night=0;
	int silenced_day=0; 
	
};
std::ostream& operator<< (std::ostream& out , Player* player);
std::ostream& operator<< (std::ostream& out , std::vector<Player*> players);
std::ostream& operator<< (std::ostream& out , Role role);
#endif