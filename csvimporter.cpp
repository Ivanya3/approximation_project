#include "csvimporter.h"
#include <QFile>
#include <QTextStream>

std::vector<QPointF> CsvImporter::importPoints(const QString& filePath, bool* ok)
{
    std::vector<QPointF> points;

    if (ok) *ok = false;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return points;
    }

    QTextStream stream(&file);
    int lineNumber = 0;

    while (!stream.atEnd()) {
        lineNumber++;
        QString line = stream.readLine().trimmed();

        if (line.isEmpty() || line.startsWith("#") || line.startsWith("//")) {
            continue;
        }

        QStringList parts;
        if (line.contains(',')) {
            parts = line.split(',');
        } else if (line.contains(';')) {
            parts = line.split(';');
        } else if (line.contains('\t')) {
            parts = line.split('\t');
        } else {
            parts = line.split(' ', Qt::SkipEmptyParts);
        }

        if (parts.size() >= 2) {
            bool xOk, yOk;
            double x = parts[0].trimmed().toDouble(&xOk);
            double y = parts[1].trimmed().toDouble(&yOk);
            if (xOk && yOk) {
                points.push_back(QPointF(x, y));
            }
        }
    }

    file.close();

    if (!points.empty() && ok) {
        *ok = true;
    }

    return points;
}

