#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../DataContainer/Table.h"
#include <Eigen/Dense>

class VolSlice {
    public:
        VolSlice(std::string modelName, double T, Eigen::VectorXd params);

        virtual Eigen::MatrixXd compute_iv(const Eigen::VectorXd& params, const Eigen::MatrixXd& K, double T, double S0, double r) const = 0;
        void save(const Eigen::MatrixXd& K, double T, double S0, double r, std::string outputFile) const;
        int calibrate(Table& mkt_slice, double S0, double r);

        double get_maturity() const {return maturity;}
        int get_n_params() const {return params.size();}
        void set_params(Eigen::VectorXd new_params) {params = new_params;}
    private:
    protected:
        std::string modelName;
        double maturity;
        Eigen::VectorXd params;
};