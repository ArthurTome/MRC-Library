///*

//MAIN CODE
#include <iostream>
#include <complex>
#include "MRC.hpp"

constexpr auto N = 20;

using namespace std;


int main(int argc, char *argv[])
{
    //Config Simulation
    float t  = 0.5;
    float tal = 0.16;
    float ts = 0.001;
    int sig = 1;                                            // Fmax = 91 and sig = 1, text paramters p:223 fig:5.69
    int F = 91;

    int s_soc = t / ts + 1;                                 //size soc vector
    int s_rxx = tal / ts + 1;                               //size rxx vector

    //
    complex<float> soc[s_soc];                              //Buffer to SoC
    complex<float> rxx[s_rxx];                              //Buffer to Rxx
    complex<float> soc_tmp[s_soc];                          //Buffer to soc_tmp
	SoC <float, N> channel;

	channel.Comp_EMEDS(sig, F);                             //EMEDS sig = 1 Fmax = 91Hz

    // Numeric iteration for soc mean
    for (int i = 0; i < 10000; i++) {
        channel.Comp_SoC(&soc_tmp[0], t, ts);               //SoC vector simulation, take vector for SoC

        for (int t = 0; t < s_soc; t++)
        {
            soc[t] += soc_tmp[t];
            if (i != 0) rxx[t] /= 2;
        }
    }

    channel.NRXX(&soc[0], &rxx[0], t, tal, ts);             //Numeric Correlation vector simulation
    

    //channel.IRXX(&rxx[0], 1, 91, t, ts);                  //JAKES Correlation vector simulation
    //channel.RXX(&rxx[0], t, ts);                          //Parametric Correlation vector simulation
    //for (int t = 0; t < s_soc; t++) cout << '[' << soc[t].real() << "," << soc[t].imag() << "],";


    for (int t_i = 0; t_i < (int)(tal/ts) + 1; t_i++) cout << "," << rxx[t_i].real();       // Print for python
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