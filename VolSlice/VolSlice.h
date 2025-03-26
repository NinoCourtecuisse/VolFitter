#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>

class VolSlice {
    public:
        VolSlice(std::string modelName, double T, Eigen::VectorXd params);

        virtual Eigen::MatrixXd compute_iv(const Eigen::MatrixXd& K, double T) const = 0;

        double get_maturity() const {return maturity;}
        int get_n_params() const {return params.size();}
        void set_params(Eigen::VectorXd new_params) {params = new_params;}
    private:
    protected:
        std::string modelName;
        double maturity;
        Eigen::VectorXd params;
};