#include "mainwindow.h"
#include "userinterface.h"
#include "configuredialog.h"
#include "asynchronousonebufferedai.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
//    //更改编码
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
    QTextCodec::setCodecForTr(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));


    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    userinterface w;
//    w.show();
    ConfigureDialog dialog;
    int resultDialog = dialog.exec();
    if (resultDialog == QDialog::Rejected)
    {
        a.exit(0);
        return 0;
    }
    else if(resultDialog == QDialog::Accepted)
    {
//        w.SetConfigureParameter(dialog.GetConfigureParameter());
//        w.SetConfigureDialog(&dialog);
//        w.Initialize();
        w.show();
//        w.set
    }

    return a.exec();
}

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    AI_AsynchronousOneBufferedAi w;
//    ConfigureDialog dialog;
//    int resultDialog = dialog.exec();
//    if (resultDialog == QDialog::Rejected)
//    {
//        a.exit(0);
//        return 0;
//    }
//    else if (resultDialog == QDialog::Accepted)
//    {
//        w.SetConfigureParameter(dialog.GetConfigureParameter());
//        w.SetConfigureDialog(&dialog);
//        w.Initialize();
//        w.show();
//    }

//    return a.exec();
//}

