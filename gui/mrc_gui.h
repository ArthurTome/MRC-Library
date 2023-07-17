#ifndef MRC_GUI_H
#define MRC_GUI_H

#include "soctab.h"
#include "rxxtab.h"
#include "psdtab.h"

#include <complex>

#include <QtWidgets>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>

using namespace Qt;
using namespace std;

/// @brief Class for creating the program interface, inputting, and updating chart information.
class mrc_gui : public QWidget
{
    Q_OBJECT
public:
    explicit mrc_gui(QWidget *parent = 0);
    ~mrc_gui();

    void FFT_shift(complex<double>* A, unsigned long size);

public Q_SLOTS:
    void RefreshValues();

private:
    QTabWidget *tabWidget;

    // Tab
    SoCTab* A;
    RxxTab* B;
    PSDTab* C;

    // Vectors
    complex<double> *soc;
    complex<double> *rxx;
    complex<double> *rxx_t;
    complex<double> *irxx;
    complex<double> *crxx;
    complex<double> *fft;
    complex<double> *ifft;

    QGridLayout *m_mainLayout;
    QFormLayout *m_formLayout;

    QSpinBox *m_N;
    QSpinBox *m_Samples;
    QDoubleSpinBox *m_ts;
    QDoubleSpinBox *m_freq;
    QDoubleSpinBox *m_sig;
    QDoubleSpinBox *m_rep;
    QLineEdit *m_mean_real;
    QLineEdit *m_mean_imag;
    QLineEdit *m_execT;

    QRadioButton *radio1;
    QRadioButton *radio2;

    QLabel *label_N;
    QLabel *label_Samples;
    QLabel *label_TimeStamp;
    QLabel *label_Freq;
    QLabel *label_Variance;
    QLabel *label_Real;
    QLabel *label_Imag;
    QLabel *label_Rep;
    QLabel *label_ExecT;

};

#endif // MRC_GUI_H
