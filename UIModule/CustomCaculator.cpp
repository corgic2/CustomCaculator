#include "CustomCaculator.h"

CustomCaculator::CustomCaculator(QWidget* parent)
    : QWidget(parent)
{
    ui->setupUi(this);
}

CustomCaculator::~CustomCaculator()
{
    delete ui;
}
