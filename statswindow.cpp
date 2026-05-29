#include "statswindow.h"
#include "slidervv.h"
#include "graf.h"
#include "csvimporter.h"

#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <cmath>

StatsWindow::StatsWindow(QWidget *parent)
    : QWidget(parent)
{
    sliderDegree = new SliderVV(this);
    sliderDegree->setRange(1, 10);
    sliderDegree->setValue(1);

    tablePoints = new QTableWidget(0, 2, this);
    tablePoints->setHorizontalHeaderLabels({"X", "Y"});
    tablePoints->horizontalHeader()->setStretchLastSection(true);

    tableCoeffs = new QTableWidget(1, 3, this);
    tableCoeffs->horizontalHeader()->setStretchLastSection(true);

    btnAddPoint = new QPushButton("Добавить точку", this);
    btnRemovePoint = new QPushButton("Удалить точку", this);
    btnBuild = new QPushButton("Построить", this);
    btnImportCsv = new QPushButton("Импорт CSV", this);

    graf = new Graf(this, false);
    graf->setWorldSize(500, 500);
    graf->setGridStep(50);
    graf->setMinimumSize(400, 400);

    // Левая панель с элементами управления
    QVBoxLayout* leftLayout = new QVBoxLayout();

    // Группа степени полинома
    QGroupBox* degreeGroup = new QGroupBox("Степень полинома", this);
    QVBoxLayout* degreeLayout = new QVBoxLayout();
    degreeLayout->addWidget(sliderDegree);
    degreeGroup->setLayout(degreeLayout);

    // Группа коэффициентов
    QGroupBox* coeffsGroup = new QGroupBox("Коэффициенты полинома", this);
    QVBoxLayout* coeffsLayout = new QVBoxLayout();
    coeffsLayout->addWidget(tableCoeffs);
    coeffsGroup->setLayout(coeffsLayout);

    // Группа точек
    QGroupBox* pointsGroup = new QGroupBox("Точки", this);
    QVBoxLayout* pointsLayout = new QVBoxLayout();
    pointsLayout->addWidget(tablePoints);

    // Кнопки
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(btnAddPoint);
    btnLayout->addWidget(btnRemovePoint);
    btnLayout->addWidget(btnBuild);
    btnLayout->addWidget(btnImportCsv);
    pointsLayout->addLayout(btnLayout);

    pointsGroup->setLayout(pointsLayout);

    // Собираем левую панель
    leftLayout->addWidget(degreeGroup);
    leftLayout->addWidget(coeffsGroup);
    leftLayout->addWidget(pointsGroup);
    leftLayout->addStretch();

    leftLayout->setContentsMargins(5, 5, 5, 5);
    leftLayout->setSpacing(10);

    // Основной layout
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addWidget(graf, 2);

    setLayout(mainLayout);

    // Настройка размеров
    tablePoints->setMinimumHeight(200);
    tableCoeffs->setMinimumHeight(100);
    sliderDegree->setMinimumWidth(150);

    resize(1000, 600);
    setMinimumSize(800, 500);

    // Политики размеров
    tablePoints->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableCoeffs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    graf->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Подключение сигналов
    connect(btnAddPoint, &QPushButton::clicked, this, &StatsWindow::onAddPoint);
    connect(btnRemovePoint, &QPushButton::clicked, this, &StatsWindow::onRemovePoint);
    connect(btnBuild, &QPushButton::clicked, this, &StatsWindow::onBuild);
    connect(btnImportCsv, &QPushButton::clicked, this, &StatsWindow::onImportCsv);

    connect(sliderDegree, &SliderVV::valueChanged, this, [=](int deg){
        tableCoeffs->setColumnCount(deg + 1);
    });

    connect(tablePoints, &QTableWidget::cellChanged, this, &StatsWindow::onTableDataChanged);
}

void StatsWindow::onAddPoint()
{
    int row = tablePoints->rowCount();
    tablePoints->insertRow(row);

    QTableWidgetItem* itemX = new QTableWidgetItem("0");
    QTableWidgetItem* itemY = new QTableWidgetItem("0");
    tablePoints->setItem(row, 0, itemX);
    tablePoints->setItem(row, 1, itemY);

    showPointsOnGraph();
}

void StatsWindow::onRemovePoint()
{
    int currentRow = tablePoints->currentRow();
    if (currentRow >= 0) {
        tablePoints->removeRow(currentRow);
        showPointsOnGraph();
    }
}

void StatsWindow::onBuild()
{
    int rows = tablePoints->rowCount();
    int degree = sliderDegree->value();

    std::vector<double> x, y;

    for (int i = 0; i < rows; ++i) {
        QTableWidgetItem* itemX = tablePoints->item(i, 0);
        QTableWidgetItem* itemY = tablePoints->item(i, 1);

        if (!itemX || !itemY) continue;

        bool okX, okY;
        double xi = itemX->text().toDouble(&okX);
        double yi = itemY->text().toDouble(&okY);

        if (okX && okY) {
            x.push_back(xi);
            y.push_back(yi);
        }
    }

    if (x.size() < degree + 1) {
        return;
    }

    auto coeffs = leastSquaresPoly(x, y, degree);

    if (coeffs.empty()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось вычислить коэффициенты полинома");
        return;
    }

    tableCoeffs->setColumnCount(coeffs.size());
    QStringList headers;
    for (int i = 0; i < coeffs.size(); ++i) {
        tableCoeffs->setItem(0, i, new QTableWidgetItem(QString::number(coeffs[i], 'f', 5)));
        headers << QString("a%1").arg(i);
    }
    tableCoeffs->setHorizontalHeaderLabels(headers);

    auto poly = generatePolyPoints(coeffs, graf->getWorldWidth());
    graf->setPolyPoints(poly);

    showPointsOnGraph();
}

void StatsWindow::showPointsOnGraph()
{
    std::vector<QPointF> points;
    int rows = tablePoints->rowCount();

    for (int i = 0; i < rows; ++i) {
        QTableWidgetItem* itemX = tablePoints->item(i, 0);
        QTableWidgetItem* itemY = tablePoints->item(i, 1);

        if (itemX && itemY) {
            bool okX, okY;
            double x = itemX->text().toDouble(&okX);
            double y = itemY->text().toDouble(&okY);

            if (okX && okY) {
                points.push_back(QPointF(x, y));
            }
        }
    }
    graf->setIlluminationPoints(points);
    graf->showIllumination(true);
}

void StatsWindow::onTableDataChanged(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    showPointsOnGraph();
}

void StatsWindow::onImportCsv()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Импорт точек из CSV",
        "",
        "CSV файлы (*.csv);;Текстовые файлы (*.txt);;Все файлы (*.*)"
        );

    if (filePath.isEmpty()) {
        return;
    }

    bool ok = false;
    std::vector<QPointF> importedPoints = CsvImporter::importPoints(filePath, &ok);

    if (!ok || importedPoints.empty()) {
        QMessageBox::warning(
            this,
            "Ошибка импорта",
            "Не удалось импортировать точки из файла.\n"
            "Проверьте формат данных (должны быть два столбца: X,Y)\n\n"
            "Поддерживаемые разделители: запятая, точка с запятой, табуляция, пробел"
            );
        return;
    }

    while (tablePoints->rowCount() > 0) {
        tablePoints->removeRow(0);
    }

    tablePoints->blockSignals(true);

    for (const auto& point : importedPoints) {
        int row = tablePoints->rowCount();
        tablePoints->insertRow(row);

        QTableWidgetItem* itemX = new QTableWidgetItem(QString::number(point.x()));
        QTableWidgetItem* itemY = new QTableWidgetItem(QString::number(point.y()));

        tablePoints->setItem(row, 0, itemX);
        tablePoints->setItem(row, 1, itemY);
    }

    tablePoints->blockSignals(false);

    showPointsOnGraph();

    graf->setPolyPoints({});
    tableCoeffs->setRowCount(1);
    tableCoeffs->setColumnCount(sliderDegree->value() + 1);
}

std::vector<double> StatsWindow::leastSquaresPoly(
    const std::vector<double>& x,
    const std::vector<double>& y,
    int degree)
{
    int n = x.size();
    int size = degree + 1;

    if (n < size) return {};

    std::vector<double> Sx(2*degree+1, 0.0);
    std::vector<double> Sxy(size, 0.0);

    for (int i = 0; i < n; ++i) {
        double xi = x[i];
        double yi = y[i];
        double xp = 1;

        for (int j = 0; j <= 2*degree; ++j) {
            if (j <= degree)
                Sxy[j] += yi * xp;

            Sx[j] += xp;
            xp *= xi;
        }
    }

    // для метода Гаусса
    std::vector<std::vector<double>> mat(size, std::vector<double>(size+1));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            mat[i][j] = Sx[i+j];

        mat[i][size] = Sxy[i];
    }

    // Метод Гаусса-Жордана
    for (int i = 0; i < size; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < size; ++k) {
            if (std::abs(mat[k][i]) > std::abs(mat[maxRow][i])) {
                maxRow = k;
            }
        }

        if (maxRow != i) {
            std::swap(mat[i], mat[maxRow]);
        }

        double d = mat[i][i];
        if (std::abs(d) < 1e-10) {
            return {};
        }

        for (int j = i; j <= size; ++j)
            mat[i][j] /= d;

        for (int k = 0; k < size; ++k) {
            if (k == i) continue;

            double f = mat[k][i];
            for (int j = i; j <= size; ++j)
                mat[k][j] -= f * mat[i][j];
        }
    }

    std::vector<double> res(size);
    for (int i = 0; i < size; ++i)
        res[i] = mat[i][size];

    return res;
}

std::vector<QPointF> StatsWindow::generatePolyPoints(
    const std::vector<double>& coeffs,
    int worldWidth)
{
    std::vector<QPointF> pts;

    if (coeffs.empty()) return pts;

    double startX = -worldWidth/2;
    double endX = worldWidth + worldWidth/2;

    for (double x = startX; x <= endX; ++x) {
        double y = 0;
        double xp = 1;

        for (double c : coeffs) {
            y += c * xp;
            xp *= x;
        }

        pts.push_back(QPointF(x, y));
    }

    return pts;
}
