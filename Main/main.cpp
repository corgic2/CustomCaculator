#include <QApplication>
#include "../UIModule/CustomCaculator.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    CustomCaculator demo;
    demo.show();
    return app.exec();
}