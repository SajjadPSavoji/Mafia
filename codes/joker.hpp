#ifndef JOKER_HEADER_GUARD
#define JOKER_HEADER_GUARD
#include "player.hpp"
class JOKER:public Player
{
public:
	JOKER(std::string _name , Role _role):Player(_name,_role){}
	virtual bool is_mafia(){return false;}
	
};
#endif