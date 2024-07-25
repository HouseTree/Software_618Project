#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "excelread.h"
#include "qcustomplot.h"
#include "simplegraph.h"
#include "configuredialog.h"

#include <QMainWindow>
#include <QDebug>
#include <QTimer>

namespace Ui {
class userinterface;
}

class userinterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit userinterface(QWidget *parent = 0);
    ~userinterface();

    void drawgraph_test();

    void SetConfigureDialog(ConfigureDialog * dialog){configureDialog = dialog;}
    void SetConfigureParameter(ConfigureParameter value){configure = value;}
    void CheckError(ErrorCode errorCode);
    void ConfigureDevice();

    static void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void * userParam);
    void initTabs();
    void setText(int row, int colum, const QString &text, int font_size = 11, bool is_black = false);
    void init_LED_Vs();
    void Init_LED();

signals:
    void UpdateButton();

private slots:
    void slotTimeout_F_MM();

    void on_ButtonStartCollect_clicked();

    void on_ButtonConfigure_clicked();


    void on_actionManu_triggered();

private:
    Ui::userinterface *ui;
    SimpleGraph *graph;
    ConfigureDialog *configureDialog;
    ConfigureParameter configure;
    WaveformAiCtrl * waveformAiCtrl;
    double *scaledData;

//    QTimer *_timer;
    static const int sectionCount = 1;


};

#endif // USERINTERFACE_H
