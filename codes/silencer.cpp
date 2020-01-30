#include "silencer.hpp"

using namespace std;
void SILENCER::silent(Player* person , int next_day)
{
	person->get_silenced(next_day);
}