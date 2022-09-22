///*

//MAIN CODE
#include <iostream>
#include <memory>                                   //At Work
#include "MRC.hpp"

#define N 10

using namespace std;

int main(int argc, char *argv[])
{

    float T  = 0.25;
    float Ts = 0.001;

    int num = T / Ts + 1;

    //Config Simulation 
    complex<float> mu[num];                         //Buffer to SoC
	SoC <float, N> channel;

	channel.Comp_model(1, 91);                      //EMEDS sig = 1 Fmax = 91Hz
    channel.Calc_SoC(&mu[0], T, Ts);                //SoC vector simulation, take vector for SoC

    for (int t = 0; t < num; t++) cout << '[' << mu[t].real() << "," << mu[t].imag() << "],";

    return 0;
}

 //*/

/*

//TESTE CODES
#include <complex>
#include <iostream>
#include <numbers>

//#define PI 3.14159265358979323846

using namespace std;

#define N 7
#define sig 1
float mod[N];

int main()
{
    for (short i = 1; i <= N + 1; i++)
    {
        //phas[i - 1] = distrib(gen);
        mod[i - 1] = sig * sqrt(2 / (float)N);
        //freq[i - 1] = Fmax * cos((i - 0.25) * (2 * PI / N));
        cout << mod[i - 1] << '\n';
    }
    cout << "hello world" << 2*1.15;
}

*/