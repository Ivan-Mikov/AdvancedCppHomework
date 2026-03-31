#include "manager.h"

#include <iostream>
#include <optional>
#include <iomanip>

void UserManager::CreateUser(int userId, std::string username) {
    if (users.find(userId) == users.end())
        users[userId] = new User(userId, username);
    else std::cout << "There is already user with this ID" << std::endl;
}

void UserManager::DeleteUser(int userId) {
    std::optional<int> groupId = users[userId]->GetGroupId();
    if (groupId.has_value()) 
        groups[groupId.value()]->DeleteUser(userId);
    delete users[userId];
    users.erase(userId);
}

void UserManager::AllUsers() {
    std::cout << "Users list:\n" 
        << std::left << std::setw(10) << "Id"        
        << std::left << std::setw(20) << "Username"
        << std::right << std::setw(15) << "Group" 
        << std::endl;

    for (auto user : users) {
        GetUser(user.first);
    }
}

void UserManager::GetUser(int userId) {
    if (users.find(userId) != users.end()) {
        auto user = users[userId];
        std::cout << std::left << std::setw(10) << user->GetId()        
            << std::left << std::setw(20) << user->GetUsername()
            << std::right << std::setw(15);

        auto groupId = user->GetGroupId();
        if (groupId.has_value())
            std::cout << groupId.value() << std::endl;
        else
            std::cout << "No group" << std::endl;
    } else std::cout << "There is no users with this ID" << std::endl;
}

void UserManager::CreateGroup(int groupId) {
    if (groups.find(groupId) == groups.end())
        groups[groupId] = new Group(groupId);
    else std::cout << "There is already group with this ID" << std::endl;
}

void UserManager::DeleteGroup(int groupId) {
    for (auto u : users) {
        auto user = u.second;
        if (user->GetGroupId() == groupId)
            user->SetGroupId(std::nullopt);
    }
    delete groups[groupId];
    groups.erase(groupId);
}

void UserManager::AllGroups() {
    for (auto group : groups) {
        GetGroup(group.first);
    }
}

void UserManager::GetGroup(int groupId) {
    if (groups.find(groupId) != groups.end()) {
        std::cout << "ID: " << groupId << "\nUsers in group:" << std::endl;
        if (groups[groupId]->UsersCount() == 0)
            std::cout << "No users in the group" << std::endl;
        else {
            std::cout << std::left << std::setw(10) << "Id"        
                << std::left << std::setw(20) << "Username"
                << std::right << std::setw(15) << "Group" 
                << std::endl;
            for (auto userId : groups[groupId]->GetUsers()) {
                GetUser(userId);
            }
        }
    } else std::cout << "There is no group with this ID" << std::endl;
}

// Я решил добавить еще пару методов
void UserManager::AddUserToGroup(int userId, int groupId) {
    if (groups.find(groupId) == groups.end()) {
        std::cout << "There is no group with this ID" << std::endl;
        return;
    }
    if (users.find(userId) == users.end()) {
        std::cout << "There is no user with this ID" << std::endl;
        return;
    }
    groups[groupId]->AddUser(userId);
    users[userId]->SetGroupId(groupId);
}

void UserManager::ClearGroup(int groupId) {
    if (groups.find(groupId) != groups.end()) {
        for (auto userId : groups[groupId]->GetUsers()) {
            users[userId]->SetGroupId(std::nullopt);
            groups[groupId]->DeleteUser(userId);
        }
    } else std::cout << "There is no group with this ID" << std::endl;
}
