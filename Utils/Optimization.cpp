#include <iostream>
#include "Optimization.h"

using namespace std;
using namespace Eigen;

/*
int Functor::operator()(const VectorXd &x, VectorXd &fvec) const {
    vol_slice.set_params(x);
    VectorXd iv_market = observed_data.getColumn(string("IV"));
    VectorXd strikes = observed_data.getColumn(string("Strike"));
    VectorXd iv_model = vol_slice.compute_iv(strikes, vol_slice.get_maturity());
    fvec = iv_model - iv_market;
    return 0;
}
*/