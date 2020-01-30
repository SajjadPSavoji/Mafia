#ifndef DETECTIVE_HEADER_GUARD
#define DETECTIVE_HEADER_GUARD
#include "villager.hpp"

#define YES "Yes"
#define NO "No"
class DETECTIVE: public VILLAGER
{
public:
	DETECTIVE(std::string _name , Role _role):VILLAGER(_name,_role){}
	virtual bool is_mafia(){return false;}
	virtual void detect(Player* suspect);
};

#endif