#include "doctor.hpp"

using namespace std;
void DOCTOR::heal(Player* patient , int night_number)
{
	patient->get_healed(night_number);
}