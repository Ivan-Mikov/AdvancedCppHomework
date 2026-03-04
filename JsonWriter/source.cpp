#include <fstream>
#include <string>

class JsonWriter {
    std::ofstream file;
    bool first;
public:
    JsonWriter(const std::string& filename) : file(filename), first(true) { 
        file << "{\n  ";
    }

    JsonWriter(const JsonWriter& rhs) = delete;
    JsonWriter& operator=(const JsonWriter& rhs) = delete;

    JsonWriter(JsonWriter&& rhs) = default;
    JsonWriter& operator=(JsonWriter&& rhs) = default;

    ~JsonWriter() {
        file << "\n}\n";
        file.close();
    }

    void Add(const std::string& key, const::std::string& value) {
        if (first) {
            file << "\"" << key << "\": \"" << value << "\"";
            first = false;
        } else {
            file << ",\n  \"" << key << "\": \"" << value << "\"";
        }
    }
};

int main() {
    JsonWriter json("data.json");
    json.Add("name", "Ivan");
    json.Add("age", "19");
    json.Add("group", "Б12-414");
}