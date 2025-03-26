#include <iostream>
#include <Eigen/Dense>
#include "../VolSlice/FlatSlice.h"
#include "../DataContainer/Table.h"

template<typename _Scalar, int NX = Eigen::Dynamic, int NY = Eigen::Dynamic>
struct Functor
{
  typedef _Scalar Scalar;
  enum {
      InputsAtCompileTime = NX,
      ValuesAtCompileTime = NY
  };

  typedef Eigen::Matrix<Scalar,InputsAtCompileTime,1> InputType;
  typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,1> ValueType;
  typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,InputsAtCompileTime> JacobianType;

  int m_inputs, m_values;

  Functor() : m_inputs(InputsAtCompileTime), m_values(ValuesAtCompileTime) {}
  Functor(int inputs, int values) : m_inputs(inputs), m_values(values) {}

  int inputs() const { return m_inputs; }
  int values() const { return m_values; }

};

struct LstqFunctor: Functor<double> {
    LstqFunctor(const Table& observed, FlatSlice& slice) 
        : Functor<double>(slice.get_n_params(), observed.get_n_data()), observed_data(observed), vol_slice(slice) {}

    int operator()(const Eigen::VectorXd &z, Eigen::VectorXd &fvec) const {
        fvec = Eigen::MatrixXd::Constant(m_values, int(1), z(0)) - observed_data.getColumn("IV");
        return 0;
    }

    const Table& observed_data;
    FlatSlice& vol_slice;
};