#include "main_window.hpp"
#include <QDebug>
#include <QWidget>
MainWindow::MainWindow(QWidget *parent):QWidget(parent){

  MessageWidget *msgWidget  = new MessageWidget();
  CanvasWidget  *canWidget  = new CanvasWidget();
  REPLWidget    *replWidget = new REPLWidget();
  QtInterpreter *qInterp = new QtInterpreter();
  QObject::connect(replWidget, SIGNAL(lineEntered(QString)), qInterp, SLOT(parseAndEvaluate(QString)));
  QObject::connect(qInterp,SIGNAL(info(QString)), msgWidget,SLOT(info(QString)));
  QObject::connect(qInterp,SIGNAL(error(QString)), msgWidget,SLOT(error(QString)));
  QObject::connect(qInterp,SIGNAL(drawGraphic(QGraphicsItem*)),
                  canWidget,SLOT(addGraphic(QGraphicsItem*)));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(msgWidget);
  layout->addWidget(canWidget);
  layout->addWidget(replWidget);

  this->setLayout(layout);
}
MainWindow::MainWindow(std::string filename, QWidget * parent){

  std::ifstream ifs(filename);

  MessageWidget *msgWidget  = new MessageWidget();
  CanvasWidget  *canWidget  = new CanvasWidget();
  REPLWidget    *replWidget = new REPLWidget();
  QtInterpreter *qInterp = new QtInterpreter();

  QObject::connect(replWidget, SIGNAL(lineEntered(QString)), qInterp, SLOT(parseAndEvaluate(QString)));
  QObject::connect(qInterp,SIGNAL(info(QString)), msgWidget,SLOT(info(QString)));
  QObject::connect(qInterp,SIGNAL(error(QString)), msgWidget,SLOT(error(QString)));
  QObject::connect(qInterp,SIGNAL(drawGraphic(QGraphicsItem*)),
                  canWidget,SLOT(addGraphic(QGraphicsItem*)));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(msgWidget);
  layout->addWidget(canWidget);
  layout->addWidget(replWidget);

  this->setLayout(layout);
  qInterp ->read_file(ifs);

}
