#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Vector3D.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect signals
    // QObject::connect(ui->pushButtonCalcIntersect, &QAbstractButton::clicked, MainWindow::on_pushButtonCalcIntersect_clicked());
}

void MainWindow::on_pushButtonCalcIntersect_clicked()
{
    qInfo() << "Calculate intersection started.";
    Vector3D A(ui->LineEditAx->text().toDouble(), ui->LineEditAy->text().toDouble(), ui->LineEditAz->text().toDouble(), "A");
    Vector3D B(ui->LineEditBx->text().toDouble(), ui->LineEditBy->text().toDouble(), ui->LineEditBz->text().toDouble(), "B");
    Vector3D C(ui->LineEditCx->text().toDouble(), ui->LineEditCy->text().toDouble(), ui->LineEditCz->text().toDouble(), "C");
    Vector3D D(ui->LineEditDx->text().toDouble(), ui->LineEditDy->text().toDouble(), ui->LineEditDz->text().toDouble(), "D");
    qDebug() << "Points to calculate intersection:";
    qDebug() << A.get_string_to_show();
    qDebug() << B.get_string_to_show();
    qDebug() << C.get_string_to_show();
    qDebug() << D.get_string_to_show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
