#include <random>
#include <complex>
#include <numbers>


#define PI 3.14159265358979323846

template <class datat, short N>
class SoC{
    /* data */
    // Model parameters for the compute
    datat mod[N];         // route amplitude
    datat freq[N];        // doppler frequency
    datat phas[N];        // phase deviation
    datat mu [N];         // channel model
    //short N;              // number of elements

    // Vision line constants parameters for the compute model
    datat m_mod[N];       // route amplitude
    datat m_freq[N];      // doppler frequency
    datat m_phas[N];      // phase deviation
public:
    /* functions */
    void Calc_SoC();
    void Define_vision(datat T_mod, datat T_freq, datat T_phas);
    void Comp_model(datat sig, datat Fmax);     //EMEDS
    void Comp_model(datat sig);                 //LPNM
    //void Comp_model(datat Fmax);                //
};

/// @brief Compute Sum of Cisoids model
template <class datat, short N>
void SoC<datat, N>::Calc_SoC()
{

    short i = 1;
    while (i <= N)
    {
        mu[i] += mod[i] * exp(0, 2 * PI * freq[i] + phas[i]);
    }
}


template <class datat, short N>
void SoC<datat, N>::Define_vision(datat T_mod, datat T_freq, datat T_phas)
{
    m_mod = T_mod;
    m_freq = T_freq;
    m_phas = T_phas;
}

/// @brief Compute Parameters by Extended Method of Exact Doppler Spread (EMEDS)
/// 
/// @param Fmax Maximum Doppler Frequency
/// @param sig Standard Deviation
template <class datat, short N>
void SoC<datat, N>::Comp_model(datat sig, datat Fmax)
{
    // Fmax = 91 and sig = 1, text paramters p:223 fig:5.69
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<datat> distrib(0, 2 * 3.14);

    short i = 1;
    while (i <= N)
    {
        mod[i] = sig * sqrt(2 / N);
        freq[i] = Fmax * cos((2 * PI * (i - 0.25) / N));
        phas[i] = distrib(gen);
    }
}

/// @brief Compute Parameters by Lp-Norm Method (LPNM) 
/// @param sig Standard Deviation
template <class datat, short N>
void SoC<datat, N>::Comp_model(datat sig)
{
    short i = 1;
    double sum_mod = 0;

    while (i <= N - 1)
    {
        sum_mod += mod[i] * mod[i];
    }

    mod[N] = sqrt(2 * sig * sig - sum_mod);
}
