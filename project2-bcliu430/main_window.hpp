#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>
#include <QMainWindow>
#include <QLayout>
#include <QObject>
#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "repl_widget.hpp"
#include "qt_interpreter.hpp"
#include <fstream>

class MainWindow:public QWidget{
Q_OBJECT
public:
  // Default construct a MainWindow
   MainWindow(QWidget * parent = nullptr);

  // Default construct a MainWidow, using filename as the script file to attempt to preload
  MainWindow(std::string filename, QWidget * parent = nullptr);
private:

};
#endif
