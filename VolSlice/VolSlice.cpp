#include <iostream>
#include "VolSlice.h"
using namespace std;

VolSlice::VolSlice(string modelName_, double T, vector<double> params_)
    : modelName(modelName_), maturity(T), params(params_)
    {}