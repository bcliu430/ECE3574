#include <QApplication>
#include "complex_widget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc,argv);

    ComplexWidget widget;

    widget.show();

    return app.exec();
}
