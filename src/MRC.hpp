#include <complex>
#include <random>

#define PI 3.14159265358979323846

template <class datat, short N>
class SoC{
    /* data */
    // Model parameters for the compute
    datat mod[N];                       // route amplitude
    datat freq[N];                      // doppler frequency
    datat phas[N];                      // phase deviation

    //Smart Pointers for time simulation
    //std::complex<datat> mu[N];          // Sum of Cisoids Realization
    //std::complex<datat> VLC;            // Vision Line Component

public:
    /* functions */
    void Calc_SoC(datat T, datat Ts);
    void Define_VLC(datat T_mod, datat T_freq, datat T_phas);
    void Comp_model(datat sig, datat Fmax);     //EMEDS
    void Comp_model(datat sig);                 //LPNM
    //void Comp_model(datat Fmax);                //
};

/// @brief Compute Sum of Cisoids model
/// @param T simulation Time, t = [0, T]
/// @param Ts time step
template <class datat, short N>
void SoC<datat, N>::Calc_SoC(datat T, datat Ts) //takes an empty pointer and returns filled
{
    for (datat t = 0; t <= T/Ts; t++)
    {
        for (short i = 0; i <= N; i++)              //Compute 
        {
        //C1*EXP(i*[2pi*F*t + Theta])
            mu[t] += std::complex<datat>(mod[i], 0) * exp(std::complex<datat>(0, 2 * PI * freq[i] + phas[i])); //Pointer return not implemented
        }
    }
}

//template <class datat, short N>
//void SoC<datat, N>::Calc_VLC(datat &m, datat T, datat Ts) //takes an empty pointer and returns filled
//{}

/// @brief Compute Vision Line Component
/// @param 
/// @param
template <class datat, short N>
void SoC<datat, N>::Define_VLC(datat T_mod, datat T_freq, datat T_phas)
{
    //for (datat t = 0; t <= T/Ts; t++)     //Create time vector simulation
    //{
    //    mu[i] += std::complex<datat>(mod[i], 0) * exp(std::complex<datat>(0, 2 * PI * freq[i] + phas[i])); //time vector not implemented
    //}
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

    for (short i = 0; i <= N; i++)
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
    double sum_mod = 0;

    for (short i = 0; i <= (N - 1); i++)
    {
        sum_mod += mod[i] * mod[i];
    }

    mod[N] = sqrt(2 * sig * sig - sum_mod);
}