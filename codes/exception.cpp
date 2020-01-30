#include "exception.hpp"

using namespace std;
ostream& operator<<(ostream& out , Exp exception)
{
	out<<exception.get_message();
	return out;
}
string Exp::get_message(){return message;}