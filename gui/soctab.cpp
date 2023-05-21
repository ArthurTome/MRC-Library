#include "soctab.h"

SoCTab::SoCTab(QWidget *parent): QWidget(parent)
{
    // Create chart view with the chart
    m_chart = new QChart();
    m_chartSoC = new QChartView(m_chart, this);

    m_ChartLayoutSoC = new QGridLayout();
    m_ChartLayoutSoC->addWidget(m_chartSoC);
    setLayout(m_ChartLayoutSoC);

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    axisX->setTitleText("t(s)");

    axisY = new QValueAxis;
    axisY->setTitleText("Sinal level");
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickAnchor(0);
    axisY->setTickInterval(1);
    axisY->setTickCount(5);

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);

}
