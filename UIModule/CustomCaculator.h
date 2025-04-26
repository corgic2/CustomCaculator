#pragma once

#include <QMap>
#include <QString>
#include <QToolButton>
#include <QWidget>
#include <stack>
#include "ui_CustomCaculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CustomCaculatorClass; };
QT_END_NAMESPACE

class CustomCaculator : public QWidget
{
    Q_OBJECT

public:
    CustomCaculator(QWidget* parent = nullptr);
    ~CustomCaculator() override;
    void InitUI();

    int Caculate(const QString& text);
    bool IsOperator(char c);
    int Priority(char op);
    void Compute(std::stack<int>& nums, std::stack<char>& ops);
signals:

protected slots:
    void SlotBtnClickedToChangedLineEditText(bool bChcked);
    void SlotBtnBackSpace();    //删除按钮
    void SlotOperateToResult(); //等于按钮
private:
    Ui::CustomCaculatorClass* ui = new Ui::CustomCaculatorClass();

    QMap<QToolButton*, int> m_btnMap;
    QMap<QToolButton*, QString> m_optMap;
};
