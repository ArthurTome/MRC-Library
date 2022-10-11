///*

//MAIN CODE
#include <iostream>
#include <memory>                                   //At Work
#include "MRC.hpp"

#define N 20

using namespace std;

int main(int argc, char *argv[])
{

    float t  = 0.08;
    float ts = 0.001;

    int num = t / ts + 1;

    //Config Simulation 
    complex<float> mu[num];                         //Buffer to SoC
	SoC <float, N> channel;

	channel.Comp_GMEA(1, 91);                       //EMEDS sig = 1 Fmax = 91Hz
    //channel.Comp_SoC(&mu[0], t, ts);              //SoC vector simulation, take vector for SoC
    //channel.RXX(&mu[0], t, ts);                   //SoC vector simulation, take vector for SoC
    channel.IRXX(&mu[0], 1, 91, t, ts);             //SoC vector simulation, take vector for SoC

    //for (int t = 0; t < num; t++) cout << '[' << mu[t].real() << "," << mu[t].imag() << "],";
    for (int t_i = 0; t_i < num; t_i++) cout << mu[t_i].real() << ",";
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