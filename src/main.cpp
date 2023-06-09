/** INTERFACE BASICA EM C++
 *  
 *  
*/

#include <iostream>
#include <complex>
#include "MRC.hpp"
#include <fftw3.h>

//#include <chrono>

using namespace std;

/// @brief FFT shift make negative and positive frequencys centralized in vector
/// @param A VECTOR FFT
/// @param size size of vector
void fft_shift(complex<double>* A, unsigned long size){
    unsigned long fr = floor((size + 1)/2);
    complex<double> t = {0, 0};

    if(size%2 == 0){
        for (unsigned long i = fr; i < size; i++){
            t = A[i - fr];
            A[i - fr] = A[i];
            A[i] = t;
        }
    }else{
        for (unsigned long i = fr; i < size; i++){
            t = A[i - fr + 1];
            A[i - fr] = A[i];
            A[i] = t;
        }
        A[fr - 1] = complex<double>(0, 0);;
    }
}

int main(int argc, char *argv[]){
    // |=====================| DEFAULT PARAMETERS |======================|
    short N = 21;
    double freq = 91;
    double sig = 1;
    double ts = 0.0001;
    unsigned long sz = 8000;

    // |======================| CONSOLE OPTIONS |========================|
    if (argc < 3) {
        return 0;
    }
    if ((string(argv[1]) != "--help")&&
        (string(argv[1]) != "--emeds")&&
        (string(argv[1]) != "--gmea")){
        cout << "Parametros informados" << '\n';
        return 1;
    }
    if ((string(argv[2]) != "--soc")&&
        (string(argv[2]) != "--rxx")&&
        (string(argv[2]) != "--fft")){
        cout << "Parametros informados invalidos";
        return 1;
    }
    for(short i = 3; i < argc; i+=2)
    {
        if (i == argc - 1){
            cout << "Quantidade do parametro não informada\n";
            return 1;
        }
        if (string(argv[i])== "--ncis"){
            N = atoi(argv[i+1]);
            continue;
        }
        if (string(argv[i]) == "--freq"){
            freq = atoi(argv[i+1]);
            continue;
        }

        if (string(argv[i]) == "--sig"){
            sig = atoi(argv[i+1]);
            continue;
        }

        if (string(argv[i]) == "--size"){
            sz = atoi(argv[i+1]);
            continue;
        }
        if (string(argv[i]) == "--ts"){
            ts = atoi(argv[i+1]);
            continue;
        }
        cout << "um parametro desconhecido" << '\n';
        return 1;
    }

    cout << N << ' ' << freq << ' ' << sig << ' ' << sz << ' ';

    // |=======================| DECLARE ARRAYS |========================|
    complex<double>* soc = new complex<double>[sz]();
    complex<double>* rxx = new complex<double>[sz]();
    complex<double>* fft = new complex<double>[sz]();

    // |=======================|  START FUNCTION |=======================|
    //auto start = chrono::high_resolution_clock::now();  // GET INIT TIME
    SoC <double> dSoC(N, freq, sig);                    // Initialize class <float> 
                                                        // with frequency 91 and standard deviation 1
    if (string(argv[1]) == "--emeds")
    {
        dSoC.Comp_EMEDS();                              // EMEDS
    }
    else if (string(argv[1]) == "--gmea")
    {
        dSoC.Comp_GMEA();                               // GMEA
    }
    
    dSoC.Comp_SoC(&soc[0], sz, ts);                     // Compute Sum os Cisoids
    cout.precision(6);

    if((string(argv[2]) == "--rxx")||(string(argv[2]) == "--fft")){
        dSoC.NRXX(&soc[0], &rxx[0], sz, sig);           // Compute numeric correlation for rxx and fft outputs
        // |============================| RXX |=============================|
        if(string(argv[2]) == "--rxx"){
            for (unsigned long i = 0; i < sz; i++){
                cout << rxx[i].real() << ", ";          // OUT RXX
            }
        }
        // |============================| FFT |=============================|
        else if(string(argv[2]) == "--fft"){
            fftw_plan p; // Plan
            p = fftw_plan_dft_1d(sz,reinterpret_cast<fftw_complex*>(&rxx[0]), 
                                    reinterpret_cast<fftw_complex*>(&fft[0]), 
                                    FFTW_FORWARD, FFTW_ESTIMATE);
            fftw_execute(p);
            fftw_destroy_plan(p);
            fft_shift(&fft[0], sz);

            for (unsigned long i = 0; i < sz; i++){
                cout << abs(fft[i]) << ", ";            // OUT FFT
            }
        }
    } else {
        // |============================| SOC |=============================|
        for (unsigned long i = 0; i < sz; i++){
            cout << soc[i].real() << ", ";              // OUT SOC
        }
    }

    //auto stop = chrono::high_resolution_clock::now();  // GET TIME
    //auto duration = duration_cast<chrono::microseconds>(stop - start);
    // |============================|  OUT |=============================|

    // NOT NECESSARY MAKE ERROR DOUBLE FREE OR CORRUPT
    //delete[] soc;
    //delete[] rxx;
    //delete[] fft;

    //cout << "\nDONE\n";
    //cout << "EXECUTE TIME(s): " << duration.count()/1000000.0 << '\n';
    //cout << "CHANNEL DURATION(s): " << ts*(float)sz << '\n';

    return 0;
}