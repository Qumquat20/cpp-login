#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <fstream>


void clog()
{
	using namespace std;

	string line;

	ifstream changelog("changelog.txt");

	if (!changelog){
		cout << "Could not open changelog file.";
	}

	while (changelog){
		getline(changelog, line);
		cout << line << endl;
	}
}



#endif