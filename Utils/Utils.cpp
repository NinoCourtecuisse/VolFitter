#include <iostream>
#include <fstream>
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

Eigen::VectorXd linspace(double start, double end, int num) {
    Eigen::VectorXd v(num);
    if (num == 1) {
        v(0) = start;
    } else {
        double step = (end - start) / (num - 1);
        for (int i = 0; i < num; ++i) {
            v(i) = start + i * step;
        }
    }
    return v;
}

void saveToCSV(const std::string& filename, const Eigen::MatrixXd& matrix, const std::vector<std::string>& headers) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i < headers.size(); ++i) {
            file << headers[i];
            if (i < headers.size() - 1) file << ",";
        }
        file << "\n";

        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.cols(); ++j) {
                file << matrix(i, j);
                if (j < matrix.cols() - 1) file << ",";
            }
            file << "\n";
        }
        file.close();
        std::cout << "Saved to " << filename << std::endl;
    } else {
        std::cerr << "Could not open file for writing\n";
    }
}