#include "psdtab.h"

PSDTab::PSDTab(QWidget *parent): QWidget(parent)
{
    // Create chart view with the chart
    m_chart = new QChart();
    m_chartPSD = new QChartView(m_chart, this);

    this->setContextMenuPolicy(CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));

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

    m_chart->addAxis(axisX, AlignBottom);
    m_chart->addAxis(axisY, AlignLeft);
    m_chart->legend()->setVisible(false);
    m_chart->setTitle("PSD SoC");

}

void PSDTab::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Save Chart", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(Save_Img()));
    contextMenu.addAction(&action1);

    contextMenu.exec(mapToGlobal(pos));
}

void PSDTab::Save_Img()
{
    QPixmap p = m_chartPSD->grab();
    p.save("PSD.png", "PNG");
}
