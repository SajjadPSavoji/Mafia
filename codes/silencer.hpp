#ifndef SILENCER_HEADER_GUARD
#define SILENCER_HEADER_GUARD
#include "mafia.hpp"
class SILENCER: public MAFIA
{
public:
	SILENCER(std::string _name , Role _role):MAFIA(_name,_role){}
	virtual bool is_mafia(){return true;}
	virtual void silent(Player* person , int next_day);
	
};

#endif