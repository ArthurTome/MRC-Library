/** INTERFACE BASICA EM C++
 *  
 *  
*/

#include <iostream>
#include <iomanip>
#include <complex>
#include <array>
#include "MRC.hpp"
#include <fftw3.h>

#define sz 5000

using namespace std;


int main(int argc, char *argv[]){
    // |============================================================|
    short N = 21;
    float freq = 91;
    float sig = 1;

    // |============================================================|
    // External vector of exernal aplications
    array<complex<float>, sz> soc = {};
    array<complex<float>, sz> rxx = {};
    array<complex<float>, sz> out = {};
    array<float, sz> psd = {};

    // |============================================================|

    //START FUNCTION
    SoC <float> floatSoC(N, freq, sig);            // Initialize class <float> with frequency 91 and standard deviation 1
    floatSoC.Comp_EMEDS();                         // Compute parameter 
    floatSoC.Comp_SoC(soc.begin(), sz, 0.0001);    // Compute Sum os Cisoids
    //floatSoC.NRXX(soc.begin(), rxx.begin(), sz);
    floatSoC.RXX(rxx.begin(), sz, 0.0001, sig);

    // FFT
    //fftwf_complex *out = new fftwf_complex [sz]; // Output
    //fftwf_complex *in = new fftwf_complex [sz]; // Output
    //float *out = new float[samples];
    fftwf_plan p; // Plan

    //for (int i = 0; i < sz; i++){
    //    in[i][0] = rxx[i].real();
    //}


    //p = fftwf_plan_dft_r2c_1d(sz, &rxx[0], &out[0], FFTW_ESTIMATE);
    p = fftwf_plan_dft_1d(sz, reinterpret_cast<fftwf_complex*>(&rxx[0]), reinterpret_cast<fftwf_complex*>(&out[0]), FFTW_FORWARD, FFTW_ESTIMATE);
    fftwf_execute(p);
    fftwf_destroy_plan(p);

    cout << "READY\n";
    for (int i = 0; i < sz; i++){
        cout << abs(out[i]) << ", ";
    }

    //for (int i = 0; i < sz; i++){
    //    cout << rxx[i] << ",";
    //}

    cout << "\nDONE";
}