#include <vector>
#include <iostream>
#include <string>
#include <optional>
#include <sstream>
#include <iomanip>

class CP {
    std::string name;
    double latitude;
    double longitude;
    std::optional<double> fine = std::nullopt;

public:
    CP(std::string n, double lat, double lon, std::optional<double> f = std::nullopt)
        : name(n), latitude(lat), longitude(lon), fine(f) {}
    
    std::string Name() const { return name; }
    double Latitude() const { return latitude; }
    double Longitude() const { return longitude; }
    bool IsOptional() const { return (fine != std::nullopt); }
    double Fine() const { return fine.value_or(0); }
};


class Builder {
public:
    virtual void ProcessRequired(const CP& cp) = 0;
    virtual void ProcessOptional(const CP& cp) = 0;
};


class Director {
public:
    void build(const std::vector<CP>& checkpoints, Builder* builder) {
        for (auto cp : checkpoints) {
            if (cp.IsOptional())
                builder->ProcessOptional(cp);
            else
                builder->ProcessRequired(cp);
        }
    }
};


// Конкретные реализации:
class TextBuilder : public Builder {
    std::stringstream result;
    int serial_number;

    const int W_NUM = 4;
    const int W_NAME = 20;
    const int W_COORD = 15;
    const int W_FINE = 10;

    void PrintCP(const CP& cp, std::string fineText) {
        result << std::left << std::fixed << std::setprecision(5)
               << std::setw(W_NUM)   << serial_number++
               << std::setw(W_NAME)  << cp.Name()
               << std::setw(W_COORD) << cp.Latitude()
               << std::setw(W_COORD) << cp.Longitude()
               << std::setw(W_FINE)  << fineText << "\n";
    }
    
public:
    TextBuilder() {
        Reset();
        result << std::left 
               << std::setw(W_NUM)   << "#"
               << std::setw(W_NAME)  << "NAME"
               << std::setw(W_COORD) << "LATITUDE"
               << std::setw(W_COORD) << "LONGITUDE"
               << std::setw(W_FINE)  << "FINE" << "\n";
        
        result << std::string(W_NUM + W_NAME + W_COORD * 2 + W_FINE, '-') << "\n";
    }

    void ProcessRequired(const CP& cp) override {
        PrintCP(cp, "SS Void");
    }

    void ProcessOptional(const CP& cp) override {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3) << cp.Fine() << "h";
        PrintCP(cp, ss.str());
    }

    void Reset() {
        result.str("");
        result.clear();
        serial_number = 1;
    }

    std::string GetResult() const { return result.str(); }
};


class SumFineBuilder : public Builder {
    double result;
    
public:
    SumFineBuilder() {
        result = 0;
    }

    void ProcessRequired(const CP& cp) override {
        return;
    }

    void ProcessOptional(const CP& cp) override {
        result += cp.Fine();
    }

    void Reset() {
        result = 0;
    }

    double GetResult() const { return result; }
};


int main() {
    std::vector<CP> route;
    route.emplace_back("Start Gate", 55.7558, 37.6173); 
    route.emplace_back("River Crossing", 55.8012, 37.7015);
    route.emplace_back("Deep Forest", 55.9123, 37.8540);
    route.emplace_back("Mountain Pass", 56.1055, 38.1234);
    route.emplace_back("Finish Line", 56.2500, 38.3000);
    route.emplace_back("Hidden Cave", 55.7800, 37.6500, 1.5);
    route.emplace_back("Old Mill", 55.8500, 37.7500, 0.5);
    route.emplace_back("Swamp Path", 55.9500, 37.9000, 2.0);
    route.emplace_back("Eagle Rock", 56.0500, 38.0000, 1.0);
    route.emplace_back("Sandy Hill", 56.1500, 38.2000, 0.75);

    Director director;
    TextBuilder tb;
    SumFineBuilder sfb;

    director.build(route, &tb);
    director.build(route, &sfb);

    std::cout << "First builder result:\n" << tb.GetResult();
    std::cout << "Second builder result: " << sfb.GetResult();
}