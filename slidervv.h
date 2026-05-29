#ifndef SLIDERVV_H
#define SLIDERVV_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>

class SliderVV : public QWidget
{
    Q_OBJECT
public:
    explicit SliderVV(QWidget *parent = nullptr);

    int value() const;
    void setRange(int min, int max);
    void setValue(int val);
signals:
    void valueChanged(int value);
private:
    QSlider* slider;
    QLabel* label;
};

#endif // SLIDERVV_H
