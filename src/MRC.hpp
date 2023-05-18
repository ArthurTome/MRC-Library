#ifndef MRC_HPP
#define MRC_HPP

#include <complex>
#include <cmath>
#include <random>
//#include <array>

using namespace std;

/// @brief class for simulation based on sum of cisoids
/// OBS: The time vector, despite being correctly defined, 
/// for reasons of rounding the expression (t/ts) has one 
/// less element than the theoretical
/// @param datat the type for class, float or double
template <class datat> 
class SoC{
    /* data */
    // Model parameters for the compute
    public:
    datat *mod;                                         // Pointer to route amplitude
    datat *freq;                                        // Pointer to doppler frequency
    datat *phas;                                        // Pointer to phase deviation

    datat freq_max;                                     // Max Frequency
    datat sig;                                          // Standard Deviation
    datat mean;                                         // Mean of log process
    short N;                                            // Number of cisoids

    /* functions */

    /// @brief Construct to class, initialize arrays of parameters
    /// @param N Size of parameters arrays
    /// @param freq_t frequency maximum
    /// @param sig_t standard deviarion
    SoC(short N_t, datat freq_t, datat sig_t):freq_max(freq_t), sig(sig_t),mean(0),N(N_t)
    {
        mod  = new datat[N];                            // Initialize route amplitude array
        freq = new datat[N];                            // Initialize doppler frequency array
        phas = new datat[N];                            // Initialize phase deviation array

        for (int i = 0; i < N; i++) {
            mod[i] = 0;
            freq[i] = 0;
            phas[i] = 0;
        }
    }

    SoC(short N_t, datat freq_t, datat sig_t, datat mean_t):freq_max(freq_t), sig(sig_t),mean(0),N(N_t)
    {
        mod  = new datat[N];                            // Initialize route amplitude array
        freq = new datat[N];                            // Initialize doppler frequency array
        phas = new datat[N];                            // Initialize phase deviation array

        for (int i = 0; i < N; i++) {
            mod[i] = 0;
            freq[i] = 0;
            phas[i] = 0;
        }
    }

    ~SoC()
    {
        delete[] mod;
        delete[] freq;
        delete[] phas;
    }

    /// @brief Compute Jakes Ideal Auto Correlation 
    /// @param rxx Pointer to external rxx buffer
    /// @param size legth of vector rxx
    /// @param ts time step
    void IRXX(datat* rxx, datat size, datat ts)
    {
        //int num = (t / ts) + 1;             // length for time, [0, t - ts]
        for (int t_i = 0; t_i < size + 1; t_i++)
        {
            //rxx[t_i] = 0;
            rxx[t_i] = pow(sig, 2) * cyl_bessel_j(0, 2 * M_PI * freq_max * t_i * ts);
        }
    }

    /// @brief Compute Model Auto Correlation 
    /// @param rxx Pointer to external irxx buffer
    /// @param size legth of vector rxx
    /// @param ts time step
    void RXX(datat* rxx, datat size, datat ts) {
        //int num = (t / ts) + 1;
        for (int t_i = 0; t_i < size + 1; t_i++)
        {
            rxx[t_i] = 0;
            for (short i = 0; i < N; i++)                       //Compute 
            {
                //C1*EXP(i*[2pi*F*t + Theta])
                rxx[t_i] += cos(2 * M_PI * freq[i] * t_i * ts) * pow(mod[i],2)/2;
            }
        }
    }

    /// @brief Compute Numeric Model Auto Correlation 
    /// ref. https://mathworld.wolfram.com/Autocorrelation.html
    /// @param soc Pointer to external soc buffer
    /// @param rxx Pointer to external rxx buffer
    /// @param size Legth of vector rxx and soc
    void NRXX(complex<datat>* soc ,datat* rxx ,datat size) {
        //int s_soc = (t / ts) + 1;

        for (int t_i = 0; t_i < size + 1; t_i++)
        {
            rxx[t_i] = 0;
            for (short i = t_i; i < size + 1 ; i++)
            {
                rxx[t_i] += (soc[i-t_i] * conj(soc[i])).real() / (2 * size);
            }
        }                    
    }

    /// @brief Compute Numeric Model Cross Correlation
    /// ref. https://mathworld.wolfram.com/Autocorrelation.html
    /// @param soc Pointer to external soc buffer
    /// @param rxx Pointer to external rxx buffer
    /// @param size Legth of vector rxx and soc
    void CRXX (complex<datat>* soc, datat* rxx, int size) {
        //int s_soc = (t / ts) + 1;

        for (int t_i = 0; t_i < size + 1; t_i++)
        {
            rxx[t_i] = 0;
            for (short i = t_i; i < size + 1 ; i++)
            {
                rxx[t_i] += (soc[i-t_i].real() * soc[i].imag()) / (2 * size);
            }
        } 
    }

    /// @brief Compute statistical properties of SoC
    /// @param soc Pointer to external soc buffer
    datat Mean_SoC(complex<datat>* soc, int size, bool rc_p)
    {
        auto mu = 0;
        for (int i = 0; i < size + 1; i++){
            mu += (rc_p) ? soc[i].real():soc[i].imag();
        }


        return mu/(float)size;
    }


    datat Var_SoC(complex<datat>* soc, int size, bool rc_p)
    {
        datat mu_t = Mean_SoC(soc, size, rc_p);
        auto var = 0;
        for (int i = 0; i < size + 1; i++){
            var += (rc_p) ? pow(soc[i].real() - mu_t, 2) :pow(soc[i].imag() - mu_t, 2);
        }

        return var/(float)size;
    }


    datat PSD_SoC(complex<datat>* soc, int size)
    {
        datat mu = 0;
        for (int i = 0; i < size + 1; i++){
            mu += abs(soc[i]);
        }

        return mu;
    }
    
    /// @brief Compute Sum of Cisoids model taking an empty pointer and returning it filled
    /// @param mu_t Pointer to external SoC buffer
    /// @param size legth of vector rxx
    /// @param ts time step
    void Comp_SoC(complex<datat>* soc, int size, datat ts) {
        //int num = size + 1;
        Comp_phas();

        for (int t_i = 0; t_i < size + 1; t_i++)
        {
            soc[t_i] = 0;
            for (short i = 0; i < N; i++)                     //Compute 
            {
                //C1*EXP(i*[2pi*F*t + Theta])
                soc[t_i] += complex<datat>(mod[i], 0) * exp(complex<datat>(0, 2 * M_PI * freq[i] * (t_i * ts) + phas[i]));
            }
        }
    }

    /// @brief Compute Vision Line Component
    /// @param vlc Pointer to external Line of Sight buffer
    /// @param size legth of vector vlc
    /// @param ts time step
    /// @param t_mod amplitude component for Line of Sight
    /// @param t_freq frequecy component for Line of Sight
    /// @param t_phas phase component for Line of Sight
    void Define_VLC(complex<datat>* vlc, datat size, datat ts, datat t_mod, datat t_freq, datat t_phas)
    {
        //int num = (t / ts) + 1;
        for (int t_i = 0; t_i < size + 1; t_i++)                       //Create time vector simulation
        {
            vlc[t_i] += complex<datat>(t_mod, 0) * exp(complex<datat>(0, 2 * M_PI * t_freq * (t_i * ts) + t_phas));
        }
    }

    /// @brief Compute Phase
    void Comp_phas() {
        random_device rd;  //Will be used to obtain a seed for the random number engine
        mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        uniform_real_distribution<datat> distrib(0, 2 * M_PI);
    
        for (short i = 0; i < N; i++)
        {
            phas[i] = distrib(gen);
        }
    
    }
    
    /// @brief Compute Parameters by Extended Method of Exact Doppler Spread (EMEDS)
    void Comp_EMEDS()
    {
        for (short i = 1; i < N + 1; i++)
        {
            mod[i - 1] = sig * sqrt(2.0 / (datat)N);
            freq[i - 1] = freq_max * cos((i - 0.25) * (2 * M_PI / (datat)N));
        }
    }
    /// @brief Compute Parameters by Method of Equal Areas (MEA) 
    void Comp_GMEA()
    {
        for (short i = 1; i < N + 1; i++)
        {
            mod[i - 1] = sig * sqrt(2 / (datat)N);                //A same of EMEDS
            freq[i - 1] = freq_max * sin(M_PI * i / (2 * (datat)N));
        }
    }

    void Log_Process(datat* log, complex<datat>* soc_t, datat size, datat mean, datat sig) {

        for (int t_i = 0; t_i < size; t_i++) log[t_i] = exp(sig * real(soc_t[t_i]) + mean);
    }
};

#endif
