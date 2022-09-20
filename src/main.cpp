/*

//MAIN CODE
#include <iostream>
#include <memory>
#include "MRC.hpp"

#define N 10

using namespace std;

int main(int argc, char *argv[])
{

    float T  = 0.20;
    float Ts = 0.01;

    complex<float> mu[T/Ts + 1];

    //Config Simulation 
	SoC <float, N>channel;
	channel.Comp_model(1, 91);      //EMEDS sig = 1 Fmax = 91Hz
    channel.Calc_SoC(1e-5, 0.25);   //SoC vector simulation, take vector for SoC

    //
    
    
    return 0;
}

//*/

///*

//TESTE CODES
#include <complex>
#include <iostream>
#include <numbers>

#define PI 3.14159265358979323846


using namespace std;
float T = 20;
float Ts = 0.1;
int c = 0;

int main()
{
    complex<double> Uf[] = { {1, 2},{3, 4} };
    complex<double>* a = &Uf[0];

    for (float i = 0; i <= T/Ts; i++) {
        c++;
        cout << i << ' ';
    }
    cout << '\n' << c << '\n' << (T/Ts + 1);
}

//*/