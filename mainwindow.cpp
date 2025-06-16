#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    ui->textBrowser->append("=== NEW CALCULATIONS STARTED ===");
    Vector3D A(ui->LineEditAx->text().toDouble(), ui->LineEditAy->text().toDouble(), ui->LineEditAz->text().toDouble(), "A");
    Vector3D B(ui->LineEditBx->text().toDouble(), ui->LineEditBy->text().toDouble(), ui->LineEditBz->text().toDouble(), "B");
    Vector3D C(ui->LineEditCx->text().toDouble(), ui->LineEditCy->text().toDouble(), ui->LineEditCz->text().toDouble(), "C");
    Vector3D D(ui->LineEditDx->text().toDouble(), ui->LineEditDy->text().toDouble(), ui->LineEditDz->text().toDouble(), "D");
    // ui->textBrowser->append(QString::fromStdString(A.get_string_to_show()));
    // ui->textBrowser->append(QString::fromStdString(B.get_string_to_show()));
    // ui->textBrowser->append(QString::fromStdString(C.get_string_to_show()));
    // ui->textBrowser->append(QString::fromStdString(D.get_string_to_show()));
    qDebug() << "Points to calculate intersection:";
    qDebug() << QString::fromStdString(A.get_string_to_show());
    qDebug() << QString::fromStdString(B.get_string_to_show());
    qDebug() << QString::fromStdString(C.get_string_to_show());
    qDebug() << QString::fromStdString(D.get_string_to_show());
    Segment3D AB(A, B, "AB");
    Segment3D CD(C, D, "CD");
    qInfo() << "Segments to calculate intersection:";
    qInfo() << QString::fromStdString(AB.get_string_to_show());
    qInfo() << QString::fromStdString(CD.get_string_to_show());
    ui->textBrowser->append("Segments to calculate intersection:");
    ui->textBrowser->append(QString::fromStdString(AB.get_string_to_show()));
    ui->textBrowser->append(QString::fromStdString(CD.get_string_to_show()));

    if (AB.is_exists_equal_surface_to(CD))
    {
        qInfo() << "General surface exists.";
        if (AB.is_collinear_to_segment(CD))
        {
            qInfo() << "Segments are collinear - intersection point does not exist.";
            ui->textBrowser->append("Segments are collinear - intersection point does not exist.");
        }
        else
        {
            qDebug() << "Calculate coefficients for vectors...";
            double u = Segment3D::calc_u_to_segments(AB, CD);
            qDebug() << "Calculated u:" << u;
            double v = Segment3D::calc_v_to_segments(AB, CD);
            qDebug() << "Calculated v:" << v;
            if ((0 <= u && u <= 1) && (0 <= v && v <= 1))
            {
                qDebug() << "Coefficients u and v are correct (both belong to the segment [0, 1]).";
                Vector3D intersection_point = Segment3D::calc_intersection_point_by_uv_and_seg(u, v, AB); // здесь нужно использовать именно AB, для CD другие коэффициенты
                qInfo() << "Calculated intersection point:" << QString::fromStdString(intersection_point.get_string_to_show());
                ui->textBrowser->append("Calculated intersection point: " + QString::fromStdString(intersection_point.get_string_to_show()));
            }
            else
            {
                qInfo() << "The intersection point is outside the specified segments.";
                ui->textBrowser->append("The intersection point is outside the specified segments.");
            }
        }
    }
    else {
        qInfo() << "General surface does not exists - the specified segments are crossing.";
        ui->textBrowser->append("General surface does not exists - the specified segments are crossing.");
    }
    ui->textBrowser->append("");
}

MainWindow::~MainWindow()
{
    delete ui;
}
