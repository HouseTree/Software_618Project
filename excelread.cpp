#include "excelread.h"

#include<QDebug>

ExcelRead::ExcelRead()
{
    excel = NULL;			//在构造函数中进行初始化操作
    workbooks = NULL;
    workbook = NULL;
    worksheets = NULL;
    worksheet = NULL;
    usedrange = NULL;
}

ExcelRead::~ExcelRead()
{

}

void ExcelRead::readExcelData()
{
    excel = new QAxObject("Excel.Application");									//创建Excel对象连接驱动
    excel->dynamicCall("SetVisible(bool)",true);								//ture的打开Excel表 false不打开Excel表
    excel->setProperty("DisplayAlerts",false);
    workbooks = excel->querySubObject("WorkBooks");
    QString fileName = QString("D:\\ProgramSpace\\Qt\\2024-07-10\\sears-s10095_20240710_1931_1.xls");
    workbook = workbooks->querySubObject("Open(const QString&)",fileName);		//打开指定Excel
    worksheets = workbook->querySubObject("WorkSheets");            			//获取表页对象
    worksheet = worksheets->querySubObject("Item(int)",2);          			//获取第1个sheet表
    usedrange =worksheet->querySubObject("Usedrange");							//获取权限
//    int iRow = usedrange->property("Row").toInt();             					//数据起始行数和列数(可以解决不规则Excel)
//    int iCol = usedrange->property("Column").toInt();
//    int intRow = usedrange->querySubObject("Rows")->property("Count").toInt();  //获取数据总行数
//    // 逐行读取主表
//    for (int i = iRow; i <= intRow; i++)
//    {
//        QString number = worksheet->querySubObject("Cells(int,int)",i,1)->dynamicCall(("Value2()")).value<QString>();
//        QString name = worksheet->querySubObject("Cells(int,int)",i,2)->dynamicCall(("Value2()")).value<QString>();
//        QString id = worksheet->querySubObject("Cells(int,int)",i,3)->dynamicCall(("Value2()")).value<QString>();
//        QString desc = worksheet->querySubObject("Cells(int,int)",i,4)->dynamicCall(("Value2()")).value<QString>();
//        qDebug() << number << name << id << desc;//打印验证数据
//    }
//    workbook->dynamicCall("Close()"); //关闭工作簿
//    excel->dynamicCall("Quit()"); //退出进程

//    delete excel;

}

