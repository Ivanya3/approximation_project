#include "slidervv.h"

SliderVV::SliderVV(QWidget *parent) : QWidget(parent)  {
    slider = new QSlider (Qt::Horizontal, this);
    label = new QLabel("0", this);

    QHBoxLayout* box = new QHBoxLayout(this);

    box->addWidget(slider);
    box->addWidget(label);

    connect(slider, &QSlider::valueChanged, this, [=](int val){
        label->setText(QString::number(val));
        emit valueChanged(val);
    });
}

int SliderVV:: value() const{
    return slider->value();
}

void SliderVV:: setRange(int min, int max){
    slider->setRange(min, max);
}

void SliderVV:: setValue(int val){
    slider->setValue(val);
}
