#include "rxxtab.h"

/// \brief RxxTab::RxxTab as class constructor to Tab graph
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
    seriesIRxx->setName("ModelCorr");

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

    // ==========================================================================
    this->setContextMenuPolicy(CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(ShowContextMenu(QPoint)));
}

///
/// \brief RxxTab::Update_View UPDATE VIEW GRAPH
/// \param Rxx Ideal Correlation
/// \param CRxx Cross Correlation
/// \param NRxx Numeric Correlation
/// \param T MAX TIME (NUMBER OF SAMPLES) * (SAMPLE_TIME)
/// \param tmax maximum coehrence time
void RxxTab::Update_View(QList<QPointF> *Rxx, QList<QPointF> *CRxx, QList<QPointF> *NRxx, double T, double tmax)
{
    // RENDER CHART WITH VALUES SOC
    if(seriesRxx->count() != 0) seriesRxx->clear();
    if(seriesCRxx->count() != 0) seriesCRxx->clear();
    if(seriesIRxx->count() != 0) seriesIRxx->clear();

    seriesRxx->replace(*Rxx);
    seriesCRxx->replace(*CRxx);
    seriesIRxx->replace(*NRxx);

    axisX->setRange(0, T);
    this->tmax = tmax;
}

///
/// \brief SoCTab::ShowContextMenu CONTEXT MENU FIGURE
///
void RxxTab::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Save Chart", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(Save_Img()));

    QAction action2("Zoom in Tal", this);
    connect(&action2, SIGNAL(triggered()), this, SLOT(Zoom_Tal()));

    contextMenu.addAction(&action1);
    contextMenu.addAction(&action2);
    contextMenu.exec(mapToGlobal(pos));
}

///
/// \brief RxxTab::Save_Img Save image chart in png
///
void RxxTab::Save_Img()
{
    QPixmap p = m_chartRxx->grab();
    p.save("Rxx.png", "PNG");
}

///
/// \brief RxxTab::Zoom in coerence time
///
void RxxTab::Zoom_Tal()
{
    axisX->setRange(0, tmax);
}
