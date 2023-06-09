#ifndef MRC_GUI_H
#define MRC_GUI_H

#include "soctab.h"
#include "rxxtab.h"
#include "psdtab.h"

#include <complex>

#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtCharts/QLineSeries>

using namespace Qt;
using namespace std;

class mrc_gui : public QWidget
{
    Q_OBJECT
public:
    explicit mrc_gui(QWidget *parent = 0);
    ~mrc_gui();

    void fft_shift(complex<float>* A, unsigned long size);

public Q_SLOTS:
    void refreshValues();

private:
    QTabWidget *tabWidget;
    // Tab
    SoCTab* A;
    RxxTab* B;
    PSDTab* C;

    // Vectors
    complex<float> *soc;
    complex<float> *rxx;
    complex<float> *irxx;
    complex<float> *crxx;
    complex<float> *fft;

    //QList<QPointF> *dataSoC_r;
    //QList<QPointF> *dataSoC_i;
    //QList<QPointF> *dataRxx;
    //QList<QPointF> *dataCRxx;
    //QList<QPointF> *dataIRxx;
    //QList<QPointF> *dataPSD;

    QGridLayout *m_mainLayout;
    QFormLayout *m_formLayout;

    QSpinBox *m_N;
    QSpinBox *m_Samples;
    QDoubleSpinBox *m_ts;
    QDoubleSpinBox *m_freq;
    QDoubleSpinBox *m_sig;
    QLineEdit *m_mean_real;
    QLineEdit *m_mean_imag;

    QRadioButton *radio1;
    QRadioButton *radio2;

    QLabel *label_N;
    QLabel *label_Samples;
    QLabel *label_TimeStamp;
    QLabel *label_Freq;
    QLabel *label_Variance;
    QLabel *label_Real;
    QLabel *label_Imag;

};

#endif // MRC_GUI_H
