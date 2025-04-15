#include <iostream>
#include <fstream>
#include <cmath>
#include "SabrSlice.h"
#include "../Utils/Optimization.h"
#include "../Utils/Utils.h"
#include <unsupported/Eigen/NonLinearOptimization>
#include <numbers>

using namespace std;
using namespace Eigen;

SabrSlice::SabrSlice(double T, Vector4d params)
    : VolSlice("sabr", T, computeReparam(params))
    {}

Vector4d SabrSlice::computeReparam(const Vector4d& params) {
    double beta = params(0);
    double alpha = params(1);
    double rho = params(2);
    double gamma = params(3);

    return Vector4d(
        tan((2 * beta - 1) * numbers::pi / 2),
        log(alpha),
        tan(rho * std::numbers::pi / 2.0),
        log(gamma)
    );
}

Vector4d SabrSlice::computeInverseReparam(const Eigen::Vector4d& params) const
{
    double beta = (atan(params(0)) * (2 / numbers::pi) + 1) / 2.0;
    double alpha = exp(params(1));
    double rho = atan(params(2)) * (2 / numbers::pi);
    double gamma = exp(params(3));

    return Vector4d(beta, alpha, rho, gamma);
}

Eigen::MatrixXd SabrSlice::compute_iv(const VectorXd& params, const MatrixXd& K, double T, double S0, double r) const
{
    Vector4d real_params = computeInverseReparam(params);
    double beta = real_params(0);
    double alpha = real_params(1);
    double rho = real_params(2);
    double gamma = real_params(3);

    double F = exp(r * T) * S0;
    ArrayXd Karr = K.array();
    ArrayXd logMoney = (F * Karr.inverse()).log();
    ArrayXd z = gamma * (F * Karr).pow((1.0 - beta) / 2.0) * logMoney / alpha;
    ArrayXd x = (((1.0 - 2 * rho * z + z.pow(2)).sqrt() + z - rho) / (1 - rho)).log();

    ArrayXd iv = alpha * z * (
        (F * Karr).pow((1 - beta) / 2.0) 
        * (1 + pow(1 - beta, 2) * logMoney.pow(2) / 24 + pow(1 - beta, 4) * logMoney.pow(4) / 1920)
        * x
    ).inverse() 
    * (1 + (
        pow(1 - beta, 2) * pow(alpha, 2) * (F * Karr).pow(1 - beta).inverse() / 24
        + rho * beta * gamma * alpha * (F * Karr).pow((1 - beta) / 2).inverse() / 4
        + (2 - 3 * rho * rho) * gamma * gamma / 24
    ) * T);
    return iv.matrix();
}
