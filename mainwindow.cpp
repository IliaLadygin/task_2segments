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
        qDebug() << "\n__Debug calc__ || ans = (0, 0.5, 0)";
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 1, 1, "DebugA");    Vector3D B(0, 3, 1, "DebugB");
        Vector3D C(0, 2, -2, "DebugC");    Vector3D D(0, 2, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0, 2, 1)");
        qDebug() << "\n__Debug calc__ || ans = (0, 2, 1)";
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 0, 1, "DebugA");    Vector3D B(0, 0, -1, "DebugB");
        Vector3D C(1, 0, -2, "DebugC");    Vector3D D(0, 0, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = x");
        qDebug() << "\n__Debug calc__ || ans = x";
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 0, 1, "DebugA");    Vector3D B(0, 0, -1, "DebugB");
        Vector3D C(1, 0, -2, "DebugC");    Vector3D D(1, 0, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = x");
        qDebug() << "\n__Debug calc__ || ans = x";
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 0, 1, "DebugA");    Vector3D B(0, 0, -1, "DebugB");
        Vector3D C(0, 0, 1, "DebugC");    Vector3D D(1, 0, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0, 0, 1)");
        qDebug() << "\n__Debug calc__ || ans = (0, 0, 1)";
        calc_ans(A, B, C, D);
    }
    {
        Vector3D A(0, 0, 1, "DebugA");    Vector3D B(0, 0, -1, "DebugB");
        Vector3D C(0, 0, 1, "DebugC");    Vector3D D(1, 1, 2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0, 0, 1)");
        qDebug() << "\n__Debug calc__ || ans = (0, 0, 1)";
        calc_ans(A, B, C, D);
    }
    {   // \note Скорее всего указанные точки недостаточно точные
        Vector3D A(1, 1, 3.5, "DebugA");    Vector3D B(0.5, 0.3, -1, "DebugB");
        Vector3D C(-1.2, -2, 1, "DebugC");    Vector3D D(1.86, 2.16, 1.99, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0.79, 0.71, 1.65) (wrong precision of points)");
        qDebug() << "\n__Debug calc__ || ans = (0.79, 0.71, 1.65) (wrong precision of points)";
        calc_ans(A, B, C, D);
    }
    {   // \note Скорее всего указанные точки недостаточно точные
        Vector3D A(1, 1, 3.5, "DebugA");    Vector3D B(0.5, 0.3, -1, "DebugB");
        Vector3D C(-1.2, -2, 1, "DebugC");    Vector3D D(0.79, 0.71, 1.65, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = (0.79, 0.71, 1.65) (wrong precision of points)");
        qDebug() << "\n__Debug calc__ || ans = (0.79, 0.71, 1.65) (wrong precision of points)";
        calc_ans(A, B, C, D);
    }
    {   // \note "Нулевой" сегмент, принадлежащий второму сегменту
        Vector3D A(-1, -1, -1, "DebugA");    Vector3D B(-1, -1, -1, "DebugB");
        Vector3D C(-1.2, -1.2, -1.2, "DebugC");    Vector3D D(1.2, 1.2, 1.2, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = A or B");
        qDebug() << "\n__Debug calc__ || ans = A or B";
        calc_ans(A, B, C, D);
    }
    {   // \note "Нулевой" сегмент, принадлежащий второму сегменту
        Vector3D A(-1.2, -1.2, -1.2, "DebugA");    Vector3D B(1.2, 1.2, 1.2, "DebugB");
        Vector3D C(1, 1, 1, "DebugC");    Vector3D D(1, 1, 1, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = C or D");
        qDebug() << "\n__Debug calc__ || ans = C or D";
        calc_ans(A, B, C, D);
    }
    {   // \note сегменты лежат на одной линии, но не пересекаются
        Vector3D A(1, 0, 0, "DebugA");    Vector3D B(-1, 0, 0, "DebugB");
        Vector3D C(2, 0, 0, "DebugC");    Vector3D D(4, 0, 0, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = сегменты лежат на одной линии, но не пересекаются");
        qDebug() << "\n__Debug calc__ || ans = сегменты лежат на одной линии, но не пересекаются";
        calc_ans(A, B, C, D);
    }
    {   // \note сегменты лежат на одной линии и пересекаются в одной точке
        Vector3D A(1, 0, 0, "DebugA");    Vector3D B(-1, 0, 0, "DebugB");
        Vector3D C(1, 0, 0, "DebugC");    Vector3D D(4, 0, 0, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = сегменты лежат на одной линии и пересекаются в одной точке");
        qDebug() << "\n__Debug calc__ || ans = сегменты лежат на одной линии и пересекаются в одной точке";
        calc_ans(A, B, C, D);
    }
    {   // \note сегменты лежат на одной линии и имеют целый сегмент пересечений AC
        Vector3D A(1, 0, 0, "DebugA");    Vector3D B(-1, 0, 0, "DebugB");
        Vector3D C(0, 0, 0, "DebugC");    Vector3D D(4, 0, 0, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = сегменты лежат на одной линии и имеют целый сегмент пересечений AC");
        qDebug() << "\n__Debug calc__ || ans = сегменты лежат на одной линии и имеют целый сегмент пересечений AC";
        calc_ans(A, B, C, D);
    }
    {   // \note сегменты лежат на одной линии и имеют целый сегмент пересечений BC
        Vector3D A(-1, 0, 0, "DebugA");    Vector3D B(1, 0, 0, "DebugB");
        Vector3D C(0, 0, 0, "DebugC");    Vector3D D(4, 0, 0, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = сегменты лежат на одной линии и имеют целый сегмент пересечений BC");
        qDebug() << "\n__Debug calc__ || ans = сегменты лежат на одной линии и имеют целый сегмент пересечений BC";
        calc_ans(A, B, C, D);
    }
    {   // \note сегменты лежат на одной линии и имеют целый сегмент пересечений DB
        Vector3D A(-1, 0, 0, "DebugA");    Vector3D B(1, 0, 0, "DebugB");
        Vector3D C(4, 0, 0, "DebugC");    Vector3D D(0, 0, 0, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = сегменты лежат на одной линии и имеют целый сегмент пересечений DB");
        qDebug() << "\n__Debug calc__ || ans = сегменты лежат на одной линии и имеют целый сегмент пересечений DB";
        calc_ans(A, B, C, D);
    }
    {   // \note сегменты лежат на одной линии и имеют целый сегмент пересечений DA
        Vector3D A(-1, 0, 0, "DebugA");    Vector3D B(1, 0, 0, "DebugB");
        Vector3D C(-4, 0, 0, "DebugC");    Vector3D D(0, 0, 0, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = сегменты лежат на одной линии и имеют целый сегмент пересечений DA");
        qDebug() << "\n__Debug calc__ || ans = сегменты лежат на одной линии и имеют целый сегмент пересечений DA";
        calc_ans(A, B, C, D);
    }
    {   // \note сегмент CD внутри сегмента AB
        Vector3D A(5, 0, 1, "DebugA");    Vector3D B(2, 0, 1, "DebugB");
        Vector3D C(3, 0, 1, "DebugC");    Vector3D D(4, 0, 1, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = сегмент CD внутри сегмента AB");
        qDebug() << "\n__Debug calc__ || ans = сегмент CD внутри сегмента AB";
        calc_ans(A, B, C, D);
    }
    {   // \note сегмент AB внутри сегмента CD
        Vector3D A(3, 0, 1, "DebugA");    Vector3D B(4, 0, 1, "DebugB");
        Vector3D C(5, 0, 1, "DebugC");    Vector3D D(2, 0, 1, "DebugD");
        ui->textBrowser->append("__Debug calc__ || ans = сегмент AB внутри сегмента CD");
        qDebug() << "\n__Debug calc__ || ans = сегмент AB внутри сегмента CD";
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
        qDebug() << "General surface exists.";
        Segment3D::Collinear collinear = AB.is_collinear_to_segment(CD);
        if (collinear.m_is_collinear)
        {
            qDebug() << "Segment AB is collinear to segment CD.";
            ui->textBrowser->append("Segment AB is collinear to segment CD.");
            if (AB.norm() < Vector3D::eps) // Проверки на нулевые сегменты
            {
                qDebug() << "Segment AB has zero length.";
                ui->textBrowser->append("Segment AB has zero length.");
                if (CD.is_consist_point(AB.getStart())) {
                    qInfo() << "Point A (or equal point B) is belongs to the segment CD and it is a intersection point.";
                    ui->textBrowser->append("Point A (or equal point B) is belongs to the segment CD and it is a intersection point.");
                }
                else {
                    qInfo() << "Intersection point does not exist.";
                    ui->textBrowser->append("Intersection point does not exist.");
                }
            }
            else if (CD.norm() < Vector3D::eps)
            {
                qDebug() << "Segment CD has zero length.";
                ui->textBrowser->append("Segment CD has zero length.");
                if (AB.is_consist_point(CD.getStart())) {
                    qInfo() << "Point C (or equal point D) is belongs to the segment AB and it is a intersection point.";
                    ui->textBrowser->append("Point C (or equal point D) is belongs to the segment AB and it is a intersection point.");
                }
                else {
                    qInfo() << "Intersection point does not exist.";
                    ui->textBrowser->append("Intersection point does not exist.");
                }
            }
            else
            {
                // Проверка не лежат ли сегменты на одной прямой
                if (AB.is_line_with_segment_consist_point(C))
                {
                    if (AB.is_consist_point(C) || AB.is_consist_point(D) || CD.is_consist_point(A) || CD.is_consist_point(B))
                    {
                        qDebug() << QString::fromStdString(AB.get_string_to_show());
                        qDebug() << QString::fromStdString(CD.get_string_to_show());
                        Segment3D intersection;
                        // Рассмотрение 6-и случаев, чтобы понять, какой именно сегмент является пересечением
                        // TODO возможно есть способ сократить число проверок
                        if (AB.is_consist_point(C) && CD.is_consist_point(B)) { // Check is intersection segment CB
                            intersection = Segment3D(C, B, "Intersection");
                        }
                        else if (AB.is_consist_point(C) && CD.is_consist_point(A)) { // Check is intersection segment AC
                            intersection = Segment3D(A, C, "Intersection");
                        }
                        else if (AB.is_consist_point(D) && CD.is_consist_point(B)) { // Check is intersection segment DB
                            intersection = Segment3D(D, B, "Intersection");
                        }
                        else if (AB.is_consist_point(D) && CD.is_consist_point(A)) { // Check is intersection segment AD
                            intersection = Segment3D(A, D, "Intersection");
                        }
                        else if (AB.is_consist_point(C) && AB.is_consist_point(D)) { // Check is segment CD inside segment AB
                            intersection = Segment3D(C, D, "Intersection");
                        }
                        else if (CD.is_consist_point(A) && CD.is_consist_point(B)) { // Check is segment AB inside segment CD
                            intersection = Segment3D(A, B, "Intersection");
                        }
                        else throw "Error while ckecking intersection segment.";
                        if (intersection.norm() < Vector3D::eps)
                        {
                            qInfo() << "Zero length segment" << QString::fromStdString(intersection.get_string_to_show()) << "is an intersection point.";
                            ui->textBrowser->append("Zero length segment " + QString::fromStdString(intersection.get_string_to_show()) + " is an intersection point.");
                        }
                        else
                        {
                            qInfo() << "Segment" << QString::fromStdString(intersection.get_string_to_show()) << "is an intersection segment.";
                            ui->textBrowser->append("Segment " + QString::fromStdString(intersection.get_string_to_show()) + " is an intersection segment.");
                        }
                    }
                    else
                    {
                        qInfo() << "Segments are collinear, belong to one line, but don't have an intersection - intersection point does not exist.";
                        ui->textBrowser->append("Segments are collinear, belong to one line, but don't have an intersection - intersection point does not exist.");
                    }
                }
                else
                {
                    qInfo() << "Segments are collinear and don't belong to one line - intersection point does not exist.";
                    ui->textBrowser->append("Segments are collinear and don't belong to one line - intersection point does not exist.");
                }
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
