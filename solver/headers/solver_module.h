#ifndef SOLVER_MODULE
#define SOLVER_MODULE
#include "solvers_interface.h"

#include <vector>
#include <map>
#include <set>
#include <windows.h>

using pDerFun = double (*)(const double&, const double&);
using DER_VALUES = std::vector<double>;

class SolverModule {
public:

    void addNewSolver(ISolver* solver) {
        user_solvers[solver->getName()] = solver;
    }

    /**
     * @brief solveBlock
     * Вызов решателя
     *
     * @param solver Функция решателя
     * @param X Вектор аргументов
     * @param F Фукнция расчета производной уравнения (в форме Коши)
     * @param h Шаг решателя
     * @return Вектор решений дифференциального уравнения
     */
    std::vector<double> solveBlock(ISolver* solver,
                                   const std::vector<double>& X,
                                   pDerFun F,
                                   double h);

    /**
     * @brief solveSchema
     * Решает систему дифференциальных уравнений последовательно соединенных
     * блоков
     *
     * @param solver Функция решателя
     * @param input Вектор входных значений
     * @param funcs Фукнции расчета производной уравнения (в форме Коши)
     * @param h Шаг решателя
     * @return Вектор векторов с решениями каждого из уравнений
     */
    std::vector<DER_VALUES> solveSchema(ISolver* solver,
                                        const std::vector<double>& input,
                                        std::vector<pDerFun> funcs,
                                        double h);
    SolverModule();
    ~SolverModule();

private:
    std::map<std::string, ISolver*> user_solvers;
};

#endif // SOLVER_MODULE

