#include "detective.hpp"

using namespace std;
void DETECTIVE::detect(Player* suspect)
{
	if(suspect->is_mafia())
		cout<<YES<<endl;
	else
		cout<<NO<<endl;
}