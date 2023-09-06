/**
 * @file rxxtab.h
 * @brief display tab for corralation
*/
#ifndef RXXTAB_H
#define RXXTAB_H

#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>

using namespace Qt;

/// @brief Class for creating and organizing the charts in the correlation tab.
class RxxTab : public QWidget
{
    Q_OBJECT

public:
    explicit RxxTab(QWidget *parent = nullptr);
    void Update_View(QList<QPointF> *Rxx, QList<QPointF> *CRxx, QList<QPointF> *NRxx, double T, double tmax);

private:
    QChart *m_chart;
    QChartView *m_chartRxx;
    QGridLayout *m_ChartLayoutRXX;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QLineSeries *seriesRxx;
    QLineSeries *seriesCRxx;
    QLineSeries *seriesIRxx;

    double tmax;

private slots:
    void ShowContextMenu(const QPoint &pos);
    void Save_Img();
    void Zoom_Tal();
};

#endif // RXXTAB_H
