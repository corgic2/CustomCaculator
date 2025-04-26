#include "CustomCaculator.h"
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#define ERRMsg "err"
CustomCaculator::CustomCaculator(QWidget* parent)
    : QWidget(parent)
{
    ui->setupUi(this);
    InitUI();
}

CustomCaculator::~CustomCaculator()
{
    delete ui;
}

void CustomCaculator::InitUI()
{
    m_btnMap.insert(ui->toolButton_10, 0);
    m_btnMap.insert(ui->toolButton_7, 1);
    m_btnMap.insert(ui->toolButton_8, 2);
    m_btnMap.insert(ui->toolButton_9, 3);
    m_btnMap.insert(ui->toolButton_4, 4);
    m_btnMap.insert(ui->toolButton_5, 5);
    m_btnMap.insert(ui->toolButton_6, 6);
    m_btnMap.insert(ui->toolButton, 7);
    m_btnMap.insert(ui->toolButton_2, 8);
    m_btnMap.insert(ui->toolButton_3, 9);
    for (auto& tmp : m_btnMap.keys())
    {
        connect(tmp, &QToolButton::clicked, this, &CustomCaculator::SlotBtnClickedToChangedLineEditText);
    }
    m_optMap.insert(ui->toolButton_11, "+");
    m_optMap.insert(ui->toolButton_12, "-");
    m_optMap.insert(ui->toolButton_13, "*");
    m_optMap.insert(ui->toolButton_14, "/");
    for (auto& tmp : m_optMap.keys())
    {
        connect(tmp, &QToolButton::clicked, this, &CustomCaculator::SlotBtnClickedToChangedLineEditText);
    }

    connect(ui->toolButton_16, &QToolButton::clicked, this, &CustomCaculator::SlotBtnBackSpace);

    connect(ui->toolButton_15, &QToolButton::clicked, this, &CustomCaculator::SlotOperateToResult);
}

int CustomCaculator::Caculate(const QString& text)
{
    std::stack<int> nums;
    std::stack<char> ops;
    int num = 0;
    std::string exp = text.toStdString();
    for (int i = 0; i < exp.length(); i++)
    {
        char c = exp[i];

        if (isdigit(c))
        {
            num = num * 10 + (c - '0');
        }
        else if (IsOperator(c))
        {
            nums.push(num);
            num = 0;

            // 处理优先级更高的运算符
            while (!ops.empty() && Priority(ops.top()) >= Priority(c))
            {
                Compute(nums, ops);
            }
            ops.push(c);
        }
        else if (c != ' ')
        {
            ui->lineEdit->setText(ERRMsg);
            //throw std::invalid_argument("Invalid character: " + std::string(1, c));
        }
    }

    nums.push(num);

    // 处理剩余运算符
    while (!ops.empty())
    {
        Compute(nums, ops);
    }
    if (nums.size() != 0)
    {
        return 0;
    }
    return nums.top();
}

bool CustomCaculator::IsOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int CustomCaculator::Priority(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    if (op == '*' || op == '/')
    {
        return 2;
    }
    return 0;
}

void CustomCaculator::Compute(std::stack<int>& nums, std::stack<char>& ops)
{
    if (nums.size() < 2 || ops.empty())
    {
        ui->lineEdit->setText(ERRMsg);
    }

    int b = nums.top();
    nums.pop();
    int a = nums.top();
    nums.pop();
    char op = ops.top();
    ops.pop();

    switch (op)
    {
    case '+':
        nums.push(a + b);
        break;
    case '-':
        nums.push(a - b);
        break;
    case '*':
        nums.push(a * b);
        break;
    case '/':
        if (b == 0)
        {
            ui->lineEdit->setText(ERRMsg);
            return;
        }
        nums.push(a / b); // 整数除法（向零取整）
        break;
    default:
        ui->lineEdit->setText(ERRMsg);
    }
}
void CustomCaculator::SlotBtnClickedToChangedLineEditText(bool bChcked)
{
    QObject* senderobj = sender();
    auto senderBtn = dynamic_cast<QToolButton*>(senderobj);
    QString text = ui->lineEdit->text();
    if (senderBtn == nullptr)
    {
        return;
    }
    if (m_btnMap.find(senderBtn) != m_btnMap.end())
    {
        ui->lineEdit->setText(text + QString::number(m_btnMap[senderBtn]));
    }
    else if (m_optMap.find(senderBtn) != m_optMap.end())
    {
        ui->lineEdit->setText(text + m_optMap[senderBtn]);
    }
}

void CustomCaculator::SlotBtnBackSpace()
{
    QString text = ui->lineEdit->text();
    text.remove(text.size() - 1, 1);
    ui->lineEdit->setText(text);
}

void CustomCaculator::SlotOperateToResult()
{
    int nums = Caculate(ui->lineEdit->text());

    ui->lineEdit->setText(QString::number(nums));
}