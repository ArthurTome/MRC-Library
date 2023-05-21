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

class mrc_gui : public QWidget
{
    Q_OBJECT
public:
    explicit mrc_gui(QWidget *parent = 0);
    ~mrc_gui();

public Q_SLOTS:
    void refreshValues();
    void fft_shift(complex<float>* A, int size);

private:
    QTabWidget *tabWidget;
    // Tab
    SoCTab A;
    RxxTab B;
    PSDTab C;

    QList<QLineSeries *> m_seriesSoC;
    QList<QLineSeries *> m_seriesRxx;
    QList<QLineSeries *> m_seriesIRxx;
    QList<QLineSeries *> m_seriesCRxx;
    QList<QLineSeries *> m_seriesPSD;

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

    QLabel *label_Chart_SoC;
    QLabel *label_Chart_RXX;
};

#endif // MRC_GUI_H
