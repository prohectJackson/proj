#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_personIn2_clicked();

    void on_personIn1_clicked();

    void on_personOut1_clicked();

    void on_pushButton_clicked();


    void on_personIn3_clicked();

    void on_personIn4_clicked();

    void on_personOut3_clicked();

    void on_personOut4_clicked();

    void on_turnOffRoom1_clicked();

    void on_turn_clicked();

    void on_turnOffRoom3_clicked();

    void on_turnOffRoom4_clicked();

    void on_CurtainRoom1_clicked();

    void on_CurtainRoom2_clicked();

    void on_curtainRoom3_clicked();

    void on_curtainRoom4_clicked();

private:
    Ui::MainWindow *ui;
    int dataSocket = socket(AF_INET, SOCK_STREAM, 0);
};
#endif // MAINWINDOW_H
