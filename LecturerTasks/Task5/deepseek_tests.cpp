#include "log.h"

#include <thread>
#include <chrono>

int main() {
    Log* log = Log::Instance();
    
    const char* messages[] = {
        "Starting application",
        "Loading configuration",
        "Loading modules",
        "Initializing database",
        "Database connected",
        "Loading user data",
        "User data loaded",
        "Starting network services",
        "Network services started",
        "Processing request #1",
        "Processing request #2",
        "Processing request #3",
        "High memory usage detected",
        "Cleaning up resources",
        "Saving state",
        "State saved",
        "Shutting down services",
        "Closing connections",
        "Saving logs",
        "Application terminated"
    };
    
    for (int i = 0; i < 20; i++) {
        // Чередуем типы сообщений
        EventType type;
        if (i < 15) {
            type = LOG_NORMAL;  // Первые 15 - нормальные
        } else if (i < 18) {
            type = LOG_WARNING;  // Следующие 3 - предупреждения
        } else {
            type = LOG_ERROR;    // Последние 2 - ошибки
        }
        
        log->message(type, messages[i]);
        
        // Задержка 500 мс между сообщениями
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    log->print();
    
    return 0;
}