#include <math.h>

double n_func(double *x, int N){
    double temp;

    for (int i = 0; i < N; i++)
    {
        temp += -1 * std::pow(x[i], 2);
    }
    return temp;
}

double fletcherPowell(){
    cyl_bessel_j(0, 2.0 * M_PI * freq_max * t_i * ts);
    return 0.0;
}