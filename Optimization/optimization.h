#pragma once

#include <memory>
#include <vector>
#include <armadillo>
#include <deque>
#include "Globals.h"

namespace Optimization{

struct ObjectFunc{
    ObjectFunc(int dim0 = 0):dim(dim0){}
    int dim;
    virtual double operator()(arma::vec &x, arma::vec &grad) = 0;
};

class LBFGS{
//	typedef double (* evaluateFunc)(const arma::vec x, arma::vec grad, const int n);
public:
    enum LineSearch {Wolf, Armijo};
	struct LBFGS_param{ int maxIter; int memoryLimit;};
	struct PointValueDeriv {
            double step, value, deriv;
            PointValueDeriv(double step0 = NaN, double value0 = NaN, double deriv0 = NaN) : 
			    step(step0), value(value0), deriv(deriv0) { }
	};
	LBFGS(ObjectFunc &func, LBFGS_param param0, LineSearch method);
	void calDirection();
	void updateParam();
	void calStepLength_armijo();
        void calStepLength_wolf();
	bool converge();
	void minimize();
        double cubicInterp(const LBFGS::PointValueDeriv& p0, const LBFGS::PointValueDeriv& p1);
        ObjectFunc &calValGrad;
        PointValueDeriv aHi, aLo;
        LBFGS_param param;
        double maxIter;
        double step, step_star;
        double currValue;
        int memoryLimit;
        LineSearch lineSearchMethod;
// 	s_{k-1} = x_k - x_{k-1}
//  y_{k-1} = (grad_k - grad_{k-1})
	std::deque<arma::vec> s_list, y_list;
// rho_k =1.0 /(y_k^T * s_k)	
	std::deque<double> rho_list;
	std::vector<double> alpha_list;	
        arma::vec direction;
	arma::vec grad, grad_old, x, x_init, x_old, x_new, grad_new;
};

class SteepDescent{
public:
    struct SteepDescent_param{
        double eps;
        double step;};
    SteepDescent(ObjectFunc &func, SteepDescent_param param0);
    void minimize();
private:
 //   bool converged();
    double eps;
    double step;

};




}