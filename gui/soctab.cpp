#include "soctab.h"

SoCTab::SoCTab(QWidget *parent): QWidget(parent)
{
    // Create chart view with the chart
    m_chart = new QChart();
    m_chartSoC = new QChartView(m_chart, this);

    this->setContextMenuPolicy(CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));

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

    m_chart->addAxis(axisX, AlignBottom);
    m_chart->addAxis(axisY, AlignLeft);

}

void SoCTab::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Save Chart", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(Save_Img()));
    contextMenu.addAction(&action1);

    contextMenu.exec(mapToGlobal(pos));
}

void SoCTab::Save_Img()
{
    QPixmap p = m_chartSoC->grab();
    p.save("SoC.png", "PNG");
}

