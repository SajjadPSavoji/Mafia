#include <iostream>

#include "god.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	God god("khoda");
	string command_line;
	vector<string> command_splited;
	while(getline(cin, command_line))
	{
		get_command(command_line,command_splited);
		try
		{
			execute_command(command_splited , god);
		}catch(Exp e)
		{
			cout<<e<<endl;
		}
	}
}