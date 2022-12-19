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

    array<complex<float>, s_soc> soc = {};
    array<complex<float>, s_soc> suz = {};
    array<float, s_soc> rxx = {};
    array<float, s_soc> log = {};

	SoC <float, N> channel;                                 // Create channel object


    // Test Correlation
	//channel.Comp_GMEA(sig, F);                              // GMEA sig = 0.5 Fmax = 91Hz
    channel.Comp_EMEDS(sig, F);                             // EMEDS sig = 0.5 Fmax = 91Hz
    array<float, s_soc> rxx_t = {};                         // Temporary vector for mean 

    // Rayleigh and Rice
    for (auto n = 0; n < 100; n++) {
        channel.Comp_SoC(soc.begin(), t, ts);               // SoC vector simulation, take vector for SoC
        channel.NRXX(soc.begin(), rxx_t.begin(), t, ts);    // Numeric Correlation vector simulation

        for (int t_i = 0; t_i < s_soc; t_i++)
        {
            rxx[t_i] += rxx_t[t_i];
            if (n != 0) rxx[t_i] /= 2;
        }
    }

    for (auto var = rxx.begin(); var != rxx.end(); var++) cout << *var/rxx[0] << ',';

    //Suzuki Type I
    channel.Comp_SoC(soc.begin(), t, ts);                   // SoC vector simulation, take vector for SoC
    channel.Log_Process(log.begin(), soc.begin(), 0, 1, s_soc);

    for (int t_i = 0; t_i < s_soc; t_i++) suz[t_i] = abs(soc[t_i])*log[t_i];
    cout << '\n' << '\n';
    for (auto var = log.begin(); var != log.end(); var++) cout << *var << ',';

    return 0;
}

// More tests: probability density function of the envelope, the level-crossing rate, and the
// average duration of fades