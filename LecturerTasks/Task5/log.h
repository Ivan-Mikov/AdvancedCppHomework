#pragma once

#include <deque>
#include <string>

enum EventType {
    LOG_NORMAL,
    LOG_WARNING,
    LOG_ERROR
};

class Event {
    std::string time_;
    EventType type_;
    std::string message_;

public:
    Event(EventType type, std::string msg);
    std::string GetTime() const { return time_; }
    EventType GetType() const { return type_; }
    std::string GetMessage() const { return message_; }
};

class Log {
    std::deque<Event> events;
    static Log* instance_ptr;
    const static unsigned int max_events = 10;

    Log() = default;
public:
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

    static Log* Instance();

    void message(EventType type, std::string msg);
    void print();
};
