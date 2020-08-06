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
void panel();
bool getUser();
bool getPass();
void menu();

// Checks if user exists by checking for the users file in the userinfo directory, if so then returns false, if user doesn't exist the returns true 
bool checkUser(const std::string &user){
    boost::filesystem::path p("userinfo/"+user);
    if (boost::filesystem::exists(p)){
        std::cout << RED << "User exists.\n" << RESET;
		return false;
    }
    else{
		std::cout << GREEN << "Username available.\n\n" << RESET;
        return true;
    }
}

// Prompts user for password when registering new user using getpass() to mask input. If passwords do not match, returns false. If passwords match then userfile is created with the username and password seperated by a colon.
bool addPass(const std::string &user){
	std::string newPass1;
	std::string newPass2;
	
	while (true){

		newPass1 = getpass("Enter your password: ");

		newPass2 = getpass("Re-enter your password: ");

		if (newPass1 == newPass2){
			std::ofstream userFile ("userinfo/"+user);

			if (userFile.is_open()){
				userFile << user+":"+newPass2;
				userFile.close();
				std::cout << GREEN << "User registered!" << RESET;
			}
			else std::cerr << RED << "Unable to create user." << RESET;
			return true;
		}
		else{
			std::cout << RED << "Passwords do not match." << RESET;
			return false;
		}
	}
}

// Prompts user to enter username they wish to register then passes it to checkUser() and addPass() to register. If user is added, breaks loop and calls menu().
void reg(){
	std::string newUser;

	while (true){
		std::cout << "\nPlease enter the username you would like to register: ";
		std::cin >> newUser;

		if (checkUser(newUser)){
			addPass(newUser);
			break;
		}
	}
	menu();
}

// Checks if given user exists, if so returns true, if not returns false. If unable to open userfile, sends error message to std error 
bool getUser(const std::string &userIn)
{
		std::string userFile = "userinfo/"+userIn;
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

// Prompts user for password then checks supplied password against correct password taken from userfile of user trying to authenticate.
bool getPass(const std::string &userIn)
{
	std::string passIn;

	int logAttempts;
	logAttempts = 2;
	
	std::string userFile = "userinfo/"+userIn;
	std::ifstream authFile{userFile};
	std::string fUser,fPass;

	if (!authFile){
		std::cerr << "Error, "+ userFile + "could not be opened for reading.\n";
	}

	while (authFile){
		std::getline(authFile, fUser, ':');
		std::getline(authFile, fPass); //Use EOL as delimiter
		
		while (logAttempts >= 0){
			passIn = getpass("Enter your password: ");

			if (fPass == passIn){
				std::cout << GREEN << "Password correct!\n" << RESET;
				return true;
				panel();
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

// Prompts user for username they would like to authenticate with then supplies it to getUser() which, if it returns true breaks the loop and proceeds to pass the verified username to getPass() for authentication.
void login()
{
	std::string userIn, passIn;

	while (true){
		std::cout << "Please enter your username: ";
		std::cin >> userIn;
		
		if (getUser(userIn)){
			break;
		}
		else getUser(userIn);		
	}	
	getPass(userIn);
}	

// Administration panel/prompt given to the user once they are authenticated, supply the number corresponding to the command.
void panel()
{
	std::cout << "\n-----------------------------------------------";
	std::cout << BLUE << '\n' << R"( __          __  _                          
 \ \        / / | |                         
  \ \  /\  / /__| | ___ ___  _ __ ___   ___ 
   \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \
    \  /\  /  __/ | (_| (_) | | | | | |  __/
     \/  \/ \___|_|\___\___/|_| |_| |_|\___|)" << RESET <<"\n\n";

	std::cout << "Options:" << std::endl << "  [1]  View Changelog\n";
	std::cout << "  [2]  Add user" << std::endl;
	std::cout << "  [3]  Delete user\n" << std::endl;
	std::cout << "  [4]  Exit\n\n";	

	int cmd;
	
	while (true){
		std::cout << "$ ";
		std::cin >> cmd;

		switch(cmd){
			case 1:
				clog();
				break;
			case 2:
				addUser();
				break;
			case 3:
				delUser();
				break;
			case 4:
				std::cout << "Goodbye! Exiting...";
				exit(EXIT_SUCCESS);
				break;
		}
		
	}
}

// The 'main menu' of the program which shows at startup and when a new user has been registered, supply the number corresponding to the desired action.
void menu()
{
	int choice;
	std::cout << "-----------------------------------------------";
	std::cout << "\n\nWelcome!\n\n";
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
			reg();
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
	panel();
}
