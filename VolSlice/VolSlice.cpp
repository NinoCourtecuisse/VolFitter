#include <iostream>
#include "VolSlice.h"
#include "../Utils/Utils.h"
#include "../Utils/Optimization.h"
#include <unsupported/Eigen/NonLinearOptimization>

using namespace std;
using namespace Eigen;

VolSlice::VolSlice(string modelName_, double T, VectorXd params_)
    : modelName(modelName_), maturity(T), params(params_)
    {}

void VolSlice::save(const Eigen::MatrixXd& K, double T, double S0, double r, string outputFile) const
{
    VectorXd iv_model(this->compute_iv(params, K, maturity, S0, r));
    MatrixXd outputMat(K.size(), 2);
    outputMat.col(0) = K;
    outputMat.col(1) = iv_model;
    vector<string> header({"Strike", "IV"});
    saveToCSV(outputFile, outputMat, header);
}

int VolSlice::calibrate(Table& mkt_slice, double S0, double r)
{   
    LstqFunctor functor(mkt_slice, *this, S0, r);
    Eigen::NumericalDiff<LstqFunctor> numDiff(functor);
    Eigen::LevenbergMarquardt<Eigen::NumericalDiff<LstqFunctor>,double> lm(numDiff);
    int info = lm.minimize(params);
    return info;
}