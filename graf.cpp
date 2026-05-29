#include "graf.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <algorithm>
#include <cmath>

Graf::Graf(QWidget *parent, bool enableDrawing)
    : QWidget(parent)
{
    isDrawingMode = false;
    showHighlightedPoints = false;
    isDrawingEnabled = enableDrawing;
    setMouseTracking(true);
}

QPointF Graf::worldToScreen(const QPointF& worldPoint) const
{
    double wx = (worldPoint.x() + xOffset) * currentScale;
    double wy = (worldPoint.y() + yOffset) * currentScale;

    double screenX = (wx * width()) / worldWidth;
    double screenY = height() - (wy * height()) / worldHeight;
    return QPointF(screenX, screenY);
}

QPointF Graf::screenToWorld(const QPoint& screenPoint) const
{
    double wx = (static_cast<double>(screenPoint.x()) * worldWidth) / (width() * currentScale);
    double wy = (static_cast<double>(height() - screenPoint.y()) * worldHeight) / (height() * currentScale);

    double worldX = wx - xOffset;
    double worldY = wy - yOffset;
    return QPointF(worldX, worldY);
}

void Graf::setWorldSize(int width, int height)
{
    worldWidth = width;
    worldHeight = height;
    update();
}

void Graf::setGridStep(int step)
{
    gridStep = step;
    update();
}

void Graf::setDrawingEnabled(bool enabled)
{
    qDebug() << "Graf::setDrawingEnabled called with:" << enabled;
    isDrawingEnabled = enabled;
}

void Graf::setPoints(const std::vector<QPointF>& newPoints)
{
    userPoints = newPoints;
    update();
}

void Graf::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !isDrawingEnabled) {
        isPanningMode = true;
        lastPanPosition = event->pos();
        setCursor(Qt::ClosedHandCursor);
        return;
    }

    if (event->button() == Qt::LeftButton && isDrawingEnabled) {
        QPoint screenPoint = event->pos();
        QPointF worldPoint = screenToWorld(screenPoint);
        userPoints.push_back(worldPoint);
        isDrawingMode = true;
        update();
    }
}

void Graf::mouseMoveEvent(QMouseEvent *event)
{
    if (isPanningMode) {
        QPoint delta = event->pos() - lastPanPosition;
        lastPanPosition = event->pos();
        double dx = (static_cast<double>(delta.x()) * worldWidth) / (width() * currentScale);
        double dy = -(static_cast<double>(delta.y()) * worldHeight) / (height() * currentScale);
        xOffset += dx;
        yOffset += dy;

        update();
        return;
    }

    if (isDrawingMode && isDrawingEnabled) {
        QPoint screenPoint = event->pos();
        QPointF worldPoint = screenToWorld(screenPoint);
        userPoints.push_back(worldPoint);
        update();
    }
}

void Graf::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDrawingMode = false;
        if (isPanningMode) {
            isPanningMode = false;
            if (!isDrawingEnabled) {
                setCursor(Qt::OpenHandCursor);
            } else {
                setCursor(Qt::ArrowCursor);
            }
        }
    }
}

void Graf::wheelEvent(QWheelEvent *event)
{
    double zoomFactor = 1.1;

    if (event->angleDelta().y() > 0) {
        currentScale *= zoomFactor;
    } else {
        currentScale /= zoomFactor;
    }

    if (currentScale < 0.1) currentScale = 0.1;
    if (currentScale > 10.0) currentScale = 10.0;

    update();
}

void Graf::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    int screenWidth = this->width();
    int screenHeight = this->height();
    double worldWidthVisible = worldWidth / currentScale;
    double worldHeightVisible = worldHeight / currentScale;

    double leftWorld = -xOffset;
    double rightWorld = worldWidthVisible - xOffset;
    double topWorld = worldHeightVisible - yOffset;
    double bottomWorld = -yOffset;

    double gridStepWorld = 50.0 / currentScale;
    // Округляем до красивого числа
    double niceStep = pow(10, floor(log10(gridStepWorld)));
    if (gridStepWorld / niceStep > 5) niceStep *= 5;
    else if (gridStepWorld / niceStep > 2) niceStep *= 2;
    gridStepWorld = niceStep;

    // Рисуем вертикальные линии сетки
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
    double startX = floor(leftWorld / gridStepWorld) * gridStepWorld;
    for (double worldX = startX; worldX <= rightWorld; worldX += gridStepWorld) {
        QPointF screenPoint = worldToScreen(QPointF(worldX, 0));
        int screenX = static_cast<int>(screenPoint.x());
        if (screenX >= 0 && screenX <= screenWidth) {
            painter.drawLine(screenX, 0, screenX, screenHeight);
            painter.setPen(QPen(Qt::darkGray, 1));
            painter.drawText(screenX + 5, 15, QString::number(worldX, 'f', 1));
            painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
        }
    }

    // Рисуем горизонтальные линии сетки
    double startY = floor(bottomWorld / gridStepWorld) * gridStepWorld;
    for (double worldY = startY; worldY <= topWorld; worldY += gridStepWorld) {
        QPointF screenPoint = worldToScreen(QPointF(0, worldY));
        int screenY = static_cast<int>(screenPoint.y());
        if (screenY >= 0 && screenY <= screenHeight) {
            painter.drawLine(0, screenY, screenWidth, screenY);
            painter.setPen(QPen(Qt::darkGray, 1));
            painter.drawText(5, screenY - 2, QString::number(worldY, 'f', 1));
            painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
        }
    }

    // Оси координат
    QPointF origin = worldToScreen(QPointF(0, 0));
    painter.setPen(QPen(Qt::black, 2));
    if (origin.y() >= 0 && origin.y() <= screenHeight) {
        painter.drawLine(0, origin.y(), screenWidth, origin.y());
    }
    if (origin.x() >= 0 && origin.x() <= screenWidth) {
        painter.drawLine(origin.x(), 0, origin.x(), screenHeight);
    }
    painter.drawText(screenWidth - 20, screenHeight - 5, "X");
    painter.drawText(5, 15, "Y");

    painter.setPen(QPen(Qt::black, 2));
    for (int i = 1; i < userPoints.size(); ++i) {
        QPointF p1 = worldToScreen(userPoints[i-1]);
        QPointF p2 = worldToScreen(userPoints[i]);
        painter.drawLine(p1, p2);
    }

    painter.setPen(QPen(Qt::red, 3));
    for (int i = 1; i < polynomialCurvePoints.size(); ++i) {
        QPointF p1 = worldToScreen(polynomialCurvePoints[i-1]);
        QPointF p2 = worldToScreen(polynomialCurvePoints[i]);
        painter.drawLine(p1, p2);
    }

    if (showHighlightedPoints)
    {
        painter.setPen(QPen(Qt::blue));
        painter.setBrush(Qt::blue);

        for (const auto& point : highlightedPoints)
        {
            QPointF drawPoint = worldToScreen(point);
            painter.drawEllipse(drawPoint, 5, 5);
        }
    }

    painter.setPen(QPen(Qt::gray, 1));
    painter.drawText(10, screenHeight - 10, QString("Масштаб: %1x").arg(currentScale, 0, 'f', 1));
}

void Graf::clear()
{
    userPoints.clear();
    polynomialCurvePoints.clear();
    highlightedPoints.clear();
    update();
}

std::vector<QPointF> Graf::getPoints() const
{
    return userPoints;
}

std::vector<QPointF> Graf::sample6Points() const
{
    std::vector<QPointF> samplePoints;
    int n = userPoints.size();
    if (n < 6) return userPoints;

    samplePoints.push_back(userPoints.front());
    samplePoints.push_back(userPoints.back());

    for (int i = 1; i <= 4; ++i) {
        int i4 = i * (n-1) / 5;
        samplePoints.push_back(userPoints[i4]);
    }

    return samplePoints;
}

void Graf::setPolyPoints(const std::vector<QPointF>& pointsForPoly)
{
    polynomialCurvePoints = pointsForPoly;
    update();
}

void Graf::setIlluminationPoints(const std::vector<QPointF>& pts)
{
    highlightedPoints = pts;
    update();
}

void Graf::showIllumination(bool show)
{
    showHighlightedPoints = show;
    update();
}

std::vector<QPointF> Graf::samplePoints(int count, Graf::SampleMode mode) const
{
    int n = userPoints.size();
    if (n == 0) return {};
    if (n <= count) return userPoints;

    std::vector<QPointF> result;
    result.reserve(count);

    if (mode == Uniform) {
        for (int i = 0; i < count; ++i) {
            int idx = i * (n - 1) / (count - 1);
            result.push_back(userPoints[idx]);
        }
    }
    else if (mode == Random) {
        // Алгоритм Фишера-Йетса
        std::vector<int> indices(n);
        for (int i = 0; i < n; ++i) {
            indices[i] = i;
        }
        for (int i = 0; i < count; ++i) {
            int j = i + rand() % (n - i);
            std::swap(indices[i], indices[j]);
            result.push_back(userPoints[indices[i]]);
        }
    }
    else if (mode == Chebyshev) {
        for (int i = 0; i < count; ++i) {
            double t = cos((2.0 * i + 1) / (2.0 * count) * M_PI);
            int idx = static_cast<int>((t + 1) * 0.5 * (n - 1));
            result.push_back(userPoints[idx]);
        }
    }

    return result;
}


