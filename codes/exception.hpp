#ifndef EXCEPTION_DETAIL_HEADER_GUARD
#define EXCEPTION_DETAIL_HEADER_GUARD
#include <iostream> 
class Exp :public std::exception
{
public:
	Exp(std::string _message):message(_message){}
	std::string get_message();
private:
	std::string message;
	
};
std::ostream& operator<<(std::ostream& out , Exp exception);
#endif