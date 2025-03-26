#include <iostream>
#include <cmath>
#include "FlatSlice.h"
#include "../Utils/Optimization.h"
#include <unsupported/Eigen/NonLinearOptimization>

using namespace std;
using namespace Eigen;

FlatSlice::FlatSlice(double T, double sigma)
    : VolSlice(string("flat"), T, VectorXd::Constant(1, 1, sigma))
    {}

MatrixXd FlatSlice::compute_iv(const MatrixXd& K, double T) const
{
    return MatrixXd::Constant(K.rows(), K.cols(), params[0]);
}

void FlatSlice::calibrate(Table& mkt_slice)
{   
    LstqFunctor functor(mkt_slice, *this);
    Eigen::NumericalDiff<LstqFunctor> numDiff(functor);
    Eigen::LevenbergMarquardt<Eigen::NumericalDiff<LstqFunctor>,double> lm(numDiff);
    lm.parameters.maxfev = 100;
    lm.parameters.xtol = 1.0e-10;
    cout << params << endl;
    int info = lm.minimize(params);
    cout << params << endl;

    VectorXd strikes(mkt_slice.getColumn(string("Strike")));
    VectorXd iv_mkt(mkt_slice.getColumn(string("IV")));
    VectorXd iv_model(this->compute_iv(strikes, maturity));
    
    // cout << iv_mkt - iv_model << endl;
    cout << functor.inputs() << endl;
    cout << functor.values() << endl;
}