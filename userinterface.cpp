#include "userinterface.h"
#include "ui_userinterface.h"

#include "C:\Advantech\DAQNavi\Inc\bdaqctrl.h"

#include<QTimer>
#include<QThread>
#include <QMessageBox>


using namespace Automation::BDaq;

#define deviceDescription L"PCI-1711,BID#0"

userinterface::userinterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userinterface)
{
    ui->setupUi(this);

//    while(1)
//    {

//        slotTimeout_F_MM();
//    }
    QTimer *_timer = new QTimer(this);
//    _timer->setInterval(1000);//间隔1000ms
    connect(_timer, SIGNAL(timeout()), this, SLOT(slotTimeout_F_MM()));//连接到时要处理的函数
    _timer->start(500);//间隔1000ms



//    QThread t;
//    QTimer *_timer = new QTimer(this);
//    Worker worker;
////    _timer->setInterval(1000);//间隔1000ms
//    connect(_timer, SIGNAL(timeout()), &worker, SLOT(slotTimeout_F_MM(ui)));//连接到时要处理的函数
//    _timer->start(500);//间隔1000ms
//    this->moveToThread(&t);
//    t.start();

//    QTimer *_timer = new QTimer(this);
//    _timer->setInterval(1000);//间隔1000ms
//    connect(_timer, SIGNAL(timeout()), this, SLOT(slotTimeout_F_MM()));//连接到时要处理的函数
//    _timer->start(1000);//间隔1000ms
//    _timer->stop();


//    drawgraph_test();

//    scaledData = NULL;
//    waveformAiCtrl = WaveformAiCtrl::Create();
//    waveformAiCtrl->addStoppedHandler(OnStoppedEvent, this);


    //connect the signal 'UpdateButton' the the slot 'ButtonEnable'.
//    connect(this, SIGNAL(UpdateButton()), this, SLOT(ButtonEnable()));





}

userinterface::~userinterface()
{
//    _timer->stop();
    delete ui;
}

void userinterface::drawgraph_test()
{
    ExcelRead *read = new ExcelRead();
    read->readExcelData();
    int iRow = read->usedrange->property("Row").toInt();             					//数据起始行数和列数(可以解决不规则Excel)
    int iCol = read->usedrange->property("Column").toInt();
    int intRow = read->usedrange->querySubObject("Rows")->property("Count").toInt();  //获取数据总行数
    // 图表背景颜色
    ui->customPlot_figure->setBackground(Qt::white);
    //设置属性可缩放，移动
    ui->customPlot_figure->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    QCPCurve *curGraph1 = new QCPCurve(ui->customPlot_figure->xAxis, ui->customPlot_figure->yAxis);
//    QCPCurve * curGraph1 = ui->customPlot_figure->addGraph();
    curGraph1->setPen(QPen(Qt::blue));
//    curGraph1->setLineStyle(QCPGraph::lsNone);
//    curGraph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    curGraph1->setName("Fermat's Spiral1");
    curGraph1->setLineStyle(QCPCurve::lsLine);

    QCPCurve *curGraph2 = new QCPCurve(ui->customPlot_figure->xAxis, ui->customPlot_figure->yAxis);
//    QCPCurve * curGraph1 = ui->customPlot_figure->addGraph();
    curGraph2->setPen(QPen(Qt::red));
//    curGraph1->setLineStyle(QCPGraph::lsNone);
//    curGraph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    curGraph2->setName("Fermat's Spiral2");

    QCPCurve *curGraph3 = new QCPCurve(ui->customPlot_figure->xAxis, ui->customPlot_figure->yAxis);
//    QCPCurve * curGraph1 = ui->customPlot_figure->addGraph();
    curGraph3->setPen(QPen(Qt::green));
//    curGraph1->setLineStyle(QCPGraph::lsNone);
//    curGraph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    curGraph3->setName("Fermat's Spiral3");

    ui->customPlot_figure->xAxis->setRange(-15,15);
//    ui->cusplot_3->xAxis->setNumberFormat("f");
//    ui->cusplot_3->rescaleAxes();
    ui->customPlot_figure->yAxis->setRange(-800, 1400);
//    qDebug() << key;

   // 逐行读取主表
    for (int i = 2; i <= intRow; i++)
    {

        double F1 = read->worksheet->querySubObject("Cells(int,int)",i,1)->dynamicCall(("Value2()")).value<double>();
        double D1 = read->worksheet->querySubObject("Cells(int,int)",i,2)->dynamicCall(("Value2()")).value<double>();
        double F2 = read->worksheet->querySubObject("Cells(int,int)",i,3)->dynamicCall(("Value2()")).value<double>();
        double D2 = read->worksheet->querySubObject("Cells(int,int)",i,4)->dynamicCall(("Value2()")).value<double>();
        double F3 = read->worksheet->querySubObject("Cells(int,int)",i,5)->dynamicCall(("Value2()")).value<double>();
        double D3 = read->worksheet->querySubObject("Cells(int,int)",i,6)->dynamicCall(("Value2()")).value<double>();

        curGraph1->addData(D1, F1);
        curGraph2->addData(D2, F2);
        curGraph3->addData(D3, F3);
    }
    read->workbook->dynamicCall("Close()"); //关闭工作簿
    read->excel->dynamicCall("Quit()"); //退出进程

    delete read->excel;
}

void userinterface::CheckError(ErrorCode errorCode)
{
    if (BioFailed(errorCode))
    {
        QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
            QString::number(errorCode, 16).right(8).toUpper();
        QMessageBox::information(this, "Warning Information", message);
    }
}

void userinterface::ConfigureDevice()
{
    ErrorCode errorCode = Success;
    if (scaledData != NULL)
    {
        delete []scaledData;
        scaledData = NULL;
    }
    int32 rawDataBufferLength = configure.channelCount * configure.sectionLength;
    scaledData = new double[rawDataBufferLength];
    if (scaledData == NULL)
    {
        QMessageBox::information(this, tr("Warning Information"),
            tr("Sorry! Error in allocating memory...."));
        return;
    }

    // Select a device with AccessWrite/AccessWriteWithReset mode with device number
    // or device description.
    QString deviceDesc = configure.deviceName;
    const wchar_t * description = reinterpret_cast<const wchar_t *>(deviceDesc.utf16());
    DeviceInformation selected(description);
    errorCode = waveformAiCtrl->setSelectedDevice(selected);
     CheckError(errorCode);
     errorCode = waveformAiCtrl->LoadProfile(configure.profilePath);
     CheckError(errorCode);

    //Set the streaming mode.
   errorCode = waveformAiCtrl->getConversion()->setChannelCount(configure.channelCount);
   CheckError(errorCode);
   errorCode = waveformAiCtrl->getConversion()->setChannelStart(configure.channelStart);
   CheckError(errorCode);
   errorCode = waveformAiCtrl->getConversion()->setClockRate(configure.clockRatePerChan);
   CheckError(errorCode);
   errorCode = waveformAiCtrl->getRecord()->setSectionLength(configure.sectionLength);
   CheckError(errorCode);
   errorCode = waveformAiCtrl->getRecord()->setSectionCount(sectionCount);//The nonzero value means "One Buffered" mode.
   CheckError(errorCode);
   for (int i = 0; i < waveformAiCtrl->getChannels()->getCount(); i++)
   {
      errorCode = waveformAiCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
      CheckError(errorCode);
   }

   errorCode = waveformAiCtrl->Prepare();
   CheckError(errorCode);
}

void userinterface::OnStoppedEvent(void *sender, BfdAiEventArgs *args, void *userParam)
{
    userinterface * uParam = (userinterface *)userParam;
     ((WaveformAiCtrl*)sender)->GetData(args->Count, uParam->scaledData, 0, NULL, NULL, NULL, NULL);
    for(int i=0; i<args->Count; i++)
    {
        qDebug() <<"Count:"<< args->Count << "scaledData" << uParam->scaledData[i];
    }
//     uParam->graph->Chart(uParam->scaledData, uParam->configure.channelCount,
//       args->Count / uParam->configure.channelCount, 1.0 / uParam->configure.clockRatePerChan);

     //Emit the signal 'uptateButton' to enable the main frame's button.
     emit uParam->UpdateButton();
}

//void userinterface::OnStoppedEvent(void *sender, BfdAiEventArgs *args, void *userParam)
//{
//    userinterface * uParam = (userinterface *)userParam;
//     ((WaveformAiCtrl*)sender)->GetData(args->Count, uParam->scaledData, 0, NULL, NULL, NULL, NULL);

//    for(int i=0; i<2; i++)
//    {
//        qDebug() << scaledData[i];
//    }
////    uParam->graph->Chart(uParam->scaledData, uParam->configure.channelCount,
////       args->Count / uParam->configure.channelCount, 1.0 / uParam->configure.clockRatePerChan);

//     //Emit the signal 'uptateButton' to enable the main frame's button.
//     emit uParam->UpdateButton();
//}
void userinterface::slotTimeout_F_MM()
{
    int32 const chStart = 0;
    int32 const chCount = 2;
    double values[chCount] = {0};

    ErrorCode ret = Success;
    // if(!is_init)
    // {
    //     instantaictrl = InstantAiCtrl::Create();
    //     DeviceInformation devInfo(L"DemoDevice,BID#0");
    //     ret = instantaictrl->setSelectedDevice(devInfo);
    //     is_init = true;
    // }

    InstantAiCtrl *instantaictrl = InstantAiCtrl::Create();
    DeviceInformation devInfo(deviceDescription);
    ret = instantaictrl->setSelectedDevice(devInfo);

    // ret = instantaictrl->Read(ch, dataRaw);
    // ui->lcdNumber->display(dataRaw);
    // QString ab = QString::number(dataRaw);
    // ui->textEdit_2->append(ab);

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
     /* 获取当前板卡的所有采集通道。 */
     Array<AiChannel>* channels = instantaictrl->getChannels();
     /* 设置采集通道的连接类型。*/
     channels->getItem(0).setSignalType(SingleEnded);
     channels->getItem(1).setSignalType(SingleEnded);
     /* 设置采集通道的读值范围。*/
     channels->getItem(0).setValueRange(V_Neg10To10);
     channels->getItem(1).setValueRange(V_Neg10To10);

//     channels->getItem(2).
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    ret = instantaictrl->Read(chStart, chCount, values);
    ui->lcdNumber_Force->display(values[0]);
    ui->lcdNumber_Displacement->display(values[1]);
//    ui->textBrowser->append("Start===========");
//    for(int i=0; i<chCount; i++)
//    {
//        QString ab = QString::number(values[i]);
//        ui->textBrowser->append(QString::number(i) + ":    " + ab);
//    }
//    ui->textBrowser->append("Stop===========");

    instantaictrl->Dispose();
}

void userinterface::on_ButtonStartCollect_clicked()
{
//    DeviceInformation devInfo(deviceDescription);
//    waveformAiCtrl->setSelectedDevice(devInfo);
//    ErrorCode errorCode = waveformAiCtrl->Start();
//    CheckError(errorCode);
    // Step 1: create a 'WaveformAiCtrl' object
    WaveformAiCtrl *ctrl = WaveformAiCtrl::Create();
    ErrorCode ret;
    const wchar_t filename[] = L"D:\\ProgramSpace\\Qt\\Software\\Profiles\\test.xml";
    ret = ctrl->LoadProfile(filename);
 //   ErrorCode ret = Success;
    // Step 4: set waveform AI parameters if needed
    int chStart = 0;
    int chCount = 2;
    int sectionLength = 512;
    int sectionCount = 1;
    double clkRate = 1000.0;
//    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//     /* 获取当前板卡的所有采集通道。 */
//     Array<AiChannel>* channels = ctrl->getChannels();
//     /* 设置采集通道的连接类型。*/
//     channels->getItem(0).setSignalType(SingleEnded);
//     /* 设置采集通道的读值范围。*/
//     channels->getItem(0).setValueRange(V_Neg10To10);
//     /* 设置采集通道的连接类型。*/
//     channels->getItem(1).setSignalType(SingleEnded);
//     /* 设置采集通道的读值范围。*/
//     channels->getItem(1).setValueRange(V_Neg10To10);
//    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    do{
       // Step 2: select the device with 'ModeWrite' mode
//       int deviceNumber = 0;
       DeviceInformation devInfo(deviceDescription);
       ret = ctrl->setSelectedDevice(devInfo);
       if (ret != Success) {
          printf("open device failed. error code = %x\n", ret);
          break;
       }
       // Step 3: *** configure the channels if needed ***
       //Array *channels = ctrl->getChannels();
       //for (int i = 0; i < channels->getCount(); ++i) {
       //   channels->getItem(i).setValueRange(V_0To5);
       //}

       ctrl->getConversion()->setChannelStart(chStart);
       ctrl->getConversion()->setChannelCount(chCount);
       ctrl->getConversion()->setClockRate(clkRate);
       ctrl->getRecord()->setSectionLength(sectionLength);
       ctrl->getRecord()->setSectionCount(sectionCount);
    } while(false);

    // Step 5: start data acquisition
    ctrl->Prepare();
    ctrl->Start();

    // get the AI data and process it.
    int dataCount = sectionLength * chCount * sectionCount;
    double dataBuffer[dataCount];
    ctrl->GetData(dataCount, dataBuffer, -1);//The timeout value is -1, meaning infinite waiting.


    ui->customPlot_figure->xAxis->setRange(-10,10);
//    ui->cusplot_3->xAxis->setNumberFormat("f");
//    ui->cusplot_3->rescaleAxes();
    ui->customPlot_figure->yAxis->setRange(-800, 1400);
    // 图表背景颜色
    ui->customPlot_figure->setBackground(Qt::white);
    //设置属性可缩放，移动
    ui->customPlot_figure->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    QCPCurve *curGraph1 = new QCPCurve(ui->customPlot_figure->xAxis, ui->customPlot_figure->yAxis);
//    QCPCurve * curGraph1 = ui->customPlot_figure->addGraph();
    curGraph1->setPen(QPen(Qt::blue));
//    curGraph1->setLineStyle(QCPGraph::lsNone);
//    curGraph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    curGraph1->setName("Fermat's Spiral1");
    curGraph1->setLineStyle(QCPCurve::lsLine);


    for(int i=0; i<sectionLength; i++)
    {
        qDebug() <<"i:"<< i << "scaledData" << dataBuffer[i];
        // 力值F 5000N : 10V , 1V = 500N ；位移D 10mm : 10V , 1V = 1mm
        curGraph1->addData(dataBuffer[i+sectionLength],dataBuffer[i]*500);
    }


    // Step 6: close device, release any allocated resource before quit.
    ctrl->Cleanup();

    // Step 7: destroy the object
    ctrl->Dispose();
}

void userinterface::on_ButtonConfigure_clicked()
{
    configureDialog->RefreshConfigureParameter();
    int resultDialog = configureDialog->exec();
    if (resultDialog == QDialog::Accepted)
    {
        configure = configureDialog->GetConfigureParameter();
        ConfigureDevice();
    }
}

