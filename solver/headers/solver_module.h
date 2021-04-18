#ifndef SOLVER_MODULE
#define SOLVER_MODULE
#include "solvers_interface.h"

#include <vector>
#include <map>
#include <set>
#include <windows.h>

using pDerFun = double (*)(const double&, const double&);
using DER_VALUES = std::vector<double>;

class SolverConnector {
public:
    /**
     * @brief getUserSolver
     *
     * @param solver_name Имя решателя
     * @return Указатель на решатель
     */
    ISolver* getUserSolver(std::string solver_name);

    /**
     * @brief getUserSolversNames
     *
     * @return Вектор имен всех загруженных решателей
     */
    std::vector<std::string> getUserSolversNames();

    /**
     * @brief addNewSolver
     * Добавляет решатель в список решателей
     *
     * @param dll_name Имя dll-библиотеки, в которой описан решатель
     * @return Имя решателя в списке решателей
     */
    std::string addNewSolver(std::string dll_name);
    void connectTestFunction();

    /**
     * @brief getAvailableSolverDllNames
     * Нахождение всех имеющихся решателей в указанной при
     * создании SolverConnector директории
     *
     * @return Вектор имен dll-библиотек
     */
    std::vector<std::string> getAvailableSolverDllNames();

    /**
     * @brief callSolver
     * Вызов решателя
     *
     * @param solver_name Наименование решателя
     * @param X Вектор аргументов
     * @param F Фукнция расчета производной уравнения (в форме Коши)
     * @param h Шаг решателя
     * @return Вектор решений дифференциального уравнения
     */
    std::vector<double> callSolver(std::string solver_name,
                                   const std::vector<double>& X,
                                   pDerFun F,
                                   double h);

    /**
     * @brief getAvailableSolverDllNames
     * Получает имена всех dll в заданной директории
     *
     * @return Вектор имен всех dll, найденных в заданной директории solvers_dir
     */
    std::vector<std::string> addAllAvailableSolvers();

    /**
     * @brief solveSchema
     * Решает систему дифференциальных уравнений последовательно соединенных
     * блоков
     *
     * @param solver_name Имя решателя
     * @param input Вектор входных значений
     * @param funcs Фукнции расчета производной уравнения (в форме Коши)
     * @param h Шаг решателя
     * @return Вектор векторов с решениями каждого из уравнений
     */
    std::vector<DER_VALUES> solveSchema(const std::string& solver_name,
                                        const std::vector<double>& input,
                                        std::vector<pDerFun> funcs,
                                        double h);
    SolverConnector();

    /**
     * Устанавливает директорию для поиска решателей
     */
    SolverConnector(std::string);
    ~SolverConnector();

private:
    std::map<std::string, ISolver*> user_solvers;
    std::string solvers_dir = "./";

};

#endif // SOLVER_MODULE

