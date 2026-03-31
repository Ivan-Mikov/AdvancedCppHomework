#pragma once

#include <string>
#include <optional>
#include <unordered_set>

class User {
    const int id;
    std::string username;
    std::optional<int> groupId = std::nullopt;

public:
    User(int id, std::string username) : id(id), username(username) { }

    // Запрещаем копирование, т.к. не хотим 2 пользователя с одним id
    User(const User& rhs) = delete;
    User& operator=(const User& rhs) = delete;
    User(User&& rhs) = default;
    User& operator=(User&& rhs) = default;
    
    int GetId() const { return id; }
    std::string GetUsername() const { return username; }
    std::optional<int> GetGroupId() const { return groupId; }
    void SetGroupId(std::optional<int> newGroupId) { groupId = newGroupId; }
};

class Group {
    const int id;
    std::unordered_set<int> users;
public:
    Group(int id) : id(id) { }

    // Запрещаем копирование, т.к. не хотим 2 группы с одним id
    Group(const Group& rhs) = delete;
    Group& operator=(const Group& rhs) = delete;
    Group(Group&& rhs) = default;
    Group& operator=(Group&& rhs) = default;

    int GetId() const { return id; }
    const std::unordered_set<int>& GetUsers() const { return users; }

    void AddUser(int userId) { users.insert(userId); }
    void DeleteUser(int userId) { users.erase(userId); }
    int UsersCount() { return users.size(); }
};
