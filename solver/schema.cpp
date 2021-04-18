#include "schema.h"

double Inertial(const double& x, const double& y){
    return x - y;
}

double Integrator(const double& x, const double& y){
    return x;
}

std::vector<double> ConstSource(double source_value, double step, double time) {
    std::vector<double> output(time/step, source_value);
    return output;
}
