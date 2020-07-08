#include <cmath>

using namespace std;


double error(double* av, double* av2, unsigned int N);
void set_to_zero(double *, unsigned int);
void set_to_zero(int *, unsigned int);
void check(unsigned int L, unsigned int i, double* ave, double* ave2, double *sum);

void Blocking_Method(unsigned int N, double* ave, double* ave2, double* ave_prog, double* err);
