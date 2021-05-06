#include "solver_module.h"

#include <iostream>

using namespace std;



vector<double> SolverModule::solveBlock(ISolver* solver, const vector<double>& X, pDerFun F, double h) {
        return solver->Solve(X, F, h);

}

// Вынести отдельно??
vector<DER_VALUES> SolverModule::solveSchema(ISolver* solver,
                                             const vector<double>& input,
                                             vector<pDerFun> funcs,
                                             double h) {
    vector<DER_VALUES> output(funcs.size(), DER_VALUES(input.size()));

    output[0] = solver->Solve(input, funcs[0], h);

    for (size_t i = 1; i < output.size(); ++i) {
        output[i] = solver->Solve(output[i - 1], funcs[i], h);
    }
    return output;
}

SolverModule::SolverModule() {}

SolverModule::~SolverModule() {}
