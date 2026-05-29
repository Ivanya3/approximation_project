#ifndef STATSWINDOW_H
#define STATSWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include <QPointF>

class SliderVV;
class Graf;

class StatsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatsWindow(QWidget *parent = nullptr);

private slots:
    void onAddPoint();
    void onRemovePoint();
    void onBuild();
    void onImportCsv();
    void onTableDataChanged(int row, int column);

private:
    void showPointsOnGraph();

    std::vector<double> leastSquaresPoly(const std::vector<double>& x,
                                         const std::vector<double>& y,
                                         int degree);
    std::vector<QPointF> generatePolyPoints(const std::vector<double>& coeffs,
                                            int worldWidth);

    SliderVV* sliderDegree;
    QTableWidget* tablePoints;
    QTableWidget* tableCoeffs;
    QPushButton* btnAddPoint;
    QPushButton* btnRemovePoint;
    QPushButton* btnBuild;
    QPushButton* btnImportCsv;
    Graf* graf;
};

#endif
