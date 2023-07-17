#include "psdtab.h"

/// \brief PSDTab::PSDTab as class constructor to Tab graph
PSDTab::PSDTab(QWidget *parent): QWidget(parent)
{
    // LINE SERIES
    seriesPSD = new QLineSeries();
    seriesiPSD = new QLineSeries();

    // RENDER LABEL AXIS
    axisX = new QValueAxis;
    axisX->setTitleText("w");
    axisX->setTickAnchor(0);
    axisX->setTickCount(5);

    axisY = new QValueAxis;
    axisY->setTitleText("Power");
    axisY->setRange(0, 250);

    // Create chart view with the chart
    m_chart = new QChart();
    m_chart->setTitle("PSD SoC");
    m_chart->legend()->setVisible(true);
    m_chart->addAxis(axisX, AlignBottom);
    m_chart->addAxis(axisY, AlignLeft);

    // Add Series
    m_chart->addSeries(seriesPSD);
    m_chart->addSeries(seriesiPSD);

    // Chart View
    m_chartPSD = new QChartView(m_chart, this);

    // Tab Layout
    m_ChartLayoutPSD = new QGridLayout();
    m_ChartLayoutPSD->addWidget(m_chartPSD);
    setLayout(m_ChartLayoutPSD);

    seriesPSD->setName("Model");
    seriesiPSD->setName("Ideal");

    // ==========================================================================
    // LINE ADJUSTMENTS FOR SOC
    QPen penPSD = seriesPSD->pen();
    QPen peniPSD = seriesPSD->pen();

    penPSD.setWidth(1);
    penPSD.setBrush(QBrush("blue"));

    peniPSD.setWidth(1);
    peniPSD.setBrush(QBrush("red"));

    seriesPSD->setPen(penPSD);
    seriesiPSD->setPen(peniPSD);

    // SET AXIS
    seriesPSD->attachAxis(axisX);
    seriesPSD->attachAxis(axisY);

    seriesiPSD->attachAxis(axisX);
    seriesiPSD->attachAxis(axisY);

    // ==========================================================================
    this->setContextMenuPolicy(CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(ShowContextMenu(QPoint)));
}

///
/// \brief PSDTab::Update_View UPDATE VIEW GRAPH
/// \param PSD power spectral density to numeric generation
/// \param iPSD power spectral density to ideal generation
/// \param freq maximum frequency of generation SoC
///
void PSDTab::Update_View(QList<QPointF> *PSD, QList<QPointF> *iPSD, double freq)
{
    // RENDER CHART WITH VALUES SOC
    if(seriesPSD->count() != 0) seriesPSD->clear();
    if(seriesiPSD->count() != 0) seriesiPSD->clear();

    seriesPSD->replace(*PSD);
    seriesiPSD->replace(*iPSD);

    axisX->setRange(-floor(freq*1.2), floor(freq*1.2));
}

///
/// \brief PSDTab::ShowContextMenu CONTEXT MENU FIGURE
///
void PSDTab::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Save Chart", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(Save_Img()));
    contextMenu.addAction(&action1);

    contextMenu.exec(mapToGlobal(pos));
}

///
/// \brief PSDTab::Save_Img SAVE IMAGE FUNCTION FOR CONTEXT MENU
///
void PSDTab::Save_Img()
{
    QPixmap p = m_chartPSD->grab();
    p.save("PSD.png", "PNG");
}
