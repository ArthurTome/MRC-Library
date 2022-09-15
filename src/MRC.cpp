#include <complex>      // Complex functions for cisoids method
//#include <random>       // Random distriutions for channel model
#include "MRC.hpp"

//void Init_Parameters(short N)

//void Dest_Parameters()

/// @brief Compute Sum of Cisoids model
/// @tparam N 
/// @tparam data
template <class datat, short N>
void Calc_SoC()
{
    short i = 1;
    while(i <= N)
    {
        mu[i] += mod[i]*exp(0, 2*PI*freq[i] + phas[i]);
    }
}

template <class datat, short N>
datat Get()
{
    return 0;
}

/// Define Vision Component for The Rise Process
/// @brief 
/// @param T_mod 
/// @param T_freq 
/// @param T_freq
template <class datat, short N>
void Define_Vision_Comp(datat T_mod, datat T_freq, datat T_phas)
{
    m_mod = T_mod;
    m_freq = T_freq;
    m_phas = T_phas;
}

/// @brief Define vector size for the parameters, is the same size as the model
/// @param v_size size to the vetor parameters/model
//template <class datat>
//void Define_Vector_Size(short v_size)
//{
//    m_mod = data &T_mod[v_size];        //
//    m_freq = data &T_freq[v_size];      // RAW Pointers for test
//    m_phas = data &T_phas[v_size];      //
//
//}

/// @brief Compute Parameters by Extended Method of Exact Doppler Spread (EMEDS)
/// @param Fmax Maximum Doppler Frequency
/// @param sig Standard Deviation
template <class datat, short N>
void Calc_EMEDS(double Fmax, double sig)
{
    // Fmax = 91 and sig = 1, text paramters p:223 fig:5.69
    short i = 1;
    while (i <= N)
    {
        mod[i] = sig*sqrt(2/N);
        freq[i] = Fmax*cos((2*PI*(i-0.25)/N));
    }
}

/// @brief Compute Parameters by Lp-Norm Method (LPNM) 
/// @param N 
/// @param sig
template <class datat, short N>
void Calc_LPNM(double sig, double Fmax)
{
    short i = 1;
    double sum_mod = 0;

    while (i <= N-1)
    {
        sum_mod += mod[i]*mod[i];
    }

    mod[N] = sqrt(2*sig*sig - sum_mod);
}


/*
/// @brief Select compute method for estimate paramters
/// @param Calc_Method Method for computation - parameters: 1. EMEDS, 2. MSEM
void Calc_Model_Coef(char[5] Calc_Method)
{
    switch (str2int(Calc_metrod))
    {
    case str2int("EMEDS"):
        
        Calc_EMEDS();
        break;

    case str2int("MSEM"):
        Calc_EMEDS();
        break;

    default:
        break;
    }

}
*/