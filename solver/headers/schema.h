#ifndef SCHEMA
#define SCHEMA

#include <vector>

using pDerFunc = double (*)(const double&, const double&);

double Inertial(const double&, const double&);
double Integrator(const double&, const double&);
std::vector<double> ConstSource(double, double, double);

#endif // SCHEMA

