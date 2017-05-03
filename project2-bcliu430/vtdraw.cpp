////////////////////////////////////////////////////////////////////////////////
// Filename:      main.cpp
// Name:          Beichen Liu 刘北辰
// Description:   This is the main file for vtscript
// Last Modified: ver.03-13-2017 File Created
//

#include <iostream>
#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "repl_widget.hpp"
#include "main_window.hpp"
#include "qt_interpreter.hpp"
#include <QApplication>
#include <QLayout>
#include <QWidget>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    MainWindow w;
    w.setMinimumSize(750, 500);
    if( argc >2){
        std::cerr <<"Error: invalid number of arguments to vtdraw\n";
        exit(EXIT_FAILURE);
    }
    else if (argc == 2){
        MainWindow w(argv[1]);
        qDebug() << argv[0] << argv[1];
        w.show();
    }
    else{
      qDebug() << "repl";
      w.show();
    }


    return app.exec();
}
