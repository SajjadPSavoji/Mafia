#ifndef GOD_FATHER_HEADER_GUARD
#define GOD_FATHER_HEADER_GUARD
#include "mafia.hpp"
class GODFATHER : public MAFIA
{
public:
	 GODFATHER(std::string _name , Role _role):MAFIA(_name,_role){}
	 virtual bool is_mafia(){return false;}
	
};

#endif