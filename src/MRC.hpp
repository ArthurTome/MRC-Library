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
    void Define_Vision_Comp(datat T_mod, datat T_freq, datat T_phas);
//    void Define_Vector_Size(short v_size);
    void Calc_EMEDS(double sig, double Fmax);
    void Calc_LPNM(double sig, double Fmax);
    datat Get();         // Channel 

};
