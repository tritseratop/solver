#ifndef SOLVERS_INTERFACE
#define SOLVERS_INTERFACE
#include <vector>

typedef double (*pDerFun)(const double&, const double&);
// Interface class
class ISolver {
public:
    virtual ~ISolver() { ; }
    virtual std::vector<double> Solve(const std::vector<double>& X, pDerFun F, double h) = 0;
    virtual void Release() = 0;
};

typedef ISolver* (*SOLVER) ();

#endif // SOLVERS_INTERFACE


