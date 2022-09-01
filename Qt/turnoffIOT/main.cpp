#include "mainwindow.h"
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>

#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    MainWindow win;

    win.show();
    return app.exec();

}

