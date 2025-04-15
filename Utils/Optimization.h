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

  const int m_inputs, m_values;

  Functor() : m_inputs(InputsAtCompileTime), m_values(ValuesAtCompileTime) {}
  Functor(int inputs, int values) : m_inputs(inputs), m_values(values) {}

  int inputs() const { return m_inputs; }
  int values() const { return m_values; }

};

struct LstqFunctor: Functor<double> {
    LstqFunctor(const Table& observed, VolSlice& slice, double S0, double r);

    int operator()(const Eigen::VectorXd &z, Eigen::VectorXd &fvec) const;

    const Eigen::MatrixXd mkt_strikes;
    const Eigen::MatrixXd mkt_iv;
    double S0;
    double r;
    VolSlice& vol_slice;
};