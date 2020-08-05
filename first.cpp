#include <iostream>
#include <fstream>
#include <string>
#include "commands.h"
#include <stdlib.h>
#include <boost/filesystem.hpp>

#define RESET     "\033[0m"
#define UNDERLINE "\033[4m"
#define GREEN	  "\033[32m"
#define RED       "\033[31m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"

void login();
void prompt();
bool getUser();
bool getPass();

bool checkUser(const std::string &userFile){
    boost::filesystem::path p("userinfo/"+userFile+".txt");
    if (boost::filesystem::exists(p)){
        return true;
    }
    else{
        return false;
    }
}

void reg(){
	std::string newUser;
	std::string newPass1;
	std::string newPass2;
	boost::filesystem::path infoDir("userinfo");

	std::cout << "Please enter the username you would like to register: ";
	std::cin >> newUser;

	if (checkUser(newUser)){
		
	}

}

bool getUser(const std::string &userIn)
{
		std::string userFile = "userinfo/"+userIn+".txt";
		std::ifstream authFile{userFile};
		std::string fUser;

		if (!authFile){
			std::cerr << "Error, "; 
			std::cerr << userFile <<  "could not be opened for reading.\n";
		}

		while (authFile){
			std::getline(authFile, fUser, ':' ); //Use ':' as a delimiter
			if (fUser == userIn){
				std::cout << GREEN << "Valid username.\n" << RESET << std::endl;
				return true;
			}
			else{
				std::cout << RED << "\nInavlid username. Please try again.\n" << RESET << std::endl;
				return false;
			}
		}	
}


bool getPass(const std::string &userIn)
{
	std::string passIn;

	int logAttempts;
	logAttempts = 2;
	
	std::string userFile = "userinfo/"+userIn+".txt";
	std::ifstream authFile{userFile};
	std::string fUser,fPass;

	if (!authFile){
		std::cerr << "Error, "+ userFile + "could not be opened for reading.\n";
	}

	while (authFile){
		std::getline(authFile, fUser, ':');
		std::getline(authFile, fPass); //Use EOL as delimiter
		
		while (logAttempts >= 0){
			std::cout << "Enter your password: ";
			std::cin >> passIn;

			if (fPass == passIn){
				std::cout << GREEN << "Password correct!\n" << RESET;
				return true;
				prompt();
			}
			else{
				switch(logAttempts){
					case 2:
						std::cout << YELLOW << "Incorrect password. Try again" << RESET << std::endl;
						std::cout << YELLOW << logAttempts <<" attempts remaining.\n\n" << RESET;
						logAttempts--;
						break;
					case 1:
						std::cout << RED << "Incorrect password. Try again" << RESET << std::endl;
						std::cout << RED << logAttempts <<" attempts remaining.\n\n" << RESET;
						logAttempts--;
						break;
					case 0:
						std::cout << RED << "Too many failed attempts. Exiting..." << RESET;
						exit(EXIT_FAILURE);
						break;
				}
			}
		}
	}
}




void login()
{
	std::string userIn, passIn;

	while (true){
		std::cout << "Please enter your username: ";
		std::cin >> userIn;
		
		if (getUser(userIn)){
			break;
		}
		else{
			getUser(userIn);
		}
		
	}
	
	getPass(userIn);
}	


void prompt()
{
	std::cout << BLUE << '\n' << R"( __          __  _                          
 \ \        / / | |                         
  \ \  /\  / /__| | ___ ___  _ __ ___   ___ 
   \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \
    \  /\  /  __/ | (_| (_) | | | | | |  __/
     \/  \/ \___|_|\___\___/|_| |_| |_|\___|)" << RESET <<"\n\n";

	std::cout << "Options:" << std::endl << "  [1]  View Changelog\n";
	std::cout << "  [2]  Exit\n\n";

	int cmd;
	
	while (true){
		std::cout << "$ ";
		std::cin >> cmd;

		switch(cmd){
			case 1:
				clog();
				break;
			case 2:
				std::cout << "Goodbye! Exiting...";
				exit(EXIT_SUCCESS);
				break;
		}
		
	}
}

void menu()
{
	int choice;
	std::cout << "Welcome!\n\n";
	std::cout << "[1] To login with an existing user.\n";
	std::cout << "[2] To register a new user.\n";
	std::cout << "[3] To exit.\n";
	std::cout << "\nSelect what you wish to do: ";
	std::cin >> choice;
	std::cout << '\n';

	switch (choice){
		case 1:
			login();
			break;
		case 2:
//			register();
			break;
		case 3:
			std::cout << "Goodbye!";
			exit(EXIT_SUCCESS);
			break;
	}
}



int main()
{	
	menu();
	prompt();
}