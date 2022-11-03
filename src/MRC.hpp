#ifndef MRC_HPP
#define MRC_HPP

#include <complex>
//#include <math.h>
#include <cmath>
#include <random>
#include <array>

// #define PI 3.14159265358979323846

using namespace std;

/// @brief class for simulation based on sum of cisoids
/// OBS: The time vector, despite being correctly defined, 
/// for reasons of rounding the expression (t/ts) has one 
/// less element than the theoretical
/// @param datat the type for class, float or double
/// @param N number of cisoids
template <class datat, short N> class SoC{
  /* data */
  // Model parameters for the compute
  array<datat, N> mod;                       // route amplitude
  array<datat, N> freq;                      // doppler frequency
  array<datat, N> phas;                      // phase deviation

public:
    /* functions */
    /// @brief Compute Jakes Ideal Auto Correlation 
    /// @param irxx Pointer to external rxx buffer
    /// @param t simulation Time, t = [0, T)
    /// @param ts time step
    void IRXX(complex<datat>* irxx, datat sig, datat freq_m, datat t, datat ts) {
        int num = (t / ts) + 1;             // length for time, [0, t - ts]
        for (int t_i = 0; t_i < num; t_i++)
        {
            irxx[t_i] = pow(sig, 2) * cyl_bessel_j(0, 2 * M_PI * freq_m * t_i * ts);
        }
    }

    /// @brief Compute Jakes Model Auto Correlation 
    /// @param rxx Pointer to external irxx buffer
    /// @param t simulation Time, t = [0, T)
    /// @param ts time step
    void RXX(complex<datat>* rxx, datat t, datat ts) {
        int num = (t / ts) + 1;
        for (int t_i = 0; t_i < num; t_i++)
        {
            for (short i = 0; i < N; i++)                       //Compute 
            {
                //C1*EXP(i*[2pi*F*t + Theta])
                rxx[t_i] += cos(2 * M_PI * freq[i] * t_i * ts) * pow(mod[i],2);
            }
            rxx[t_i] /= 2;
        }
    }

    /// @brief Compute Numeric Model Auto Correlation 
    /// @param soc Pointer to external soc buffer
    /// @param nrxx Pointer to external nrxx buffer
    /// @param t simulation Time, t   = [0, T)
    /// @param tal Coerence Time, tal = [0, tal)
    /// @param ts time step
    void NRXX(complex<datat>* soc ,complex<datat>* nrxx ,datat t, datat tal ,datat ts) {
        int s_soc = (t / ts) + 1;
        int s_rxx = (tal / ts) + 1;

        for (int t_i = 0; t_i < s_rxx; t_i++)
        {
            for (short i = t_i; i < s_soc; i++)                 //Compute 
            {
                nrxx[t_i] += (soc[i-t_i] * conj(soc[i]))/(abs(soc[i - t_i])*abs(conj(soc[i])));
            }
            nrxx[t_i] /= s_soc;
        }
    }
    
    /// @brief Compute Sum of Cisoids model taking an empty pointer and returning it filled
    /// @param mu_t Pointer to external SoC buffer
    /// @param t simulation Time, t = [0, T)
    /// @param ts time step
    void Comp_SoC(complex<datat> *soc, datat t, datat ts) {
        int num = (t / ts) + 1;
        datat temp = 0;
        Comp_phas();

        for (int t_i = 0; t_i < num; t_i++)
        {
            for (short i = 1; i < N + 1; i++)                     //Compute 
            {
                //C1*EXP(i*[2pi*F*t + Theta])
                soc[t_i] += complex<datat>(mod[i-1], 0) * exp(complex<datat>(0, 2 * M_PI * freq[i-1] * (t_i * ts) + phas[i-1]));
            }
        }
    }
    
    
    /// @brief Compute Vision Line Component
    /// @param vlc Pointer to external Line of Sight buffer
    /// @param t total time size
    /// @param ts time step
    /// @param t_mod amplitude component for Line of Sight
    /// @param t_freq frequecy component for Line of Sight
    /// @param t_phas phase component for Line of Sight
    void Define_VLC(complex<datat>* vlc, datat t, datat ts, datat t_mod, datat t_freq, datat t_phas)
    {
        int num = (t / ts) + 1;
        for (int t_i = 0; t_i < num; t_i++)                       //Create time vector simulation
        {
            vlc[t_i] += complex<datat>(t_mod, 0) * exp(complex<datat>(0, 2 * M_PI * t_freq * (t_i * ts) + t_phas));
        }
    }

    /// @brief Compute Phase
    void Comp_phas() {
        random_device rd;  //Will be used to obtain a seed for the random number engine
        mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        uniform_real_distribution<datat> distrib(0, 2 * M_PI);
    
        for (short i = 1; i < N + 1; i++)
        {
            phas[i - 1] = distrib(gen);
        }
    
    }
    
    /// @brief Compute Parameters by Extended Method of Exact Doppler Spread (EMEDS)
    /// @param sig Standard Deviation
    /// @param freq_m Max Frequency
    void Comp_EMEDS(datat sig, datat freq_m)
    {
        for (short i = 1; i < N + 1; i++)
        {
            mod[i - 1] = sig * sqrt(2 / (datat)N);
            freq[i - 1] = freq_m * cos((i - 0.25) * (2 * M_PI / (datat)N));
        }
    }
    /// @brief Compute Parameters by Method of Equal Areas (MEA) 
    /// @param sig Standard Deviation
    /// @param freq_m Max Frequency
    void Comp_GMEA(datat sig, datat freq_m)
    {
        for (short i = 1; i < N + 1; i++)
        {
            mod[i - 1] = sig * sqrt(2 / (datat)N);                //A same of EMEDS
            freq[i - 1] = freq_m * sin(M_PI * i / (2 * (datat)N));
        }
    }
    //void Comp_model(datat Fmax);                //
};

#endif
