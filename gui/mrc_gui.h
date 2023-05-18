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
#include <QSpacerItem>
#include <QtCharts/QValueAxis>


using namespace Qt;

class SoCTab : public QWidget
{
    Q_OBJECT

public:
    explicit SoCTab(QWidget *parent = nullptr);

    QChart *m_chart;
    QChartView *m_chartSoC;
    QGridLayout *m_ChartLayoutSoC;
    QValueAxis *axisX;
    QValueAxis *axisY;
};

class RxxTab : public QWidget
{
    Q_OBJECT

public:
    explicit RxxTab(QWidget *parent = nullptr);

    QChart *m_chart;
    QChartView *m_chartRxx;
    QGridLayout *m_ChartLayoutRXX;
    QValueAxis *axisX;
    QValueAxis *axisY;

};

class PSDTab : public QWidget
{
    Q_OBJECT

public:
    explicit PSDTab(QWidget *parent = nullptr);

    QChart *m_chart;
    QChartView *m_chartPSD;
    QGridLayout *m_ChartLayoutPSD;
    QValueAxis *axisX;
    QValueAxis *axisY;

};

class mrc_gui : public QWidget
{
    Q_OBJECT
public:
    explicit mrc_gui(QWidget *parent = 0);
    ~mrc_gui();

public Q_SLOTS:
    void refreshValues();

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
