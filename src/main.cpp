#include <iostream>
#include <complex>
#include <array>
#include "MRC.hpp"

constexpr auto N = 21;

using namespace std;

int main(int argc, char *argv[])
{
    //Config Simulation
    constexpr double sig = 1.0;                             // Fmax = 91 and sig = 1, text paramters p:223 fig:5.69
    constexpr double F = 91.0;

    constexpr double tal = N / (4.0 * F);
    constexpr double t  = 10.0*tal;
    constexpr double ts = 0.0005;

    constexpr int s_soc = (int)(t / ts) + 1;                //size soc vector
    //int s_rxx = tal / ts + 1;                             //size rxx vector

    array<complex<float>, s_soc> soc = {};
    array<float, s_soc> rxx = {};

    //complex<float> soc_tmp[s_soc];                        //Buffer to soc_tmp
	SoC <float, N> channel;


    // Test Correlation
	//channel.Comp_GMEA(sig, F);                              //EMEDS sig = 0.5 Fmax = 91Hz
    channel.Comp_EMEDS(sig, F);                             //EMEDS sig = 0.5 Fmax = 91Hz
    array<float, s_soc> rxx_t = {};

    for (auto n = 0; n < 100; n++) {
        channel.Comp_SoC(soc.begin(), t, ts);               //SoC vector simulation, take vector for SoC
        channel.NRXX(soc.begin(), rxx_t.begin(), t, ts);    //Numeric Correlation vector simulation

        for (int t_i = 0; t_i < s_soc; t_i++)
        {
            rxx[t_i] += rxx_t[t_i];
            if (n != 0) rxx[t_i] /= 2;
        }
    }

    for (auto var = rxx.begin(); var != rxx.end(); var++) cout << *var/rxx[0] << ',';

    //for (int t_i = 0; t_i < (int)(t / ts) + 1; t_i++) cout << rxx_t[t_i].real()/abs(*rxx_t.begin()) << ',';
    return 0;
}

// More tests: probability density function of the envelope, the level-crossing rate, and the
// average duration of fades