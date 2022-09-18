///*

//MAIN CODE
#include <iostream>
#include "MRC.hpp"


int main(int argc, char *argv[])
{
	SoC <float, 10>channel;
	channel.Comp_model(1, 91);
    channel.Calc_SoC();


  return 0;
}

//*/

/*

//TESTE CODES
#include <complex>
#include <random>
#include <iostream>
#include <numbers>

#define PI 3.14159265358979323846

using namespace std;

int main()
{
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<float> distrib(0, 2* PI);

    complex<float> c;
    complex<float> c1(5, 6);
    complex<float> c2(3, 5);

    for (int n = 0; n < 10; ++n) {
        cout << complex<float>(distrib(gen), 0) * exp(std::complex<float>(0, 2 * PI * distrib(gen) + distrib(gen))) << ' ';
    }
    cout << '\n';
}

*/