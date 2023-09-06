#include "soctab.h"

/// \brief SoCTab::SoCTab as class constructor to Tab graph
SoCTab::SoCTab(QWidget *parent): QWidget(parent)
{
    // LINE SERIES
    seriesSoC_r = new QLineSeries();
    seriesSoC_i = new QLineSeries();

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    axisX->setTitleText("t(s)");
    axisX->setRange(0, 0.5);

    axisY = new QValueAxis;
    axisY->setTitleText("Sinal level");
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickAnchor(0);
    axisY->setTickInterval(1);
    axisY->setTickCount(5);
    axisY->setRange(-5, 5);

    // Create chart view with the chart
    m_chart = new QChart();
    m_chart->setTitle("Sinal SoC");
    m_chart->legend()->setVisible(true);
    m_chart->addAxis(axisX, AlignBottom);
    m_chart->addAxis(axisY, AlignLeft);

    // Add Series
    m_chart->addSeries(seriesSoC_r);
    m_chart->addSeries(seriesSoC_i);

    // Chart View
    m_chartSoC = new QChartView(m_chart, this);
    m_chartSoC->setRenderHint(QPainter::Antialiasing);

    // Tab Layout
    m_ChartLayoutSoC = new QGridLayout();
    m_ChartLayoutSoC->addWidget(m_chartSoC);
    setLayout(m_ChartLayoutSoC);

    // ==========================================================================
    // LABELS
    seriesSoC_r->setName("Real");
    seriesSoC_i->setName("Imag");

    // LINE ADJUSTMENTS FOR SOC
    QPen penSoC_r = seriesSoC_r->pen();
    QPen penSoC_i = seriesSoC_i->pen();

    penSoC_r.setWidth(1);
    penSoC_r.setBrush(QBrush("red"));

    penSoC_i.setWidth(1);
    penSoC_i.setBrush(QBrush("blue"));

    seriesSoC_r->setPen(penSoC_r);
    seriesSoC_i->setPen(penSoC_i);

    // SET AXIS
    seriesSoC_r->attachAxis(axisX);
    seriesSoC_r->attachAxis(axisY);

    seriesSoC_i->attachAxis(axisX);
    seriesSoC_i->attachAxis(axisY);

    // ==========================================================================

    this->setContextMenuPolicy(CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(ShowContextMenu(QPoint)));

}

///
/// \brief SoCTab::Update_View UPDATE VIEW GRAPH
/// \param SoC_r SOC REAL COMPONENTE
/// \param SoC_i SPC IMAGINARY COMPONENT
/// \param sig STANDARD DEVIATION
/// \param max_t MAX TIME (NUMBER OF SAMPLES) * (SAMPLE_TIME)
///
void SoCTab::Update_View(QList<QPointF> *SoC_r, QList<QPointF> *SoC_i, double sig, double max_t)
{
    // RENDER CHART WITH VALUES SOC
    if(seriesSoC_r->count() != 0) seriesSoC_r->clear();
    if(seriesSoC_i->count() != 0) seriesSoC_i->clear();

    seriesSoC_r->replace(*SoC_r);
    seriesSoC_i->replace(*SoC_i);

    axisX->setRange(0.0, max_t);
    axisY->setRange(-4.0*sig, 4.0*(sig));
    axisY->setTickInterval(floor(1*sig));
}

///
/// \brief SoCTab::ShowContextMenu CONTEXT MENU FIGURE
///
void SoCTab::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Save Chart", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(Save_Img()));
    contextMenu.addAction(&action1);

    contextMenu.exec(mapToGlobal(pos));
}

///
/// \brief SoCTab::Save_Img SAVE IMAGE FUNCTION FOR CONTEXT MENU
///
void SoCTab::Save_Img()
{
    QPixmap p = m_chartSoC->grab();
    p.save("SoC.png", "PNG");
}

