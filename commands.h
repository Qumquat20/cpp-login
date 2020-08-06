#ifndef COMMANDS_H
#define COMMANDS_H

#define RESET     "\033[0m"
#define GREEN	  "\033[32m"
#define RED       "\033[31m"

#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <cstdio>


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

void addUser()
{
	std::string newUser;
	std::string newPass;

	std::cout << "\nEnter the name of the user you would like to add: ";
	std::cin >> newUser;
		
	boost::filesystem::path p("userinfo/"+newUser);
    if (boost::filesystem::exists(p)){
        std::cout << RED << "User exists.\n" << RESET;
    }
	else{
		std::ofstream userFile("userinfo/"+newUser);

		if (!userFile){
			std::cerr << RED <<"Error, userinfo/"+newUser+" cannot be opened for writing.\n" << RESET;
		}
		else{
			std::cout << GREEN << "Username available.\n\n" << RESET;
			newPass = getpass("\nEnter the password you would like for this account: ");

			userFile << newUser+":"+newPass;
			userFile.close();

			std::cout << GREEN << "User added!\n\n" << RESET;
		}
	}
}

void delUser()
{
	std::string user;

	std::cout << "\nEnter the user you would like to delete: ";
	std::cin >> user;

	boost::filesystem::path p("userinfo/"+user);
	if (boost::filesystem::exists(p)){
		boost::filesystem::remove(p);
		std::cout << GREEN << "User deleted succesfully.\n\n" << RESET;
	}
	else if(!boost::filesystem::exists(p)) std::cerr << "User does not exist.\n\n";
	else{
		std::cerr << "User could not be deleted.\n\n";
	}		
}

#endif