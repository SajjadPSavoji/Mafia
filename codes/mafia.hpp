#ifndef MAFIA_HEADER_GUARD
#define MAFIA_HEADER_GUARD
#include "player.hpp"
class MAFIA : public Player
{
public:
	 MAFIA(std::string _name , Role _role):Player(_name,_role){}
	 virtual bool is_mafia(){return true;}
	
};

#endif