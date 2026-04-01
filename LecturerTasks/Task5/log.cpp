#include "log.h"

#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

std::string getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);
    
    std::stringstream ss;
    ss << std::put_time(localTime, "%H:%M:%S");
    return ss.str();
}

Event::Event(EventType type, std::string message) {
    time_ = getTime();
    type_ = type;
    message_ = message;
}

Log* Log::instance_ptr = nullptr;

Log* Log::Instance() {
    if (!instance_ptr) {
        instance_ptr = new Log();
    }
    return instance_ptr;
}

void Log::message(EventType type, std::string msg) {
    Event event(type, msg);
    events.push_back(event);
    if (events.size() > max_events)
        events.pop_front();
}

void Log::print() {
    for (auto event : events) {
        std::cout << '[' << event.GetTime() << "] [";
        switch (event.GetType()) {
            case EventType::LOG_NORMAL:
                std::cout << "Normal";
                break;
            case EventType::LOG_WARNING:
                std::cout << "Warning";
                break;
            case EventType::LOG_ERROR:
                std::cout << "Error";
                break;
        }
        std::cout << "] " << event.GetMessage() << std::endl;
    }
}
