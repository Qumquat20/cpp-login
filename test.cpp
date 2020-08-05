#include <boost/filesystem.hpp>
#include <iostream>

void checkUser(const std::string &userFile){
    boost::filesystem::path p("userinfo/"+userFile+".txt");
    if (boost::filesystem::exists(p)){
        std::cout << "Yo\n"<<p;
    }
    else{
        std::cout << "Doesn't exist";
        std::cout << p;
    }
}

int main(){
    std::string user = "admin";
    checkUser(user);
}