#include "mrc_gui.h"
#include "../src/MRC.hpp"
#include <complex>
#include <fftw3.h>

#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QSpacerItem>

using namespace Qt;

SoCTab::SoCTab(QWidget *parent): QWidget(parent)
{
    // Create chart view with the chart
    m_chart = new QChart();
    m_chartSoC = new QChartView(m_chart, this);

    m_ChartLayoutSoC = new QGridLayout();

    //QVBoxLayout *TabLayout = new QVBoxLayout;
    m_ChartLayoutSoC->addWidget(m_chartSoC);
    setLayout(m_ChartLayoutSoC);

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    //axisX->setLabelFormat("%g");
    axisX->setTitleText("t(s)");

    axisY = new QValueAxis;
    axisY->setTitleText("Sinal level");
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickAnchor(5);
    axisY->setTickInterval(1);

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);

}

RxxTab::RxxTab(QWidget *parent): QWidget(parent)
{
    m_chart = new QChart();
    m_chartRxx = new QChartView(m_chart, this);

    m_ChartLayoutRXX = new QGridLayout();

    //QVBoxLayout *TabLayout = new QVBoxLayout;
    m_ChartLayoutRXX->addWidget(m_chartRxx);
    setLayout(m_ChartLayoutRXX);

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    //axisX->setLabelFormat("%g");
    axisX->setTitleText("tal(s)");

    axisY = new QValueAxis;
    axisY->setTitleText("Correlation");
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickAnchor(-0.5);
    axisY->setTickInterval(0.25);

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);

}

PSDTab::PSDTab(QWidget *parent): QWidget(parent)
{
    // Create chart view with the chart
    m_chart = new QChart();
    m_chartPSD = new QChartView(m_chart, this);

    m_ChartLayoutPSD = new QGridLayout();

    //QVBoxLayout *TabLayout = new QVBoxLayout;
    m_ChartLayoutPSD->addWidget(m_chartPSD);
    setLayout(m_ChartLayoutPSD);

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    axisX->setLabelFormat("%g");
    axisX->setTitleText("w");


    axisY = new QValueAxis;
    axisY->setTitleText("Power");

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);

}

mrc_gui::mrc_gui(QWidget *parent) :
    QWidget(parent)
{
    // tab layouyt
    tabWidget = new QTabWidget;
    tabWidget -> addTab(&A, tr("Channel"));
    tabWidget -> addTab(&B, tr("Correlate"));
    tabWidget -> addTab(&C, tr("PSD"));

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
    label_Chart_SoC = new QLabel();
    label_Chart_RXX = new QLabel();

    // PRESETS AND CONFIGURES
    m_mean_real->setReadOnly(true);
    m_mean_imag->setReadOnly(true);
    m_mean_real->setFixedWidth(120);
    m_mean_imag->setFixedWidth(120);
    m_Samples->setRange(0,50000);
    m_Samples->setValue(5000);
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
    label_Chart_SoC->setText("Sum of Cisoids Chart");
    label_Chart_RXX->setText("Correlation Chart");

    // CONFIGURE LAYOUT INPUT
    connect(refreshValues, SIGNAL(clicked()), this, SLOT(refreshValues()));
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

    // CONFIGURE LAYOUT CHART SOC
    //m_ChartLayoutSoC->addWidget(label_Chart_SoC, 0, 0);
    //m_ChartLayoutSoC->addWidget(m_chartSoC, 1, 0);

    // CONFIGURE LAYOUT CHART RXX
    //m_ChartLayoutRXX->addWidget(label_Chart_RXX, 0, 0);
    //m_ChartLayoutRXX->addWidget(m_chartRxx, 1, 0);

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->setColumnMinimumWidth(0, 120);
    //m_mainLayout->setColumnStretch(0, 0);
    m_mainLayout->setColumnStretch(1, 10);
    m_mainLayout->addLayout(m_formLayout, 0, 0);
    //m_mainLayout->addLayout(m_ChartLayoutSoC, 0, 1, 1, 1);
    //m_mainLayout->addLayout(m_ChartLayoutRXX, 1, 1, 1, 1);
    m_mainLayout->addWidget(tabWidget, 0, 1);
    //m_mainLayout->addWidget(m_chartSoC, 0, 1, 1, 1);
    //m_mainLayout->addWidget(m_chartRxx, 1, 1, 1, 1);
    setLayout(m_mainLayout); 
}

mrc_gui::~mrc_gui()
{

}

void mrc_gui::refreshValues()
{
    if (!m_seriesSoC.isEmpty()) m_seriesSoC.clear();
    if (!m_seriesRxx.isEmpty()) m_seriesRxx.clear();
    if (!m_seriesIRxx.isEmpty()) m_seriesIRxx.clear();
    if (!m_seriesCRxx.isEmpty()) m_seriesCRxx.clear();
    if (!m_seriesPSD.isEmpty()) m_seriesPSD.clear();

    // TIME SET
    float t_s = m_ts->value();
    int samples = m_Samples->value();

    // COMPUTE MRC LIBRARY
    complex<float>* soc = new complex<float>[samples];
    float* rxx = new float[samples];
    float* irxx = new float[samples];
    float* crxx = new float[samples];
    float mu_r = 0;
    float mu_i = 0;

    // CLASS CALLS
    SoC <float> floatSoC(m_N->value(), m_freq->value(), m_sig->value());
    if (radio1->isChecked()) floatSoC.Comp_EMEDS();
    if (radio2->isChecked()) floatSoC.Comp_GMEA();
    floatSoC.Comp_SoC(&soc[0], samples, t_s);                                   // Calculate SoC
    floatSoC.NRXX(&soc[0], &rxx[0], samples);                                   // Calculate numeric correlation
    floatSoC.CRXX(&soc[0], &crxx[0], samples);
    floatSoC.IRXX(&irxx[0], samples, t_s);                                      // Calculate ideal correlation
    mu_r = floatSoC.Mean_SoC(&soc[0], samples, true);
    mu_i = floatSoC.Mean_SoC(&soc[0], samples, false);

    // FFT
    fftwf_complex *out = new fftwf_complex [samples]; /* Output */
    //float *out = new float[samples];
    fftwf_plan p; /* Plan */

    p = fftwf_plan_dft_r2c_1d(samples, &rxx[0], &out[0], FFTW_ESTIMATE);

    fftwf_execute(p);

    fftwf_destroy_plan(p);

    // CREATE POINT VECTOR SOC AND RXX
    QList<QPointF> dataSoC_r = {};
    QList<QPointF> dataSoC_i = {};
    QList<QPointF> dataRxx = {};
    QList<QPointF> dataCRxx = {};
    QList<QPointF> dataIRxx = {};
    QList<QPointF> dataPSD = {};

    for (int i = 0; i < samples; i++) {
        dataSoC_r.append(QPointF(i * t_s, soc[i].real()));
        dataSoC_i.append(QPointF(i * t_s, soc[i].imag()));
        dataRxx.append(QPointF(i * t_s, rxx[i]));
        dataCRxx.append(QPointF(i * t_s, crxx[i]));
        dataIRxx.append(QPointF(i * t_s, irxx[i]));
    }

    for (int i = 0; i < samples / 2 + 1; i++) {
        dataPSD.append(QPointF(i, out[i][0]));
    }

    // WRITE STATS VALUES ON GUI
    m_mean_real->setText(QString::number(mu_r, 'f', 7));
    m_mean_imag->setText(QString::number(mu_i, 'f', 7));

    // CREATE LINE SOC
    QLineSeries *seriesSoC_r = new QLineSeries();
    m_seriesSoC.append(seriesSoC_r);

    QLineSeries *seriesSoC_i = new QLineSeries();
    m_seriesSoC.append(seriesSoC_i);

    QLineSeries *seriesRxx = new QLineSeries();
    m_seriesRxx.append(seriesRxx);

    QLineSeries *seriesCRxx = new QLineSeries();
    m_seriesCRxx.append(seriesCRxx);

    QLineSeries *seriesIRxx = new QLineSeries();
    m_seriesIRxx.append(seriesIRxx);

    QLineSeries *seriesPSD = new QLineSeries();
    m_seriesIRxx.append(seriesPSD);

    // LABELS
    seriesSoC_r->setName("Real");
    seriesSoC_i->setName("Imag");

    seriesRxx->setName("AutoCorr");
    seriesCRxx->setName("CrossCorr");
    seriesIRxx->setName("JakesCorr");

    // LINE ADJUSTMENTS FOR SOC
    QPen penSoC_r = seriesSoC_r->pen();
    QPen penSoC_i = seriesSoC_i->pen();

    penSoC_r.setWidth(1);
    penSoC_r.setBrush(QBrush("red"));

    penSoC_i.setWidth(1);
    penSoC_i.setBrush(QBrush("blue"));

    seriesSoC_r->setPen(penSoC_r);
    seriesSoC_i->setPen(penSoC_i);

    // LINE ADJUSTMENTS FOR RXX
    QPen penRxx = seriesRxx->pen();
    QPen penCRxx = seriesCRxx->pen();
    QPen penIRxx = seriesIRxx->pen();

    penRxx.setWidth(1);
    penRxx.setBrush(QBrush("red"));
    penCRxx.setWidth(1);
    penCRxx.setBrush(QBrush("blue"));
    penIRxx.setWidth(1);
    penIRxx.setBrush(QBrush("orange"));

    seriesRxx->setPen(penRxx);
    seriesCRxx->setPen(penCRxx);
    seriesIRxx->setPen(penIRxx);

    // Reset series values
    A.m_chart->removeAllSeries();
    B.m_chart->removeAllSeries();
    C.m_chart->removeAllSeries();

    // RENDER CHART WITH VALUES SOC
    seriesSoC_r->append(dataSoC_r);
    seriesSoC_i->append(dataSoC_i);
    A.m_chart->addSeries(seriesSoC_r);
    A.m_chart->addSeries(seriesSoC_i);
    A.m_chart->legend()->setVisible(true);
    A.m_chart->setTitle("Sinal SoC");
    A.m_chartSoC->setRenderHint(QPainter::Antialiasing);

    seriesSoC_r->attachAxis(A.axisX);
    seriesSoC_r->attachAxis(A.axisY);

    seriesSoC_i->attachAxis(A.axisX);
    seriesSoC_i->attachAxis(A.axisY);

    A.axisX->setRange(0, samples*t_s);
    A.axisY->setRange(-5, 5);

    // RENDER CHART WITH VALUES RXX
    seriesRxx->append(dataRxx);
    seriesCRxx->append(dataCRxx);
    seriesIRxx->append(dataIRxx);
    B.m_chart->addSeries(seriesRxx);
    B.m_chart->addSeries(seriesCRxx);
    B.m_chart->addSeries(seriesIRxx);
    B.m_chart->legend()->setVisible(true);
    B.m_chartRxx->setRenderHint(QPainter::Antialiasing);

    seriesRxx->attachAxis(B.axisX);
    seriesRxx->attachAxis(B.axisY);

    seriesCRxx->attachAxis(B.axisX);
    seriesCRxx->attachAxis(B.axisY);

    seriesIRxx->attachAxis(B.axisX);
    seriesIRxx->attachAxis(B.axisY);

    B.axisX->setRange(0, samples*t_s);
    B.axisY->setRange(-0.5, 1);

    B.m_chart->setTitle("Correlation SoC");

    // RENDER PSD
    seriesPSD->append(dataPSD);
    C.m_chart->addSeries(seriesPSD);
    C.m_chartPSD->setRenderHint(QPainter::Antialiasing);
    seriesPSD->attachAxis(C.axisX);
    seriesPSD->attachAxis(C.axisY);

    delete[] soc;
    delete[] rxx;
    delete[] crxx;
    delete[] irxx;
    delete[] out;
}
