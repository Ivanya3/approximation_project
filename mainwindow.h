#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_openmatstat_clicked();
    void on_checkBox_toggled(bool checked);
    void on_btnHand_toggled(bool checked);

private:
    void updateButtonPosition();
    std::vector<double> leastSquaresPoly(const std::vector<double>& x,
                                         const std::vector<double>& y,
                                         int degree);
    std::vector<QPointF> generatePolyPoints(const std::vector<double>& coeffs,
                                            int width);
    double computeMaxError(const std::vector<QPointF>& originalPoints,
                           const std::vector<double>& coeffs);
    double computeRMSE(const std::vector<QPointF>& originalPoints,
                       const std::vector<double>& coeffs);
    QString formatPolynomial(const std::vector<double>& coeffs);

    Ui::MainWindow *ui;
    QPushButton *toggleFrameButton;
};

#endif
