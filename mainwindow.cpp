#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (true) // TODO разобраться, как добавить в файл .ui
    {
        QRegExp RegExp("^[\\+|\\-]?\\d*([\\.|,]?\\d*)$"); // регулярное выражение, принимающее только числа с плавающей точкой
        QValidator *Validator = new QRegExpValidator(RegExp, this);
        ui->LineEditAx->setValidator(Validator);    ui->LineEditAy->setValidator(Validator);    ui->LineEditAz->setValidator(Validator);
        ui->LineEditBx->setValidator(Validator);    ui->LineEditBy->setValidator(Validator);    ui->LineEditBz->setValidator(Validator);
        ui->LineEditCx->setValidator(Validator);    ui->LineEditCy->setValidator(Validator);    ui->LineEditCz->setValidator(Validator);
        ui->LineEditDx->setValidator(Validator);    ui->LineEditDy->setValidator(Validator);    ui->LineEditDz->setValidator(Validator);
    }

// Здесь описаны тестовые сегменты для быстрой отладки. Отключаются в релиз версии
#ifdef QT_DEBUG
    {
        Vector3D A(1, 1, 0, "DebugA");    Vector3D B(-1, 0, 0, "DebugB");
        Vector3D C(0, 2, 0, "DebugC");    Vector3D D(0, -2, 0, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0, 0.5, 0)");
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 1, 1, "DebugA");    Vector3D B(0, 3, 1, "DebugB");
        Vector3D C(0, 2, -2, "DebugC");    Vector3D D(0, 2, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0, 2, 1)");
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 0, 1, "DebugA");    Vector3D B(0, 0, -1, "DebugB");
        Vector3D C(1, 0, -2, "DebugC");    Vector3D D(0, 0, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = x");
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 0, 1, "DebugA");    Vector3D B(0, 0, -1, "DebugB");
        Vector3D C(1, 0, -2, "DebugC");    Vector3D D(1, 0, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = x");
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 0, 1, "DebugA");    Vector3D B(0, 0, -1, "DebugB");
        Vector3D C(0, 0, 1, "DebugC");    Vector3D D(1, 0, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0, 0, 1)");
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 0, 1, "DebugA");    Vector3D B(0, 0, -1, "DebugB");
        Vector3D C(0, 0, 1, "DebugC");    Vector3D D(1, 1, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0, 0, 1)");
        calc_ans(A, B, C, D);
    }
    {   // \note Скорее всего указанные точки недостаточно точные
        Vector3D A(1, 1, 3.5, "DebugA");    Vector3D B(0.5, 0.3, -1, "DebugB");
        Vector3D C(-1.2, -2, 1, "DebugC");    Vector3D D(1.86, 2.16, 1.99, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0.79, 0.71, 1.65)");
        calc_ans(A, B, C, D);
    }
    {   // \note Скорее всего указанные точки недостаточно точные
        Vector3D A(1, 1, 3.5, "DebugA");    Vector3D B(0.5, 0.3, -1, "DebugB");
        Vector3D C(-1.2, -2, 1, "DebugC");    Vector3D D(0.79, 0.71, 1.65, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0.79, 0.71, 1.65)");
        calc_ans(A, B, C, D);
    }
    {   // \note "Нулевой" сегмент, принадлежащий второму сегменту
        Vector3D A(-1, -1, -1, "DebugA");    Vector3D B(-1, -1, -1, "DebugB");
        Vector3D C(-1.2, -1.2, -1.2, "DebugC");    Vector3D D(1.2, 1.2, 1.2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0, 0, 0)");
        calc_ans(A, B, C, D);
    }
    {   // \note "Нулевой" сегмент, принадлежащий второму сегменту
        Vector3D A(-1.2, -1.2, -1.2, "DebugA");    Vector3D B(1.2, 1.2, 1.2, "DebugB");
        Vector3D C(1, 1, 1, "DebugC");    Vector3D D(1, 1, 1, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0, 0, 0)");
        calc_ans(A, B, C, D);
    }
#endif
}

void MainWindow::on_pushButtonCalcIntersect_clicked()
{
    Vector3D A(ui->LineEditAx->text().toDouble(), ui->LineEditAy->text().toDouble(), ui->LineEditAz->text().toDouble(), "A");
    Vector3D B(ui->LineEditBx->text().toDouble(), ui->LineEditBy->text().toDouble(), ui->LineEditBz->text().toDouble(), "B");
    Vector3D C(ui->LineEditCx->text().toDouble(), ui->LineEditCy->text().toDouble(), ui->LineEditCz->text().toDouble(), "C");
    Vector3D D(ui->LineEditDx->text().toDouble(), ui->LineEditDy->text().toDouble(), ui->LineEditDz->text().toDouble(), "D");
    calc_ans(A, B, C, D);
}

void MainWindow::calc_ans(Vector3D A, Vector3D B, Vector3D C, Vector3D D)
{
    qInfo() << "\nCalculate intersection started.";
    ui->textBrowser->append("=== NEW CALCULATIONS STARTED ===");
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
        Segment3D::Collinear collinear = AB.is_collinear_to_segment(CD);
        if (collinear.m_is_collinear)
        {
            // Проверка, нет ли
            if (AB.norm() < Vector3D::eps)
            {
                qDebug() << "Segment AB have zero length.";
                ui->textBrowser->append("Segment AB have zero length.");
                if (CD.is_consist_point(AB.getStart()))
                {
                    qInfo() << "Point A is belongs to the segment CD and it is a intersection point.";
                    ui->textBrowser->append("Point A is belongs to the segment CD and it is a intersection point.");
                }
            }
            else if (CD.norm() < Vector3D::eps)
            {
                qDebug() << "Segment CD have zero length.";
                ui->textBrowser->append("Segment CD have zero length.");
                if (AB.is_consist_point(CD.getStart()))
                {
                    qInfo() << "Point C is belongs to the segment AB and it is a intersection point.";
                    ui->textBrowser->append("Point C is belongs to the segment AB and it is a intersection point.");
                }
            }
            else
            {
                qInfo() << "Segments are collinear and intersection point does not exist.";
                ui->textBrowser->append("Segments are collinear and intersection point does not exist.");
            }
        }
        else
        {
            qDebug() << "Calculate coefficients for vectors...";
            qDebug() << "Calculated det:" << collinear.m_det_number << "with det:" << collinear.m_det;
            double u = Segment3D::calc_u_to_segments(AB, CD, Vector3D::eps, collinear.m_det_number);
            qDebug() << "Calculated u:" << u;
            double v = Segment3D::calc_v_to_segments(AB, CD, Vector3D::eps, collinear.m_det_number);
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
