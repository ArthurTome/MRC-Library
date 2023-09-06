#include "mrc_gui.h"
#include "../mrc/mrc.hpp"

#include <cmath>
#include <fftw3.h>
#include <chrono>

#include <QtWidgets/QPushButton>
#include <QtCharts/QLegend>

#include <QSpacerItem>

using namespace Qt;
using namespace std;

mrc_gui::mrc_gui(QWidget *parent) :
    QWidget(parent)
{
    A = new SoCTab();                           //
    B = new RxxTab();                           // CREATE TAB GRAPH
    C = new PSDTab();                           //

    // tab layouyt
    tabWidget = new QTabWidget;
    tabWidget -> addTab(A, tr("Channel"));      //
    tabWidget -> addTab(B, tr("Correlate"));    // ATACTH TAB TO MAIN LAYOUT
    tabWidget -> addTab(C, tr("PSD"));          //

    // Create buttons for ui
    m_formLayout = new QFormLayout();
    QPushButton *refreshValues = new QPushButton("Refresh Values");
    radio1 = new QRadioButton(tr("EMEDS"));
    radio2 = new QRadioButton(tr("GMEA"));

    // LAYOUT OBJECTS
    m_N = new QSpinBox();
    m_Samples = new QSpinBox();
    m_ts = new QDoubleSpinBox();
    m_freq = new QDoubleSpinBox();
    m_sig  = new QDoubleSpinBox();
    m_rep  = new QDoubleSpinBox();
    m_mean_real = new QLineEdit();
    m_mean_imag = new QLineEdit();
    m_execT = new QLineEdit();

    // LABELS OBJECTS
    label_N = new QLabel();
    label_Samples = new QLabel();
    label_TimeStamp = new QLabel();
    label_Freq = new QLabel();
    label_Variance = new QLabel();
    label_Real = new QLabel();
    label_Imag = new QLabel();
    label_Rep = new QLabel();
    label_ExecT = new QLabel();

    // PRESETS AND CONFIGURES
    m_mean_real->setReadOnly(true);
    m_mean_imag->setReadOnly(true);
    m_mean_real->setFixedWidth(120);
    m_mean_imag->setFixedWidth(120);
    m_Samples->setRange(0,100000);
    m_Samples->setValue(4096);
    m_Samples->setFixedWidth(120);
    m_freq->setRange(0, 1000);
    m_freq->setValue(91);
    m_freq->setFixedWidth(120);
    m_ts->setDecimals(4);
    m_ts->setValue(0.0001);
    m_ts->setFixedWidth(120);
    m_N->setValue(21);
    m_N->setRange(21, 1000);
    m_N->setFixedWidth(120);
    m_sig->setValue(1);
    m_sig->setFixedWidth(120);
    m_rep->setValue(1);
    m_rep->setRange(0, 1000);
    m_rep->setFixedWidth(120);
    radio1->setChecked(true);
    refreshValues->setFixedWidth(120);

    // LABELS NAMES
    label_N->setText("N. Cisoids");
    label_Samples->setText("Samples");
    label_TimeStamp->setText("TimeStamp");
    label_Freq->setText("Frequency");
    label_Variance->setText("Variance");
    label_Real->setText("Real Mean");
    label_Imag->setText("Imag Mean");
    label_Rep->setText("Repetitions");
    label_ExecT->setText("Exec. Time");

    // CONFIGURE LAYOUT INPUT
    m_formLayout->addWidget(radio1);
    m_formLayout->addWidget(radio2);
    m_formLayout->addWidget(label_N);
    m_formLayout->addWidget(m_N);
    m_formLayout->addWidget(label_Samples);
    m_formLayout->addWidget(m_Samples);
    m_formLayout->addWidget(label_TimeStamp);
    m_formLayout->addWidget(m_ts);
    m_formLayout->addWidget(label_Freq);
    m_formLayout->addWidget(m_freq);
    m_formLayout->addWidget(label_Variance);
    m_formLayout->addWidget(m_sig);
    m_formLayout->addWidget(label_Rep);
    m_formLayout->addWidget(m_rep);
    m_formLayout->addWidget(label_Real);
    m_formLayout->addWidget(m_mean_real);
    m_formLayout->addWidget(label_Imag);
    m_formLayout->addWidget(m_mean_imag);
    m_formLayout->addWidget(label_ExecT);
    m_formLayout->addWidget(m_execT);

    m_formLayout->addWidget(refreshValues);

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->setColumnMinimumWidth(0, 120);
    m_mainLayout->setColumnStretch(1, 10);
    m_mainLayout->addLayout(m_formLayout, 0, 0);
    m_mainLayout->addWidget(tabWidget, 0, 1);
    setLayout(m_mainLayout);

    // ACTIONS
    connect(refreshValues, SIGNAL(clicked()), this, SLOT(RefreshValues()));
}

mrc_gui::~mrc_gui()
{
    delete A;       //
    delete B;       // DELETE TAB
    delete C;       //
}

/// \brief mrc_gui::refreshValues generate and update tabs
///
void mrc_gui::RefreshValues()
{
    // GET INPUTS
    double t_s = m_ts->value();                                 // Time step
    double freq = m_freq->value();                              // Frequency
    double sig = m_sig->value();                                // Standard Deviation
    double N = m_N->value();                                    // Nº cisoides
    unsigned long samples = m_Samples->value();                 // Nº samples
    double rep = m_rep->value();                                // Nº repetitions
    double tmax = N/(2 * freq);

    // COMPUTE MRC LIBRARY
    soc  = new complex<double>[samples]();                      //
    rxx  = new complex<double>[samples]();                      //
    rxx_t= new complex<double>[samples]();                      //
    fft  = new complex<double>[samples]();                      // GET MEMORY
    irxx = new complex<double>[samples]();                      //
    ifft = new complex<double>[samples]();                      //
    crxx = new complex<double>[samples]();                      //

    float mu_r = 0;
    float mu_i = 0;

    // CLASS CALLS MRC
    auto start = chrono::high_resolution_clock::now();          // GET INIT TIME
    SoC <double> floatSoC(N, freq, sig);
    if (radio1->isChecked()) floatSoC.Comp_EMEDS();
    if (radio2->isChecked()) floatSoC.Comp_GMEA();

    for (int i = 0; i < rep; i++)
    {
        floatSoC.Comp_SoC(&soc[0], samples, t_s);               // Calculate SoC
        floatSoC.NRXX(&soc[0], &rxx_t[0], samples, sig);        // Calculate  N. correlation
        for (unsigned long t_i = 0; t_i < samples; t_i ++)
        {
            // A[i]/A[0] Normalization to fix scaling issues
            rxx[t_i] = (i == 0) ? (rxx[t_i] = rxx_t[t_i]/rxx_t[0]) : ((rxx_t[t_i]/rxx_t[0] + rxx[t_i])/2.0);
        }
    }

    floatSoC.RXX(&irxx[0], samples, sig, t_s);                 // Calculate ideal correlation
    floatSoC.CRXX(&soc[0], &crxx[0], samples, sig);             // Cross correlation


    mu_r = floatSoC.Mean_SoC(&soc[0], samples, true);
    mu_i = floatSoC.Mean_SoC(&soc[0], samples, false);

    auto stop = chrono::high_resolution_clock::now();           // GET TIME
    auto duration = duration_cast<chrono::microseconds>(stop - start);

    // WRITE TIME VALUES ON GUI
    m_execT->setText(QString::number(duration.count()/1000000.0, 'f', 7));

    // WRITE STATS VALUES ON GUI
    m_mean_real->setText(QString::number(mu_r, 'f', 7));
    m_mean_imag->setText(QString::number(mu_i, 'f', 7));

    // FFT
    fftw_plan p; // Plan
    p = fftw_plan_dft_1d(samples, reinterpret_cast<fftw_complex*>(&rxx[0]),
                                   reinterpret_cast<fftw_complex*>(&fft[0]),
                                   FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);

    p = fftw_plan_dft_1d(samples, reinterpret_cast<fftw_complex*>(&irxx[0]),
                         reinterpret_cast<fftw_complex*>(&ifft[0]),
                         FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    fftw_destroy_plan(p);
    FFT_shift(&fft[0], samples);                                // CENTRALIZE FREQUENCY
    FFT_shift(&ifft[0], samples);                               //

    // CREATE POINT VECTOR SOC AND RXX
    QList<QPointF> dataPSD  ;
    QList<QPointF> dataiPSD ;
    QList<QPointF> dataIRxx ;
    QList<QPointF> dataCRxx ;
    QList<QPointF> dataRxx  ;
    QList<QPointF> dataSoC_i;
    QList<QPointF> dataSoC_r;

    // CONVERT VECTOR IN QT POINTS
    for (unsigned long i = 0; i < samples; i++) {
        dataSoC_r.append(QPointF(i * t_s, soc[i].real()));
        dataSoC_i.append(QPointF(i * t_s, soc[i].imag()));
        dataRxx.append(QPointF(i * t_s, rxx[i].real()));
        dataCRxx.append(QPointF(i * t_s, crxx[i].real()));
        dataIRxx.append(QPointF(i * t_s, irxx[i].real()));
        dataPSD.append(QPointF((i - (double)samples/2.0) / ((double)samples * t_s), abs(fft[i])));
        dataiPSD.append(QPointF((i - (double)samples/2.0) / ((double)samples * t_s), abs(ifft[i])));
    }

    // UPDATE CHARTS
    A->SoCTab::Update_View(&dataSoC_r, &dataSoC_i, sig, (double)samples*t_s);
    B->RxxTab::Update_View(&dataRxx, &dataCRxx, &dataIRxx, (double)samples*t_s, tmax);
    C->PSDTab::Update_View(&dataPSD, &dataiPSD, freq);

    // DELETE MEMORY
    delete[] soc;
    delete[] rxx;
    delete[] fft;
    delete[] irxx;
    delete[] crxx;
    delete[] rxx_t;
}

/// \brief mrc_gui::fft_shift centralize vectors
/// \param fftw vector
/// \param size vector size
void mrc_gui::FFT_shift(complex<double>* A, unsigned long size){
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
