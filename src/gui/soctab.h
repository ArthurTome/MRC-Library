/**
 * @file soctab.h
 * @brief display tab for sum of cisoids
*/
#ifndef SOCTAB_H
#define SOCTAB_H

#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>

using namespace Qt;

/// @brief Class for creating and organizing the charts in the signal tab.
class SoCTab : public QWidget
{
    Q_OBJECT

public:
    explicit SoCTab(QWidget *parent = nullptr);
    void Update_View(QList<QPointF> *SoC_r, QList<QPointF> *SoC_i, double sig, double max_t);

private:
    QChart *m_chart;
    QChartView *m_chartSoC;
    QGridLayout *m_ChartLayoutSoC;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QLineSeries *seriesSoC_r;
    QLineSeries *seriesSoC_i;

private slots:
    void ShowContextMenu(const QPoint &pos);
    void Save_Img();
};

#endif // SOCTAB_H
