#include "solver_module.h"

#include <boost/filesystem/operations.hpp>
#include <iostream>

using namespace std;
namespace fs = boost::filesystem;

ISolver* SolverConnector::getUserSolver(std::string solver_name) {
    if (user_solvers.count(solver_name) == 0) {
        cout << "There are no " + solver_name + " solver in base/n";
        return nullptr;
    } else {
        return user_solvers.at(solver_name);
    }
}

vector<string> SolverConnector::getUserSolversNames() {
    vector<string> names;
    for (const auto& name : user_solvers) {
        names.push_back(name.first);
    }
    return names;
}

LPCWSTR str2pwchar_t(string str) {
    return std::wstring(str.begin(), str.end()).c_str();
}

string SolverConnector::addNewSolver(string dll_name) {
    std::string solver_name = dll_name;
    solver_name.erase(solver_name.end() - 4, solver_name.end());

    HMODULE hlib = LoadLibrary(str2pwchar_t(dll_name));
    if (hlib == NULL) {
     cout << "Library loading error\n";
    }
    else {
     cout << "Library loaded successfully\n";
     SOLVER CreateSolver = (SOLVER)GetProcAddress(hlib, "CreateSolver");
     if (CreateSolver == NULL) {
         cout << "Function loading error\n";
     } else {
         cout << solver_name << " function loaded successfully\n";
         ISolver* pSolver = CreateSolver();
         user_solvers[solver_name] = pSolver;
     }
    }
    FreeLibrary(hlib);
    return solver_name;
 }

vector<string> SolverConnector::getAvailableSolverDllNames() {
    vector<fs::path> file_names;
    fs::directory_iterator begin(solvers_dir);
    fs::directory_iterator end;
    for (; begin != end; ++begin) {
        file_names.emplace_back(*begin);
    }
    vector<string> dll_names;
    for (const auto& name : file_names) {
        if (name.extension().string() == ".dll") {
            dll_names.push_back(name.filename().string());
        }
    }
    return dll_names;
}

vector<double> SolverConnector::callSolver(string solver_name, const vector<double>& X, pDerFun F, double h) {
    if (user_solvers.count(solver_name) == 0) {
        cout << "There are no " + solver_name + " solver in base/n";
        return {};
    } else {
        auto solver = user_solvers.at(solver_name);
        return solver->Solve(X, F, h);
    }
}

vector<string> SolverConnector::addAllAvailableSolvers() {
    fs::directory_iterator begin(solvers_dir);
    fs::directory_iterator end;
    vector<string> dll_names;
    for (; begin != end; ++ begin) {
        if ((*begin).path().extension().string() == ".dll") {
            //string k = (*begin).path().string();
            HMODULE hlib = LoadLibrary(str2pwchar_t((*begin).path().string()));
            //HMODULE hlib = LoadLibrary(str2pwchar_t("G:/knowledge/UIRS/TESTS/solver/SOLVER_DLL_WITH_CLASS/euler_class1.dll"));
            if (hlib != NULL) {
                SOLVER CreateSolver = (SOLVER)GetProcAddress(hlib, "CreateSolver");
                if (CreateSolver == NULL) {
                    cout << "Function loading error\n";
                } else {
                    cout << (*begin).path().filename().string() << " function loaded successfully\n";
                    ISolver* pSolver = CreateSolver();
                    user_solvers[(*begin).path().filename().string()] = pSolver;
                    dll_names.push_back((*begin).path().filename().string());
                }
            }
            //FreeLibrary(hlib);
        }
    }
    return dll_names;
}

// Вынести отдельно??
vector<DER_VALUES> SolverConnector::solveSchema(const string& solver_name,
                                                const vector<double>& input,
                                                vector<pDerFun> funcs,
                                                double h) {
    ISolver* solver = getUserSolver(solver_name);
    if (solver == nullptr) {
        cout << "There are no " + solver_name + " solver in base/n";
        return {};
    } else {
        vector<DER_VALUES> output(funcs.size(), DER_VALUES(input.size()));

        output[0] = solver->Solve(input, funcs[0], h);

        for (size_t i = 1; i < output.size(); ++i) {
            output[i] = solver->Solve(output[i - 1], funcs[i], h);
        }
        return output;
    }
}

SolverConnector::SolverConnector() {}

SolverConnector::SolverConnector(std::string dir) {
    solvers_dir = dir;
}

SolverConnector::~SolverConnector() {
    for(auto& s : user_solvers) {
        s.second->Release();
    }
}
