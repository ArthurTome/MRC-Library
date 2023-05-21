#include "psdtab.h"

PSDTab::PSDTab(QWidget *parent): QWidget(parent)
{
    // Create chart view with the chart
    m_chart = new QChart();
    m_chartPSD = new QChartView(m_chart, this);

    m_ChartLayoutPSD = new QGridLayout();
    m_ChartLayoutPSD->addWidget(m_chartPSD);
    setLayout(m_ChartLayoutPSD);

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    axisX->setTitleText("w");
    axisX->setTickAnchor(0);
    axisX->setTickCount(5);

    axisY = new QValueAxis;
    axisY->setTitleText("Power");

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_chart->legend()->setVisible(false);
    m_chart->setTitle("PSD SoC");

}
