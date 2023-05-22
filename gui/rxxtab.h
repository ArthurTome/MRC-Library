#ifndef RXXTAB_H
#define RXXTAB_H

#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QValueAxis>

using namespace Qt;

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

public slots:
    void ShowContextMenu(const QPoint &pos);
    void Save_Img();

};

#endif // RXXTAB_H
