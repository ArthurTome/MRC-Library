#include "mrc_gui.h"
#include "../src/MRC.hpp"


#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include <QtCharts/QLegend>

#include <QtCharts/QLineSeries>

using namespace Qt;

mrc_gui::mrc_gui(QWidget *parent) :
    QWidget(parent)
{
    // Create buttons for ui
    m_buttonLayout = new QGridLayout();
    m_ChartLayoutSoC = new QGridLayout();
    m_ChartLayoutRXX = new QGridLayout();
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
    m_mean_real->setFixedWidth(100);
    m_mean_imag->setFixedWidth(100);
    m_Samples->setRange(0,50000);
    m_Samples->setValue(5000);
    m_freq->setRange(0, 200);
    m_freq->setValue(91);
    m_ts->setDecimals(4);
    m_ts->setValue(0.0001);
    m_N->setValue(21);
    m_sig->setValue(1);
    radio1->setChecked(true);

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
    m_buttonLayout->addWidget(radio1);
    m_buttonLayout->addWidget(radio2);
    m_buttonLayout->addWidget(label_N);
    m_buttonLayout->addWidget(m_N);
    m_buttonLayout->addWidget(label_Samples);
    m_buttonLayout->addWidget(m_Samples);
    m_buttonLayout->addWidget(label_TimeStamp);
    m_buttonLayout->addWidget(m_ts);
    m_buttonLayout->addWidget(label_Freq);
    m_buttonLayout->addWidget(m_freq);
    m_buttonLayout->addWidget(label_Variance);
    m_buttonLayout->addWidget(m_sig);
    m_buttonLayout->addWidget(label_Real);
    m_buttonLayout->addWidget(m_mean_real);
    m_buttonLayout->addWidget(label_Imag);
    m_buttonLayout->addWidget(m_mean_imag);
    m_buttonLayout->addWidget(refreshValues);

    // CONFIGURE LAYOUT CHART SOC
    //m_ChartLayoutSoC->addWidget(label_Chart_SoC, 0, 0);
    //m_ChartLayoutSoC->addWidget(m_chartSoC, 1, 0);

    // CONFIGURE LAYOUT CHART RXX
    //m_ChartLayoutRXX->addWidget(label_Chart_RXX, 0, 0);
    //m_ChartLayoutRXX->addWidget(m_chartRxx, 1, 0);

    // Create chart view with the chart
    m_chart1 = new QChart();
    m_chart2 = new QChart();
    m_chartSoC = new QChartView(m_chart1, this);
    m_chartRxx = new QChartView(m_chart2, this);

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->addLayout(m_buttonLayout, 0, 0, 2, 1);
    //m_mainLayout->addLayout(m_ChartLayoutSoC, 0, 1, 1, 1);
    //m_mainLayout->addLayout(m_ChartLayoutRXX, 1, 1, 1, 1);
    m_mainLayout->addWidget(m_chartSoC, 0, 1, 1, 1);
    m_mainLayout->addWidget(m_chartRxx, 1, 1, 1, 1);
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

    m_chart1->removeAllSeries();
    m_chart2->removeAllSeries();

    // TIME SET
    float t_s = m_ts->value();
    int samples = m_Samples->value();

    // COMPUTE MRC LIBRARY
    //array<complex<float>, samples> soc = {};
    //array<float, samples> rxx = {};

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

    // CREATE POINT VECTOR SOC
    QList<QPointF> dataSoC_r;
    QList<QPointF> dataSoC_i;
    for (int i = 0; i < samples; i++) dataSoC_r.append(QPointF(i * t_s, soc[i].real()));
    for (int i = 0; i < samples; i++) dataSoC_i.append(QPointF(i * t_s, soc[i].imag()));

    // CREATE POINT VECTOR SOC
    QList<QPointF> dataRxx;
    QList<QPointF> dataCRxx;
    QList<QPointF> dataIRxx;
    for (int i = 0; i < samples; i++)
    {
        dataRxx.append(QPointF(i * t_s, rxx[i]));
        dataCRxx.append(QPointF(i * t_s, crxx[i]));
        dataIRxx.append(QPointF(i * t_s, irxx[i]));
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
    penRxx.setBrush(QBrush("orange"));

    penCRxx.setWidth(1);
    penCRxx.setBrush(QBrush("blue"));

    penIRxx.setWidth(1);
    penIRxx.setBrush(QBrush("red"));

    seriesRxx->setPen(penRxx);
    seriesCRxx->setPen(penCRxx);
    seriesIRxx->setPen(penIRxx);

    // RENDER CHART WITH VALUES SOC
    seriesSoC_r->append(dataSoC_r);
    seriesSoC_i->append(dataSoC_i);
    m_chart1->addSeries(seriesSoC_r);
    m_chart1->addSeries(seriesSoC_i);

    m_chart1->legend()->setVisible(true);
    m_chart1->createDefaultAxes();

    // RENDER CHART WITH VALUES RXX
    seriesRxx->append(dataRxx);
    seriesCRxx->append(dataCRxx);
    seriesIRxx->append(dataIRxx);
    m_chart2->addSeries(seriesRxx);
    m_chart2->addSeries(seriesCRxx);
    m_chart2->addSeries(seriesIRxx);
    m_chart2->legend()->setVisible(true);
    m_chart2->createDefaultAxes();
    m_chartSoC->setRenderHint(QPainter::Antialiasing);
    m_chartRxx->setRenderHint(QPainter::Antialiasing);

    delete[] soc;
    delete[] rxx;
    delete[] crxx;
    delete[] irxx;
}
