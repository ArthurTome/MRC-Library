#include "rxxtab.h"

RxxTab::RxxTab(QWidget *parent): QWidget(parent)
{
    // LINE SERIES
    seriesRxx = new QLineSeries();
    seriesCRxx = new QLineSeries();
    seriesIRxx = new QLineSeries();

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    axisX->setTitleText("tal(s)");

    axisY = new QValueAxis;
    axisY->setTitleText("Correlation");
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickAnchor(-0.5);
    axisY->setTickInterval(0.25);
    axisY->setRange(-0.67, 1);

    // Create chart view with the chart
    m_chart = new QChart();
    m_chart->setTitle("Sinal Correlations");
    m_chart->legend()->setVisible(true);
    m_chart->addAxis(axisX, AlignBottom);
    m_chart->addAxis(axisY, AlignLeft);

    // Add Series
    m_chart->addSeries(seriesRxx);
    m_chart->addSeries(seriesCRxx);
    m_chart->addSeries(seriesIRxx);

    // Chart View
    m_chartRxx = new QChartView(m_chart, this);
    m_chartRxx->setRenderHint(QPainter::Antialiasing);

    // Tab Layout
    m_ChartLayoutRXX = new QGridLayout();
    m_ChartLayoutRXX->addWidget(m_chartRxx);
    setLayout(m_ChartLayoutRXX);

    // ==========================================================================
    // LABELS
    seriesRxx->setName("AutoCorr");
    seriesCRxx->setName("CrossCorr");
    seriesIRxx->setName("JakesCorr");

    // LINE ADJUSTMENTS FOR RXX
    QPen penRxx = seriesRxx->pen();
    QPen penCRxx = seriesCRxx->pen();
    QPen penIRxx = seriesIRxx->pen();

    penRxx.setWidth(1);
    penRxx.setBrush(QBrush("red"));
    penCRxx.setWidth(1);
    penCRxx.setBrush(QBrush("blue"));
    penIRxx.setWidth(1);
    penIRxx.setBrush(QBrush("orange"));

    seriesRxx->setPen(penRxx);
    seriesCRxx->setPen(penCRxx);
    seriesIRxx->setPen(penIRxx);

    // SET AXIS
    seriesRxx->attachAxis(axisX);
    seriesRxx->attachAxis(axisY);

    seriesCRxx->attachAxis(axisX);
    seriesCRxx->attachAxis(axisY);

    seriesIRxx->attachAxis(axisX);
    seriesIRxx->attachAxis(axisY);

    // ==============================================================

    this->setContextMenuPolicy(CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(ShowContextMenu(QPoint)));

}
void RxxTab::Update_View(QList<QPointF> *Rxx, QList<QPointF> *CRxx, QList<QPointF> *NRxx, float max_t)
{
    // RENDER CHART WITH VALUES SOC
    if(seriesRxx->count() != 0) seriesRxx->clear();
    if(seriesCRxx->count() != 0) seriesCRxx->clear();
    if(seriesIRxx->count() != 0) seriesIRxx->clear();

    seriesRxx->replace(*Rxx);
    seriesCRxx->replace(*CRxx);
    seriesIRxx->replace(*NRxx);

    axisX->setRange(0, max_t);
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
