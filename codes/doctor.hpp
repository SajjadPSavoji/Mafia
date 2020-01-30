#ifndef DOCTOR_HEADER_GUARD
#define DOCTOR_HEADER_GUARD
#include "villager.hpp"
class DOCTOR: public VILLAGER
{
public:
	DOCTOR(std::string _name , Role _role):VILLAGER(_name,_role){}
	virtual bool is_mafia(){return false;}
	virtual void heal(Player* patient , int night_number);	
};

#endif