#pragma once
#include <iostream>
#include "VolSlice.h"
#include "../DataContainer/Table.h"
#include <Eigen/Dense>

class FlatSlice: public VolSlice {
    public:
        FlatSlice(double T, double sigma = 0.2);

        Eigen::MatrixXd compute_iv(const Eigen::MatrixXd& K, double T) const;
        void calibrate(Table& mkt_slice);
    private:
};