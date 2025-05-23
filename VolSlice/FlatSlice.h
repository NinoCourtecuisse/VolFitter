#pragma once
#include <iostream>
#include "VolSlice.h"
#include "../DataContainer/Table.h"
#include <Eigen/Dense>

class FlatSlice: public VolSlice {
    public:
        FlatSlice(double T, double sigma);

        Eigen::MatrixXd compute_iv(const Eigen::VectorXd& params, const Eigen::MatrixXd& K, double T, double S0, double r) const;
    private:
};
