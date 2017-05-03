#include "message_widget.hpp"

#include <QLayout>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>
#include <QPalette>

MessageWidget::MessageWidget(QWidget *parent):QWidget(parent){

  mymsg = new QLineEdit;
  mymsg -> setReadOnly(true);
  mymsg->setMinimumSize(330,30);
  QLabel *msg = new QLabel(this);
  msg->setText("Message:");
  msg->setMinimumSize(70,30);
  QHBoxLayout *layout = new QHBoxLayout;

  layout->addWidget(msg);
  layout->addWidget(mymsg);

  this ->setLayout(layout);

}

void MessageWidget::info(QString message){
  QPalette *pal = new QPalette();
  mymsg->setPalette(*pal);
  mymsg->setText(message);

}

void MessageWidget::error(QString message){
    QPalette *pal = new QPalette(Qt::red);
    mymsg->setText(message);
    mymsg->selectAll();
    pal->setColor(QPalette::Highlight,Qt::red);
    pal->setColor(QPalette::HighlightedText,Qt::white);
    mymsg->setPalette(*pal);
}
