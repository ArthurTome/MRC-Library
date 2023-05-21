#ifndef RXXTAB_H
#define RXXTAB_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QValueAxis>

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

#endif // RXXTAB_H
