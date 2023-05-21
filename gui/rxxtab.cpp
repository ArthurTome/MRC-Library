#include "rxxtab.h"

RxxTab::RxxTab(QWidget *parent): QWidget(parent)
{
    m_chart = new QChart();
    m_chartRxx = new QChartView(m_chart, this);

    m_ChartLayoutRXX = new QGridLayout();
    m_ChartLayoutRXX->addWidget(m_chartRxx);
    setLayout(m_ChartLayoutRXX);

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    axisX->setTitleText("tal(s)");

    axisY = new QValueAxis;
    axisY->setTitleText("Correlation");
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickAnchor(-0.5);
    axisY->setTickInterval(0.25);

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);

}
