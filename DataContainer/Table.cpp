#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Table.h"
#include "../Utils/Utils.h"
#include <cmath>
using namespace std;
using namespace Eigen;

Table::Table(string fileName)
    {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error opening file: " << fileName << endl;
            return;
        }

        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            string column;
            while (getline(ss, column, ',')) {
                header.push_back(trim(column));
            }
        }

        vector<vector<double>> data_vector;
        while (getline(file, line)) {
            stringstream ss(line);
            string value;
            vector<double> row;
            while (getline(ss, value, ',')) {
                row.push_back(stod(value));
            }
            data_vector.push_back(row);
        }

        dim[0] = data_vector.size();
        dim[1] = data_vector.empty() ? 0 : data_vector[0].size();

        file.close();
        data = vectorToMatrix(data_vector);
    }

void Table::printHead(int row) const
{
    row = min(row, static_cast<int>(data.size()));
    cout << data(seqN(0, row), Eigen::all) << endl;
}

MatrixXd Table::getColumn(string col_name) const
{
    vector<string>::const_iterator it = find(header.begin(), header.end(), col_name);
    if (it != header.end()) {
        int idx = distance(header.begin(), it);
        return data(all, idx);
    } else {
        cerr << "Column " << col_name << " is not in the dataset." << endl;
        return MatrixXd(0, 0);
    }
}