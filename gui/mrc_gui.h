#ifndef MRC_GUI_H
#define MRC_GUI_H

#include <QtWidgets>

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtCharts/QLineSeries>


using namespace Qt;

class mrc_gui : public QWidget
{
    Q_OBJECT
public:
    explicit mrc_gui(QWidget *parent = 0);
    ~mrc_gui();

public Q_SLOTS:
    void refreshValues();

private:
    QChart *m_chart1;
    QChart *m_chart2;
    QChartView *m_chartSoC;
    QChartView *m_chartRxx;
    QList<QLineSeries *> m_seriesSoC;
    QList<QLineSeries *> m_seriesRxx;
    QList<QLineSeries *> m_seriesIRxx;
    QList<QLineSeries *> m_seriesCRxx;

    QGridLayout *m_mainLayout;
    QGridLayout *m_ChartLayoutSoC;
    QGridLayout *m_ChartLayoutRXX;
    QGridLayout *m_buttonLayout;

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
