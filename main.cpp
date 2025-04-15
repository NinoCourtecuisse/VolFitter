#include <iostream>
#include <fstream>
#include "DataContainer/Table.h"
#include "VolSlice/FlatSlice.h"
#include "Utils/Utils.h"
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    string fileName("Data/Input/August.csv");
    Table table(fileName);

    double maturity(1.0);
    FlatSlice slice(maturity);
    slice.calibrate(table);

    string outputFile("Data/Output/output.csv");
    double min_strike = table.getMin(string("Strike"));
    double max_strike = table.getMax(string("Strike"));
    int N = 10;
    VectorXd K = linspace(min_strike, max_strike, N);
    slice.save(K, maturity, outputFile);

    return 0;
}