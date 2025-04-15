#pragma once
#include <iostream>
#include "VolSlice.h"
#include "../DataContainer/Table.h"
#include <Eigen/Dense>

class SabrSlice: public VolSlice {
    public:
        SabrSlice(double T, Eigen::Vector4d params);

        Eigen::MatrixXd compute_iv(const Eigen::VectorXd& params, const Eigen::MatrixXd& K, double T, double S0, double r) const;
    private:
        static Eigen::Vector4d computeReparam(const Eigen::Vector4d& params);
        Eigen::Vector4d computeInverseReparam(const Eigen::Vector4d& params) const;
};