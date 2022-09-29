#ifndef MRC_HPP
#define MRC_HPP

#include <complex>
//#include <math.h>
#include <cmath>
#include <random>
#include <array>

// #define PI 3.14159265358979323846

using namespace std;

template <class datat, short N>
class SoC{
  /* data */
  // Model parameters for the compute
  array<datat, N> mod;                       // route amplitude
  array<datat, N> freq;                      // doppler frequency
  array<datat, N> phas;                      // phase deviation

  //Smart Pointers for time simulation
  //std::complex<datat> mu[N];          // Sum of Cisoids Realization
  //std::complex<datat> VLC;            // Vision Line Component

public:
  /* functions */
  /// @brief Compute Sum of Cisoids model taking an empty pointer and returning it filled
  /// @param mu_t Pointer to external SoC buffer
  /// @param T simulation Time, t = [0, T]
  /// @param Ts time step
  void Calc_SoC(complex<datat> *mu,datat T, datat Ts) {
    int num = (T / Ts) + 1;
    for (int t = 0; t < num; t++)
      {
        for (short i = 1; i < N + 1; i++)              //Compute 
          {
            //C1*EXP(i*[2pi*F*t + Theta])
            mu_t[t] += complex<datat>(mod[i-1], 0) * exp(complex<datat>(0, 2 * M_PI * freq[i-1] * (t * Ts) + phas[i-1]));
          }
      }
  }

  //void Calc_VLC(datat &m, datat T, datat Ts) //takes an empty pointer and returns filled
  //{}

  /// @brief Compute Vision Line Component
  /// @param vlc Pointer to external Line of Sight buffer
  /// @param T total time size
  /// @param Ts time step
  /// @param T_mod amplitude component for Line of Sight
  /// @param T_freq frequecy component for Line of Sight
  /// @param T_phas phase component for Line of Sight
  void Define_VLC(complex<datat>* vlc, datat T, datat Ts, datat T_mod, datat T_freq, datat T_phas)
  {
    int num = (T / Ts) + 1;
    for (int t = 0; t < num; t++)     //Create time vector simulation
      {
        vlc[t] += complex<datat>(T_mod, 0) * exp(complex<datat>(0, 2 * M_PI * T_freq * (t * Ts) + T_phas));
      }
  }
  /// @brief Compute Parameters by Extended Method of Exact Doppler Spread (EMEDS)
  /// 
  /// @param Fmax Maximum Doppler Frequency
  /// @param sig Standard Deviation
  void Comp_model(datat sig, datat Fmax)
  {
    // Fmax = 91 and sig = 1, text paramters p:223 fig:5.69
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<datat> distrib(0, 2 * M_PI);

    for (short i = 1; i < N + 1; i++)
      {
        phas[i - 1] = distrib(gen);
        mod[i - 1] = sig * sqrt(2 / (datat)N);
        freq[i - 1] = Fmax * cos((i - 0.25) * (2 * M_PI / (datat)N));
      }
  }
  /// @brief Compute Parameters by Lp-Norm Method (LPNM) 
  /// @param sig Standard Deviation
  void Comp_model(datat sig)
  {
    double sum_mod = 0;

    for (short i = 0; i <= (N - 1); i++)
      {
        sum_mod += mod[i] * mod[i];
      }

    mod[N] = sqrt(2 * sig * sig - sum_mod);
  }
  //void Comp_model(datat Fmax);                //
};

#endif
