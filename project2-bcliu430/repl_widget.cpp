#include "repl_widget.hpp"

#include <QLayout>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include <QString>

REPLWidget::REPLWidget(QWidget *parent):QWidget(parent){

  mymsg = new QLineEdit;
  mymsg->setMinimumSize(330,30);
  mymsg->setPlaceholderText("Enter command");

  QLabel *msg = new QLabel(tr("vtscript>"));
  msg->setMinimumSize(70,30);
  QHBoxLayout *layout = new QHBoxLayout;

  layout->addWidget(msg);
  layout->addWidget(mymsg);

  this ->setLayout(layout);
  connect(mymsg,SIGNAL(returnPressed()), this, SLOT(getStr()));

}

void REPLWidget::getStr(){
    QString str = mymsg->text();
    emit lineEntered(str);
    cmd.push_back(str.toStdString());
    count = cmd.size();
    mymsg->setText("");
    return;

}

void REPLWidget::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Up){
        if(count != 0){
            count--;
        }
        else if(count == 0){
            return;
        }
        QString qstr = QString::fromStdString(cmd[count]);
        mymsg->setText(qstr);
        qDebug() << "up hit";
    }
    else if (e->key() == Qt::Key_Down){
        if(count!= cmd.size()){
            count ++;
        }
        else if(count == cmd.size()){
            return;
        }
        QString qstr = QString::fromStdString(cmd[count]);
        mymsg->setText(qstr);
        qDebug() << "down hit";
    }
}
