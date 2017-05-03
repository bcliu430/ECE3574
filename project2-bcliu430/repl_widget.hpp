#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP

#include <string>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <vector>
#include <QKeyEvent>
#include <QString>

using std::string;
class QLineEdit;
class QLabel;

class REPLWidget:public QWidget{
Q_OBJECT
public:
  // Default construct a MessageWidget displaying no text
  REPLWidget(QWidget * parent = nullptr);
  void keyPressEvent(QKeyEvent *e);
signals:
  // A signal that sends the current edited text as a QString when the return key is pressed.
  void lineEntered(QString);
public slots:
  void getStr();


private:
  QLabel *msg;
  QLineEdit *mymsg;
  QHBoxLayout *layout;
  int count = 0;
  std::vector<string> cmd;
  QString str;


};


#endif
