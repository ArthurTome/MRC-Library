/** INTERFACE BASICA EM C++
 *  
 *  
*/

#include <iostream>
#include <complex>
#include <array>
#include "MRC.hpp"

using namespace std;


int main(int argc, char *argv[]){
    // ARGS
    short N = 21;
    float freq = 91;
    float sig = 1;

    // |============================================================|
    // External vector of exernal aplications
    array<complex<float>, 100> soc = {};
    array<float, 100> rxx = {};
    array<float, 100> psd = {};

    // |============================================================|

    //START FUNCTION
    SoC <float> floatSoC(N, freq, sig);                         // Initialize class <float> with frequency 91 and standard deviation 1
    floatSoC.Comp_EMEDS();                                      // Compute parameter 
    floatSoC.Comp_SoC(soc.begin(), 100, 0.001);                 // Compute Sum os Cisoids
    //floatSoC.IRXX(rxx.begin(), 100, 0.1);
    //floatSoC.CRXX(soc.begin(), rxx.begin(), 100);               // Compute cross correlation
    //floatSoC.PSD_SoC(soc.begin(), rxx.begin(), 100);
    //cout << floatSoC.Mean_SoC(soc.begin(), 100, true) << "\n";
    //for (auto var = rxx.begin(); var != rxx.end(); var++) cout << *var << " ";
    cout << floatSoC.PSD_SoC(soc.begin(), 100);
}


/*
int main(int argc, char *argv[])
{
    //Config Simulation
    double sig = 1.0;                             // Fmax = 91 and sig = 1, text paramters p:223 fig:5.69
    double F = 91.0;

    double tal = N / (4.0 * F);
    double t  = 10.0*tal;
    double ts = 0.0005;

    int s_soc = (int)(t / ts) + 1;                          //size soc vector

    array<complex<float>, s_soc> soc = {};
    array<complex<float>, s_soc> suz = {};
    array<float, s_soc> rxx = {};
    array<float, s_soc> log = {};

	SoC <float> channel(21, 91, 1);                                    // Create channel object


    // Test Correlation
	//channel.Comp_GMEA(sig, F);                            // GMEA sig = 0.5 Fmax = 91Hz
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
*/

// More tests: probability density function of the envelope, the level-crossing rate, and the
// average duration of fades