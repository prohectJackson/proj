#include "mainwindow.h"
#include "ui_mainwindow.h"

//using namespace std;

//void* recvMsg(void *arg)
//{
//    int dataSocket = *(int *)arg;
//    char buf[1024];
//    for (;;){
//        int nread = read(dataSocket, buf, 1024);
//        if (nread == -1){
//            // error
//        }
//        buf[nread] = '\0';
//        printf("receiving message buf: %s\t nread: %d strlen(buf): %ld\n", buf,nread, strlen(buf));
//    }
//}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(dataSocket == -1){
        fprintf(stderr, "can't creat socket()\n");
        exit(1);
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("13.209.69.87");
    serverAddr.sin_port = htons(59818);

    int re;
    re = ::connect(dataSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
    if (re == -1){
        fprintf(stderr, "can't connect socket()\n");
        exit(2);
    }

//    pthread_t tid2;
//    pthread_create(&tid2, NULL, recvMsg, (void *)&dataSocket);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_personIn1_clicked()
{
    char buf[10] = "1personIn";
    write(dataSocket, buf, strlen(buf));

}

void MainWindow::on_personIn2_clicked()
{
    char buf[10] = "2personIn";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_personOut1_clicked()
{
    char buf[11] = "1personOut";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_pushButton_clicked()
{
    char buf[11] = "2personOut";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_personIn3_clicked()
{
    char buf[11] = "3personIn";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_personIn4_clicked()
{
    char buf[11] = "4personIn";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_personOut3_clicked()
{
    char buf[11] = "3personOut";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_personOut4_clicked()
{
    char buf[11] = "4personOut";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_turnOffRoom1_clicked()
{
    char buf[10] = "1turnOff";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_turn_clicked()
{
    char buf[10] = "2turnOff";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_turnOffRoom3_clicked()
{
    char buf[10] = "3turnOff";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_turnOffRoom4_clicked()
{
    char buf[10] = "4turnOff";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_CurtainRoom1_clicked()
{
    char buf[10] = "1ledOn";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_CurtainRoom2_clicked()
{
    char buf[10] = "2ledOn";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_curtainRoom3_clicked()
{
    char buf[10] = "3ledOn";
    write(dataSocket, buf, strlen(buf));
}

void MainWindow::on_curtainRoom4_clicked()
{
    char buf[10] = "4ledOn";
    write(dataSocket, buf, strlen(buf));
}
