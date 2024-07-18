#include "mainwindow.h"
#include "userinterface.h"
#include "configuredialog.h"
#include "asynchronousonebufferedai.h"

#include <QApplication>

int main(int argc, char *argv[])
{
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

