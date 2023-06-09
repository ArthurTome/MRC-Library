#include "psdtab.h"

PSDTab::PSDTab(QWidget *parent): QWidget(parent)
{
    // LINE SERIES
    seriesPSD = new QLineSeries();

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    axisX->setTitleText("w");
    axisX->setTickAnchor(0);
    axisX->setTickCount(5);

    axisY = new QValueAxis;
    axisY->setTitleText("Power");
    axisY->setRange(0, 210);

    // Create chart view with the chart
    m_chart = new QChart();
    m_chart->setTitle("PSD SoC");
    m_chart->legend()->setVisible(false);
    m_chart->addAxis(axisX, AlignBottom);
    m_chart->addAxis(axisY, AlignLeft);

    // Add Series
    m_chart->addSeries(seriesPSD);

    // Chart View
    m_chartPSD = new QChartView(m_chart, this);

    // Tab Layout
    m_ChartLayoutPSD = new QGridLayout();
    m_ChartLayoutPSD->addWidget(m_chartPSD);
    setLayout(m_ChartLayoutPSD);

    // ==========================================================================
    // LINE ADJUSTMENTS FOR SOC
    QPen penPSD = seriesPSD->pen();

    penPSD.setWidth(1);
    penPSD.setBrush(QBrush("blue"));

    seriesPSD->setPen(penPSD);

    // SET AXIS
    seriesPSD->attachAxis(axisX);
    seriesPSD->attachAxis(axisY);

    // ==============================================================

    this->setContextMenuPolicy(CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(ShowContextMenu(QPoint)));
}

void PSDTab::Update_View(QList<QPointF> *PSD, float freq)
{
    // RENDER CHART WITH VALUES SOC
    if(seriesPSD->count() != 0) seriesPSD->clear();

    seriesPSD->replace(*PSD);

    axisX->setRange(-floor(freq*1.2), floor(freq*1.2));

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
