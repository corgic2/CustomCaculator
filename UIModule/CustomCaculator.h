#pragma once

#include <QWidget>
#include "ui_CustomCaculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CustomCaculatorClass; };
QT_END_NAMESPACE

class CustomCaculator : public QWidget
{
	Q_OBJECT

public:
	CustomCaculator(QWidget *parent = nullptr);
	~CustomCaculator();

private:
	Ui::CustomCaculatorClass * ui = new Ui::CustomCaculatorClass();
};
