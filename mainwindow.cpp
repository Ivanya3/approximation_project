#include "mainwindow.h"
#include "statswindow.h"
#include "csvimporter.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройка графического виджета
    ui->widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->widget->setMinimumSize(300, 300);
    ui->widget->setWorldSize(200, 200);
    ui->widget->setGridStep(20);
    ui->widget->setDrawingEnabled(true);

    // Настройка комбобокса
    ui->comboDistribution->addItem("Равномерное");
    ui->comboDistribution->addItem("Рандомное");
    ui->comboDistribution->addItem("Чебышева");

    // Настройка слайдеров
    ui->sliderDegree->setRange(3, 20);
    ui->sliderPoints->setRange(4, 100);
    ui->sliderDegree->setValue(3);
    ui->sliderPoints->setValue(4);

    // Связывание слайдеров
    connect(ui->sliderDegree, &SliderVV::valueChanged, this, [=](int degree){
        int minPoints = degree + 1;
        ui->sliderPoints->setRange(minPoints, 100);
        if(ui->sliderPoints->value() < minPoints){
            ui->sliderPoints->setValue(minPoints);
        }
    });

    // Настройка кнопки руки
    connect(ui->btnHand, &QPushButton::clicked, this, [=](bool checked){
        if (checked) {
            ui->widget->setDrawingEnabled(false);
            ui->widget->setCursor(Qt::OpenHandCursor);
        } else {
            ui->widget->setDrawingEnabled(true);
            ui->widget->setCursor(Qt::ArrowCursor);
        }
    });

    // Настройка расположения фрейма
    ui->frame->move(0, 0);
    ui->frame->resize(ui->frame->width(), height());

    // Добавление теней (упрощенный код без дублирования)
    auto createShadow = [](int blurRadius = 10) {
        auto* shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(blurRadius);
        shadow->setColor(QColor(0, 0, 0, 50));
        shadow->setOffset(0, 0);
        return shadow;
    };

    ui->frame->setGraphicsEffect(createShadow());
    ui->labelFormula->setGraphicsEffect(createShadow());
    ui->btnHand->setGraphicsEffect(createShadow(15));
    ui->pushButton->setGraphicsEffect(createShadow(15));
    ui->pushButton_2->setGraphicsEffect(createShadow(15));
    ui->pushButton_4->setGraphicsEffect(createShadow(15));
    ui->pushButton_5->setGraphicsEffect(createShadow(15));

    // Создание кнопки переключения фрейма
    toggleFrameButton = new QPushButton("◀", this);
    toggleFrameButton->setFixedSize(40, 40);
    toggleFrameButton->setStyleSheet(
        "QPushButton {"
        "    background-color: white;"
        "    border-radius: 20px;"
        "    border: 1px solid #ccc;"
        "    font-size: 20px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #f0f0f0;"
        "}"
        );
    toggleFrameButton->raise();
    toggleFrameButton->setFocusPolicy(Qt::NoFocus);

    connect(toggleFrameButton, &QPushButton::clicked, this, [this]() {
        if (ui->frame->isVisible()) {
            ui->frame->hide();
            toggleFrameButton->setText("▶");
        } else {
            ui->frame->show();
            toggleFrameButton->setText("◀");
            toggleFrameButton->raise();
        }
        updateButtonPosition();
    });

    QTimer::singleShot(0, this, [this]() {
        updateButtonPosition();
    });
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    ui->frame->move(0, 0);
    ui->frame->resize(ui->frame->width(), height());
    updateButtonPosition();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateButtonPosition()
{
    if (!toggleFrameButton) return;

    if (ui->frame->isVisible()) {
        int frameWidth = ui->frame->width();
        if (frameWidth == 0) {
            frameWidth = 200;
        }
        int buttonX = ui->frame->x() + frameWidth - 45;
        int buttonY = ui->frame->y() + 5;
        toggleFrameButton->move(buttonX, buttonY);
    } else {
        toggleFrameButton->move(20, 20);
    }
    toggleFrameButton->raise();
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->clear();
    ui->labelError->setText("Макс. ошибка: --");
    ui->labelRMSE->setText("RMSE: --");
    ui->labelFormula->setText("Формула: --");
}

void MainWindow::on_pushButton_2_clicked()
{
    int degree = ui->sliderDegree->value();
    int pointCount = ui->sliderPoints->value();
    int distributionIndex = ui->comboDistribution->currentIndex();

    Graf::SampleMode sampleMode;
    switch(distributionIndex) {
    case 0: sampleMode = Graf::Uniform; break;
    case 1: sampleMode = Graf::Random; break;
    default: sampleMode = Graf::Chebyshev; break;
    }

    std::vector<QPointF> samplePoints = ui->widget->samplePoints(pointCount, sampleMode);

    if (samplePoints.size() < static_cast<size_t>(degree + 1)) return;

    // Извлечение координат
    std::vector<double> xCoordinates, yCoordinates;
    for (const auto& point : samplePoints) {
        xCoordinates.push_back(point.x());
        yCoordinates.push_back(point.y());
    }

    // Вычисление полинома
    std::vector<double> coefficients = leastSquaresPoly(xCoordinates, yCoordinates, degree);

    int worldWidth = ui->widget->getWorldWidth();
    std::vector<QPointF> curvePoints = generatePolyPoints(coefficients, worldWidth);

    // Отображение результатов
    ui->widget->setPolyPoints(curvePoints);
    ui->widget->setIlluminationPoints(samplePoints);

    // Вычисление ошибок
    std::vector<QPointF> allPoints = ui->widget->getPoints();
    double maxError = computeMaxError(allPoints, coefficients);
    double rmse = computeRMSE(allPoints, coefficients);

    ui->labelError->setText(QString("Макс. ошибка: %1").arg(maxError, 0, 'f', 2));
    ui->labelRMSE->setText(QString("RMSE: %1").arg(rmse, 0, 'f', 2));
    ui->labelFormula->setText("Формула: " + formatPolynomial(coefficients));

    qDebug() << "Максимальная ошибка:" << maxError;
    qDebug() << "RMSE:" << rmse;
}

void MainWindow::on_pushButton_3_clicked()
{
    // Пустая реализация
}

void MainWindow::on_pushButton_4_clicked()
{
    StatsWindow* statsWindow = new StatsWindow();
    statsWindow->show();
}

void MainWindow::on_pushButton_5_clicked()
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

    bool importSuccess = false;
    std::vector<QPointF> importedPoints = CsvImporter::importPoints(filePath, &importSuccess);

    if (!importSuccess || importedPoints.empty()) {
        QMessageBox::warning(
            this,
            "Ошибка импорта",
            "Не удалось импортировать точки из файла.\n"
            "Проверьте формат данных (должны быть два столбца: X,Y)"
            );
        return;
    }

    ui->widget->clear();
    ui->widget->setPoints(importedPoints);

    ui->labelError->setText("Макс. ошибка: --");
    ui->labelRMSE->setText("RMSE: --");
    ui->labelFormula->setText("Формула: --");
}

void MainWindow::on_openmatstat_clicked()
{
    StatsWindow* statsWindow = new StatsWindow();
    statsWindow->show();
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    ui->widget->showIllumination(checked);
}

void MainWindow::on_btnHand_toggled(bool checked)
{
    qDebug() << "Кнопка руки нажата!" << checked;
    if (checked) {
        ui->widget->setDrawingEnabled(false);
        ui->widget->setCursor(Qt::OpenHandCursor);
    } else {
        ui->widget->setDrawingEnabled(true);
        ui->widget->setCursor(Qt::ArrowCursor);
    }
}

// ==========================================
// МАТЕМАТИЧЕСКИЕ МЕТОДЫ
// ==========================================

std::vector<double> MainWindow::leastSquaresPoly(
    const std::vector<double>& x,
    const std::vector<double>& y,
    int degree)
{
    int n = x.size();
    int size = degree + 1;

    if (n < size) return {};

    std::vector<double> Sx(2 * degree + 1, 0.0);
    std::vector<double> Sxy(size, 0.0);

    for (int i = 0; i < n; ++i) {
        double xi = x[i];
        double yi = y[i];
        double xi_p = 1.0;

        for (int j = 0; j <= 2 * degree; ++j) {
            if (j <= degree) {
                Sxy[j] += yi * xi_p;
            }
            Sx[j] += xi_p;
            xi_p *= xi;
        }
    }

    // Построение расширенной матрицы
    std::vector<std::vector<double>> mat(size, std::vector<double>(size + 1));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            mat[i][j] = Sx[i + j];
        }
        mat[i][size] = Sxy[i];
    }

    // Метод Гаусса-Жордана с выбором главного элемента
    for (int i = 0; i < size; ++i) {
        // Поиск максимального элемента в столбце
        int maxRow = i;
        for (int k = i + 1; k < size; ++k) {
            if (std::abs(mat[k][i]) > std::abs(mat[maxRow][i])) {
                maxRow = k;
            }
        }

        if (maxRow != i) {
            std::swap(mat[i], mat[maxRow]);
        }

        double pivot = mat[i][i];
        if (std::abs(pivot) < 1e-9) return {};

        // Нормализация строки
        for (int j = i; j <= size; ++j) {
            mat[i][j] /= pivot;
        }

        // Исключение в других строках
        for (int k = 0; k < size; ++k) {
            if (k == i) continue;

            double factor = mat[k][i];
            for (int j = i; j <= size; ++j) {
                mat[k][j] -= factor * mat[i][j];
            }
        }
    }

    // Извлечение коэффициентов
    std::vector<double> coeffs(size);
    for (int i = 0; i < size; ++i) {
        coeffs[i] = mat[i][size];
    }

    return coeffs;
}

std::vector<QPointF> MainWindow::generatePolyPoints(
    const std::vector<double>& coeffs,
    int width)
{
    std::vector<QPointF> polyPoints;

    if (coeffs.empty()) return polyPoints;

    int degree = coeffs.size();
    int startX = -width;
    int endX = width * 2;

    for (int xi = startX; xi <= endX; ++xi) {
        double yi = 0.0;
        double x_pow = 1.0;

        for (int j = 0; j < degree; ++j) {
            yi += coeffs[j] * x_pow;
            x_pow *= xi;
        }

        polyPoints.push_back(QPointF(xi, yi));
    }

    return polyPoints;
}

double MainWindow::computeMaxError(
    const std::vector<QPointF>& originalPoints,
    const std::vector<double>& coeffs)
{
    if (originalPoints.empty() || coeffs.empty()) {
        return 0.0;
    }

    double maxError = 0.0;
    int degree = coeffs.size();

    for (const auto& point : originalPoints) {
        double x = point.x();
        double trueY = point.y();

        double polyY = 0.0;
        double x_pow = 1.0;

        for (int j = 0; j < degree; ++j) {
            polyY += coeffs[j] * x_pow;
            x_pow *= x;
        }

        double error = std::abs(trueY - polyY);
        if (error > maxError) {
            maxError = error;
        }
    }

    return maxError;
}

double MainWindow::computeRMSE(
    const std::vector<QPointF>& originalPoints,
    const std::vector<double>& coeffs)
{
    if (originalPoints.empty() || coeffs.empty()) {
        return 0.0;
    }

    double sumSquaredErrors = 0.0;
    int degree = coeffs.size();

    for (const auto& point : originalPoints) {
        double x = point.x();
        double trueY = point.y();

        double polyY = 0.0;
        double x_pow = 1.0;

        for (int j = 0; j < degree; ++j) {
            polyY += coeffs[j] * x_pow;
            x_pow *= x;
        }

        double error = trueY - polyY;
        sumSquaredErrors += error * error;
    }

    double rmse = std::sqrt(sumSquaredErrors / originalPoints.size());
    return rmse;
}

QString MainWindow::formatPolynomial(const std::vector<double>& coeffs)
{
    if (coeffs.empty()) {
        return "нет данных";
    }

    QString result = "y = ";
    int degree = coeffs.size() - 1;

    for (int i = degree; i >= 0; --i) {
        double coef = coeffs[i];

        if (std::abs(coef) < 1e-15) continue;

        if (coef > 0 && result != "y = ") {
            result += " + ";
        } else if (coef < 0) {
            result += " - ";
            coef = -coef;
        }

        QString coefStr;
        double absCoef = std::abs(coef);

        if (absCoef >= 0.01 && absCoef < 1000) {
            coefStr = QString::number(coef, 'f', 4);
            while (coefStr.contains('.') && (coefStr.endsWith('0') || coefStr.endsWith('.'))) {
                coefStr.chop(1);
            }
        } else {
            coefStr = QString::number(coef, 'e', 4);
        }

        if (std::abs(coef - 1.0) > 1e-10 || i == 0) {
            result += coefStr;
        }

        if (i == 1) {
            result += "·x";
        } else if (i > 1) {
            result += "·x" + QString::number(i);
        }
    }

    return result;
}
