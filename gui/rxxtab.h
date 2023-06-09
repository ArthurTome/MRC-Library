#ifndef RXXTAB_H
#define RXXTAB_H

#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>

using namespace Qt;

class RxxTab : public QWidget
{
    Q_OBJECT

public:
    explicit RxxTab(QWidget *parent = nullptr);
    void Update_View(QList<QPointF> *Rxx, QList<QPointF> *CRxx, QList<QPointF> *NRxx, float max_t);

    QChart *m_chart;
    QChartView *m_chartRxx;
    QGridLayout *m_ChartLayoutRXX;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QLineSeries *seriesRxx;
    QLineSeries *seriesCRxx;
    QLineSeries *seriesIRxx;

public slots:
    void ShowContextMenu(const QPoint &pos);
    void Save_Img();

};

#endif // RXXTAB_H
