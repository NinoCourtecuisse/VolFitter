#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <Eigen/Dense>

class Table {
    public:
        Table(std::string fileName);

        void printHead(int row = 5) const;
        std::vector<std::string> getHeader() const {return header;}
        Eigen::MatrixXd getColumn(std::string col_name) const;
    private:
        std::array<int, 2> dim;
        std::vector<std::string> header;
        Eigen::MatrixXd data;
    protected:
};