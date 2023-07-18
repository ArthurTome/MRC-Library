# MRC-Library
This is a study project to develop a modern C++ library for simulating mobile radio channels based on the Sum of Cisoids method (and correlated methods).

### Bibliography
1. Patzold, Matthias. Mobile Radio Channels 2º.

### Example

Initially, set the parameters for which the class will calculate the signal: number of sinusoids, the quantity of terms in the sum, frequency and maximum frequency that make up the signal, sig and the standard deviation of the signal, ts and the time step used by the class, and sz, short for 'size,' the number of points that will compose the signal. The quantity sz * ts constitutes the time interval of the signal

```cpp
    short N = 21;                           // Nº Cisoids
    double freq = 91;                       // M Frequency
    double sig = 1;                         // Standart Deviation
    double ts = 0.0001;                     // Time step
    unsigned long sz = 8192;                // Size Vector
```
The class operates using pointers and does not allocate memory for the signal, only a small internal quantity to create the sum terms and parameters. Therefore, you should create an array and pass its reference to the class. Here, two terms named 'soc' and 'rxx' are created for filling with the signal and its correlation data.

```cpp
    // Get memory
    complex<double>* soc = new complex<double>[sz]();
    complex<double>* rxx = new complex<double>[sz]();
```
MRC is a template class and is compatible with the 'double' and 'float' data types. The compiler will likely produce an error if any other data type is used. 'SoC<datat> dSoC(N, freq, sig)' creates an instance of the class, where 'datat' is replaced with the data type 'float', and it preconfigures it with the parameters. 'dSoC.Comp_model' performs the calculation of the frequency modulus terms for each term, with 'model' being replaced by either 'EMEDS' or 'GMEA', so far, both methods are used for parameter calculation. For more details, please consult the reference book."

```cpp
    SoC <double> dSoC(N, freq, sig);        // Initialize class <float>
    dSoC.Comp_EMEDS();                      // EMEDS
    // or
    dSoC.Comp_GMEA();                       // GMEA

```
The class provides several output methods. If the intention is only to calculate the signal, simply use 'dSoC.Comp_SoC(&soc, sz, ts)', passing the memory reference and the information of its size and time step. The method 'dSoC.NRXX' uses the generated signal to calculate its autocorrelation. Similar to the previous method, it requires the memory information and size, and additionally, the standard deviation for normalization.

```cpp
    dSoC.Comp_SoC(&soc[0], sz, ts);         // Compute Sum os Cisoids
    dSoC.NRXX(&soc[0], &rxx[0], sz, sig);   // Compute numeric correlation
```
If dynamic allocation is used, remember to delete at the end of its usage. In the case of recalculating the class, it will reset the vectors point by point before filling them again.

```cpp
    delete[] soc;                           // Delete memory
    delete[] rxx;                           //
```