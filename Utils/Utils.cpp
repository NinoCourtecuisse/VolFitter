#include <iostream>
#include "Utils.h"

using namespace std;
using namespace Eigen;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \r");
    if (first == string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

MatrixXd vectorToMatrix(const vector<vector<double>>& vec) {
    if (vec.empty()) {
        return MatrixXd(0, 0);
    }
    size_t rows = vec.size();
    size_t cols = vec[0].size();
    MatrixXd matrix(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        if (vec[i].size() != cols) {
            cerr << "Error: All rows must have the same number of columns." << endl;
            return MatrixXd(0, 0);
        }
        for (size_t j = 0; j < cols; ++j) {
            matrix(i, j) = vec[i][j];
        }
    }
    return matrix;
}