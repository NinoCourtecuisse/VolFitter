#include <iostream>
#include <fstream>
#include <cmath>
#include "FlatSlice.h"
#include "../Utils/Optimization.h"
#include "../Utils/Utils.h"
#include <unsupported/Eigen/NonLinearOptimization>

using namespace std;
using namespace Eigen;

FlatSlice::FlatSlice(double T, double sigma)
    : VolSlice(string("flat"), T, VectorXd::Constant(1, 1, sigma))
    {}

MatrixXd FlatSlice::compute_iv(const VectorXd& params, const MatrixXd& K, double T, double S0, double r) const
{
    return MatrixXd::Constant(K.rows(), K.cols(), params[0]);
}
