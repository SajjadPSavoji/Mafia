#ifndef IMMORTAL_HEADER_GUARD
#define IMMORTAL_HEADER_GUARD
#include "villager.hpp"
class IMMORTAL : public VILLAGER
{
public:
	IMMORTAL(std::string _name , Role _role):VILLAGER(_name,_role){life=2;}
	virtual bool is_mafia(){return false;}
	
};

#endif