#include "solver_module.h"
#include "solver_connector.h"
#include "print_tools.h"
#include "schema.h"

#include <math.h>

using namespace std;

struct SolverParams {
    double h = 0.1;
};

double DerFun1(const double& x, const double& y){
    return 3 * sin(2 * y) + x;
}

void GenerateX(SolverParams params, vector<double>& X, double init_v) {
    X[0] = init_v;
    for (int i = 1; i < static_cast<int>(X.size()); ++i) {
        X[i] = X[0] + params.h * i;
    }
}

int main()
{
    const int n = 15;
    vector<double> X(n);
    SolverParams param;
    GenerateX(param, X, 0);

    SolverConnector sc("G:/knowledge/UIRS/TESTS/solver/SOLVER_DLL_WITH_CLASS/");
    vector<string> dll_names = sc.addAllAvailableSolvers();

    SolverModule sm;
    vector<DER_VALUES> output = sm.solveSchema(sc.getUserSolver(dll_names[0]), ConstSource(1, 0.1, 10), {Inertial, Integrator}, 0.1);
    cout << output[1] << endl;

//    bool end = 0;
//    while(!end) {
//        cout << "Existed DLL:\n";
//        vector<string> dll_names = sc.getAvailableSolverDllNames();
//        PrintNames(dll_names);
//        cout << "Enter the solver dll-module number you need: ";
//        int dll_number;
//        cin >> dll_number;

//        sc.addNewSolver(dll_names[dll_number - 1]);
//        vector<string> user_solver_names = sc.getUserSolversNames();
//        PrintNames(user_solver_names);
//        cout << "Enter the solver number you need: ";
//        int solv_number;
//        cin >> solv_number;

//        vector<DER_VALUES> Y1 = sm.solveSchema(sc.getUserSolver(user_solver_names[solv_number - 1]), X, DerFun1, param.h);
//        cout << "X:  " << X << endl;
//        cout << "Y1: " << Y1 << endl;

//        cout << "Enter 1 to complete: ";
//        cin >> end;
//    }

    return 0;
}



