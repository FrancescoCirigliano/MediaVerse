#include "View/MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    View::MainWindow* main_window = new View::MainWindow();

    main_window->setWindowIcon(QIcon(":/assets/icon/logo.png"));
    main_window->showMaximized();

    return a.exec();
}
