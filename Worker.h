#ifndef WORKER_H
#define WORKER_H
//#include "C:\Advantech\DAQNavi\Inc\bdaqctrl.h"
//#include "ui_userinterface.h"

//using namespace Automation::BDaq;

//#define deviceDescription L"PCI-1711,BID#0"

//class Worker : public QObject
//{
//    Q_OBJECT
//private slots:
////    void slotTimeout_F_MM(Ui::userinterface *ui)
////    {
////        int32 const chStart = 0;
////        int32 const chCount = 2;
////        double values[chCount] = {0};

////        ErrorCode ret = Success;
////        // if(!is_init)
////        // {
////        //     instantaictrl = InstantAiCtrl::Create();
////        //     DeviceInformation devInfo(L"DemoDevice,BID#0");
////        //     ret = instantaictrl->setSelectedDevice(devInfo);
////        //     is_init = true;
////        // }

////        InstantAiCtrl *instantaictrl = InstantAiCtrl::Create();
////        DeviceInformation devInfo(deviceDescription);
////        ret = instantaictrl->setSelectedDevice(devInfo);

////        // ret = instantaictrl->Read(ch, dataRaw);
////        // ui->lcdNumber->display(dataRaw);
////        // QString ab = QString::number(dataRaw);
////        // ui->textEdit_2->append(ab);

////        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
////         /* 获取当前板卡的所有采集通道。 */
////         Array<AiChannel>* channels = instantaictrl->getChannels();
////         /* 设置采集通道的连接类型。*/
////         channels->getItem(0).setSignalType(SingleEnded);
////         channels->getItem(1).setSignalType(SingleEnded);
////         /* 设置采集通道的读值范围。*/
////         channels->getItem(0).setValueRange(V_Neg10To10);
////         channels->getItem(1).setValueRange(V_Neg10To10);

////    //     channels->getItem(2).
////        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

////        ret = instantaictrl->Read(chStart, chCount, values);
////        ui->lcdNumber_Force->display(values[0]);
////        ui->lcdNumber_Displacement->display(values[1]);
////    //    ui->textBrowser->append("Start===========");
////    //    for(int i=0; i<chCount; i++)
////    //    {
////    //        QString ab = QString::number(values[i]);
////    //        ui->textBrowser->append(QString::number(i) + ":    " + ab);
////    //    }
////    //    ui->textBrowser->append("Stop===========");

////        instantaictrl->Dispose();
////    }
//};
#endif // WORKER_H
