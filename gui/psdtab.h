#ifndef PSDTAB_H
#define PSDTAB_H

#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>

using namespace Qt;

class PSDTab : public QWidget
{
    Q_OBJECT

public:
    explicit PSDTab(QWidget *parent = nullptr);
    void Update_View(QList<QPointF> *PSD, float freq);

    QChart *m_chart;
    QChartView *m_chartPSD;
    QGridLayout *m_ChartLayoutPSD;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QLineSeries *seriesPSD;

public slots:
    void ShowContextMenu(const QPoint &pos);
    void Save_Img();

};

#endif // PSDTAB_H
