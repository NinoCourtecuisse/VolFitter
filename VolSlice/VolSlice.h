#include <iostream>
#include <string>
#include <vector>

class VolSlice {
    public:
        VolSlice(std::string modelName, double T, std::vector<double> params);
    private:
    protected:
        std::string modelName;
        double maturity;
        std::vector<double> params;
};