#ifndef QT_INTERPRETER_HPP
#define QT_INTERPRETER_HPP

#include <sstream>      // std::stringstream, std::stringbuf
#include <cmath>
#include "message_widget.hpp"
#include "repl_widget.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include "expression.hpp"
#include "main_window.hpp"
#include "qgraphics_arc_item.hpp"
#include "interpreter_semantic_error.hpp"
#include <QObject>

class QtInterpreter: public QObject {
Q_OBJECT
public:
  // Default construct an QtInterpreter with the default environment and an empty AST
  QtInterpreter(QObject * parent = nullptr) { }
  ~QtInterpreter() { }
  void display(Expression e);
  QGraphicsItem *item;
  void read_file(std::istream &expre);

signals:
  // a signal emitting a graphic to be drawn as a pointer
  void drawGraphic(QGraphicsItem * item);

  // a signal emitting an informational message
  void info(QString message);

  // a signal emitting an error message
  void error(QString message);
public slots:
  // a public slot that accepts and expression string and parses/evaluates it
  void parseAndEvaluate(QString entry);
private:
  Expression root;
  Environment env;
  QString out;



};
#endif
