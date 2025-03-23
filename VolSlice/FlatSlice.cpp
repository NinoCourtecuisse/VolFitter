#include <iostream>
#include <cmath>
#include "FlatSlice.h"

using namespace std;
using namespace Eigen;

FlatSlice::FlatSlice(double T, double sigma)
    : VolSlice(string("flat"), T, vector<double>({sigma}))
    {}

MatrixXd FlatSlice::compute_iv(const MatrixXd& K, double T)
{
    return MatrixXd::Constant(K.rows(), K.cols(), params[0]);
}

void FlatSlice::calibrate(Table& mkt_slice)
{   
    MatrixXd strikes(mkt_slice.getColumn(string("Strike")));
    MatrixXd iv_mkt(mkt_slice.getColumn(string("IV")));
    MatrixXd iv_model(this->compute_iv(strikes, maturity));
    
    cout << iv_mkt - iv_model << endl;
}