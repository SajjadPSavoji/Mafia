#ifndef VILLAGER_HEADER_GUARD
#define VILLAGER_HEADER_GUARD
#include "player.hpp"
class VILLAGER : public Player
{
public:
	 VILLAGER(std::string _name , Role _role):Player(_name,_role){}
	 virtual bool is_mafia(){return false;}
};
	

#endif