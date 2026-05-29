#ifndef CSVIMPORTER_H
#define CSVIMPORTER_H

#include <QPointF>
#include <QString>
#include <vector>

class CsvImporter {
public:
    static std::vector<QPointF> importPoints(const QString& filePath, bool* ok = nullptr);
};

#endif
