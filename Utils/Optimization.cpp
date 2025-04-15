#include <iostream>
#include "Optimization.h"

using namespace std;
using namespace Eigen;

LstqFunctor::LstqFunctor(const Table& observed, VolSlice& slice, double S0, double r)
    :   Functor<double>(slice.get_n_params(), observed.get_n_data()),
        mkt_strikes(observed.getColumn("Strike")), 
        mkt_iv(observed.getColumn("IV")), S0(S0), r(r), vol_slice(slice) 
        {}

int LstqFunctor::operator()(const Eigen::VectorXd &z, Eigen::VectorXd &fvec) const 
{
    Eigen::MatrixXd iv_model = vol_slice.compute_iv(z, mkt_strikes, vol_slice.get_maturity(), S0, r);
    fvec = iv_model - mkt_iv;
    return 0;
}
