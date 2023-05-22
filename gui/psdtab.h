#ifndef PSDTAB_H
#define PSDTAB_H

#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QValueAxis>

using namespace Qt;

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

public slots:
    void ShowContextMenu(const QPoint &pos);
    void Save_Img();

};

#endif // PSDTAB_H
