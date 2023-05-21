#ifndef SOCTAB_H
#define SOCTAB_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QValueAxis>

using namespace Qt;
using namespace std;

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

#endif // SOCTAB_H
