#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <vector>

std::string trim(const std::string& str);
Eigen::MatrixXd vectorToMatrix(const std::vector<std::vector<double>>& vec);
Eigen::VectorXd linspace(double start, double end, int num);
void saveToCSV(const std::string& filename, const Eigen::MatrixXd& matrix, const std::vector<std::string>& headers);