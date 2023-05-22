#include "rxxtab.h"

RxxTab::RxxTab(QWidget *parent): QWidget(parent)
{
    m_chart = new QChart();
    m_chartRxx = new QChartView(m_chart, this);

    this->setContextMenuPolicy(CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));

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

    m_chart->addAxis(axisX, AlignBottom);
    m_chart->addAxis(axisY, AlignLeft);

}

void RxxTab::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Save Chart", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(Save_Img()));
    contextMenu.addAction(&action1);

    contextMenu.exec(mapToGlobal(pos));
}

void RxxTab::Save_Img()
{
    QPixmap p = m_chartRxx->grab();
    p.save("Rxx.png", "PNG");
}
