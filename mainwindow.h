#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vector3D.h"
#include "segment3D.h"
#include <QDebug.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushButtonCalcIntersect_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
