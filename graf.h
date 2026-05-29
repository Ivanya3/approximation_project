#ifndef GRAF_H
#define GRAF_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include <QPointF>

class Graf : public QWidget {
    Q_OBJECT

public:
    enum SampleMode {
        Uniform,
        Random,
        Chebyshev
    };

    explicit Graf(QWidget *parent = nullptr, bool enableDrawing = true);

    void setWorldSize(int width, int height);
    void setGridStep(int step);
    void setDrawingEnabled(bool enabled);
    void setPoints(const std::vector<QPointF>& newPoints);
    void setPolyPoints(const std::vector<QPointF>& pointsForPoly);
    void setIlluminationPoints(const std::vector<QPointF>& pts);
    void showIllumination(bool show);
    void clear();

    std::vector<QPointF> getPoints() const;
    std::vector<QPointF> samplePoints(int count, SampleMode mode) const;
    std::vector<QPointF> sample6Points() const;

    int getWorldWidth() const { return worldWidth; }
    int getWorldHeight() const { return worldHeight; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QPointF worldToScreen(const QPointF& worldPoint) const;
    QPointF screenToWorld(const QPoint& screenPoint) const;

    std::vector<QPointF> userPoints;
    std::vector<QPointF> polynomialCurvePoints;
    std::vector<QPointF> highlightedPoints;

    double currentScale = 1.0;
    double xOffset = 0.0;
    double yOffset = 0.0;
    int worldWidth = 200;
    int worldHeight = 200;
    int gridStep = 20;

    bool isDrawingMode = false;
    bool isPanningMode = false;
    bool isDrawingEnabled = true;
    bool showHighlightedPoints = false;

    QPoint lastPanPosition;
};

#endif // GRAF_H
