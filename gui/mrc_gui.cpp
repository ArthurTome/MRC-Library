#include "mrc_gui.h"
#include "../src/MRC.hpp"

#include <cmath>
#include <fftw3.h>

#include <QtWidgets/QPushButton>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

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
    m_mean_real = new QLineEdit();
    m_mean_imag = new QLineEdit();

    // LABELS OBJECTS
    label_N = new QLabel();
    label_Samples = new QLabel();
    label_TimeStamp = new QLabel();
    label_Freq = new QLabel();
    label_Variance = new QLabel();
    label_Real = new QLabel();
    label_Imag = new QLabel();

    // PRESETS AND CONFIGURES
    m_mean_real->setReadOnly(true);
    m_mean_imag->setReadOnly(true);
    m_mean_real->setFixedWidth(120);
    m_mean_imag->setFixedWidth(120);
    m_Samples->setRange(0,100000);
    m_Samples->setValue(4096);
    m_Samples->setFixedWidth(120);
    m_freq->setRange(0, 200);
    m_freq->setValue(91);
    m_freq->setFixedWidth(120);
    m_ts->setDecimals(4);
    m_ts->setValue(0.0001);
    m_ts->setFixedWidth(120);
    m_N->setValue(21);
    m_N->setFixedWidth(120);
    m_sig->setValue(1);
    m_sig->setFixedWidth(120);
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
    m_formLayout->addWidget(label_Real);
    m_formLayout->addWidget(m_mean_real);
    m_formLayout->addWidget(label_Imag);
    m_formLayout->addWidget(m_mean_imag);
    m_formLayout->addWidget(refreshValues);

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->setColumnMinimumWidth(0, 120);
    m_mainLayout->setColumnStretch(1, 10);
    m_mainLayout->addLayout(m_formLayout, 0, 0);
    m_mainLayout->addWidget(tabWidget, 0, 1);
    setLayout(m_mainLayout);

    // ACTIONS
    connect(refreshValues, SIGNAL(clicked()), this, SLOT(refreshValues()));
}

mrc_gui::~mrc_gui()
{
    delete A;       //
    delete B;       // DELETE TAB
    delete C;       //
}

void mrc_gui::refreshValues()
{
    // GET INPUTS
    float t_s = m_ts->value();
    float freq = m_freq->value();
    float sig = m_sig->value();
    unsigned long samples = m_Samples->value();

    // COMPUTE MRC LIBRARY
    soc  = new complex<float>[samples];         //
    rxx  = new complex<float>[samples];         //
    fft  = new complex<float>[samples];         // GET MEMORY
    irxx = new complex<float>[samples];         //
    crxx = new complex<float>[samples];         //

    float mu_r = 0;
    float mu_i = 0;

    // CLASS CALLS MRC
    SoC <float> floatSoC(m_N->value(), freq, sig);
    if (radio1->isChecked()) floatSoC.Comp_EMEDS();
    if (radio2->isChecked()) floatSoC.Comp_GMEA();
    floatSoC.Comp_SoC(&soc[0], samples, t_s);                                       // Calculate SoC
    floatSoC.NRXX(&soc[0], &rxx[0], samples, sig);                                  // Calculate numeric correlation
    floatSoC.CRXX(&soc[0], &crxx[0], samples, sig);
    floatSoC.IRXX(&irxx[0], samples, sig, t_s);                                     // Calculate ideal correlation
    mu_r = floatSoC.Mean_SoC(&soc[0], samples, true);
    mu_i = floatSoC.Mean_SoC(&soc[0], samples, false);

    // WRITE STATS VALUES ON GUI
    m_mean_real->setText(QString::number(mu_r, 'f', 7));
    m_mean_imag->setText(QString::number(mu_i, 'f', 7));

    // FFT
    fftwf_plan p; // Plan
    p = fftwf_plan_dft_1d(samples, reinterpret_cast<fftwf_complex*>(&rxx[0]),
                                   reinterpret_cast<fftwf_complex*>(&fft[0]),
                                   FFTW_FORWARD, FFTW_ESTIMATE);
    fftwf_execute(p);
    fftwf_destroy_plan(p);
    fft_shift(&fft[0], samples);            // CENTRALIZE FREQUENCY

    // CREATE POINT VECTOR SOC AND RXX
    QList<QPointF> dataPSD   ;
    QList<QPointF> dataIRxx  ;
    QList<QPointF> dataCRxx  ;
    QList<QPointF> dataRxx   ;
    QList<QPointF> dataSoC_i ;
    QList<QPointF> dataSoC_r ;

    // CONVERT VECTOR IN QT POINTS
    for (unsigned long i = 0; i < samples; i++) {
        dataSoC_r.append(QPointF(i * t_s, soc[i].real()));
        dataSoC_i.append(QPointF(i * t_s, soc[i].imag()));
        dataRxx.append(QPointF(i * t_s, rxx[i].real()));
        dataCRxx.append(QPointF(i * t_s, crxx[i].real()));
        dataIRxx.append(QPointF(i * t_s, irxx[i].real()));
        dataPSD.append(QPointF((i - (float)samples/2.0) / ((float)samples * t_s), abs(fft[i])));
    }

    // UPDATE CHARTS
    A->SoCTab::Update_View(&dataSoC_r, &dataSoC_i, sig, (float)samples*t_s);
    B->RxxTab::Update_View(&dataRxx, &dataCRxx, &dataIRxx, (float)samples*t_s);
    C->PSDTab::Update_View(&dataPSD, freq);

    // DELETE MEMORY
    delete[] soc;
    delete[] rxx;
    delete[] fft;
    delete[] irxx;
    delete[] crxx;
}

/// \brief mrc_gui::fft_shift centralize vectors
/// \param A FFT VECTOR
/// \param size SIZE OF VECTOR
void mrc_gui::fft_shift(complex<float>* A, unsigned long size){
    unsigned long fr = floor((size + 1)/2);
    complex<float> t = {0, 0};

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
        A[fr - 1] = complex<float>(0, 0);;
    }
}
