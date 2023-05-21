#ifndef PSDTAB_H
#define PSDTAB_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QValueAxis>

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

#endif // PSDTAB_H
