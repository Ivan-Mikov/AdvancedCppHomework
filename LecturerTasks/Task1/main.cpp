#include "manager.h"

#include <iostream>
#include <string>
#include <sstream>

void PrintHelp() {
    std::cout 
        << "                   Available Commands\n"
        << "createUser {userId} {username}    - Create new user\n"
        << "deleteUser {userId}               - Delete user\n"
        << "allUsers                          - Print list of all users\n"
        << "getUser {userId}                  - Print information about user\n"
        << "createGroup {groupId}             - Create new group\n"
        << "deleteGroup {groupId}             - Delete group\n"
        << "allGroups                         - Print list of all groups\n"
        << "getGroup {groupId}                - Print information about group\n"
        << "addUserToGroup {userId} {groupId} - Add user to the group\n"
        << "clearGroup {groupId}              - Delete all users in the group\n"
        << "help                              - Print help\n"
        << "quit                              - Close the programm" 
    << std::endl;
}

int main() {
    std::cout << "Welcome to User Management System." << std::endl;
    std::cout << "For quit print 'quit'\n";
    UserManager um;
    std::string line;
    
    int userId, groupId;
    std::string command, username;

    while (true) {

        std::cout << "> ";
        std::getline(std::cin, line);
        std::stringstream ss(line);

        if (!(ss >> command)) {
            std::cout << "Line is empty. Try again" << std::endl;
            continue;
        }

        if (command == "createUser") {
            if (ss >> userId >> username) {
                um.CreateUser(userId, username);
            } else std::cout << "Incorrect format. Write 'createUser {userId} {username}'" << std::endl;
        }
        else if (command == "deleteUser") {
            if (ss >> userId) {
                um.DeleteUser(userId);
            } else std::cout << "Incorrect format. Write 'deleteUser {userId}'" << std::endl;
        }
        else if (command == "allUsers") {
            um.AllUsers();
        }
        else if (command == "getUser") {
            if (ss >> userId) {
                um.GetUser(userId);
            } else std::cout << "Incorrect format. Write 'getUser {userId}'" << std::endl;
        }
        else if (command == "createGroup") {
            if (ss >> groupId) {
                um.CreateGroup(groupId);
            } else std::cout << "Incorrect format. Write 'createGroup {groupId}'" << std::endl;
        }
        else if (command == "deleteGroup") {
            if (ss >> groupId) {
                um.DeleteGroup(groupId);
            } else std::cout << "Incorrect format. Write 'deleteGroup {groupId}'" << std::endl;
        }
        else if (command == "allGroups") {
            um.AllGroups();
        }
        else if (command == "getGroup") {
            if (ss >> groupId) {
                um.GetGroup(groupId);
            } else std::cout << "Incorrect format. Write 'getGroup {groupId}'" << std::endl;           
        }
        else if (command == "addUserToGroup") {
            if (ss >> userId >> groupId) {
                um.AddUserToGroup(userId, groupId);
            } else std::cout << "Incorrect format. Write 'addUserToGroup {userId} {groupId}'" << std::endl;   
        }
        else if (command == "clearGroup") {
            if (ss >> groupId) {
               um.ClearGroup(groupId);
            } else std::cout << "Incorrect format. Write 'clearGroup {groupId}'" << std::endl;         
        }
        else if (command == "help") {
            PrintHelp();
        }
        else if (command == "quit") {
            break;
        }
        else {
            std::cout << "Unknown command: " << command
                << "\nFor help print 'help'" << std::endl;  
        }
    }
}
