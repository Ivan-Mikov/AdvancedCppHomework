#pragma once

#include "user.h"

#include <unordered_map>
#include <string>

class UserManager {
    std::unordered_map<int, User*> users;
    std::unordered_map<int, Group*> groups;
    
public:
    void CreateUser(int userId, std::string username);
    void DeleteUser(int userId);
    void AllUsers();
    void GetUser(int userId);
    void CreateGroup(int groupId);
    void DeleteGroup(int groupId);
    void AllGroups();
    void GetGroup(int groupId);

    // Я решил добавить еще пару методов
    void AddUserToGroup(int userId, int groupId);
    void ClearGroup(int groupId);
};