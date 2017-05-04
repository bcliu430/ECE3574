// a simple example using Qt
#include <cstdlib>
#include <iostream>
#include <vector>

#include <QWidget>
#include <QPainter>
#include <QApplication>
#include <QTextStream>


// an int list model
struct ListModel
{
  virtual std::size_t length() = 0;
  virtual int get(std::size_t index) = 0;
};

// how one might implement a list view in Qt
// this is just an example, Qt has a ListView already
class ListView : public QWidget
{
  Q_OBJECT
  
public:
  ListView(QWidget * parent = 0): QWidget(parent){
    QSize size(100,300);
    setMinimumSize(size);
    setMaximumSize(size);
    setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum));
  }
  void paintEvent(QPaintEvent * event){  
    QPainter painter(this);
    for(std::size_t i = 0; i < model->length(); ++i){
      QString entry;
      QTextStream(&entry) << model->get(i); 
      painter.drawText(10, 20*(i+1), entry);
    }
  }

  void setModel(ListModel * m){
    model = m;
  }
  
private:
  ListModel * model;
};


// a templated class that conforms to the ListModel interface
// for demontration, just an adaptor of std::vector
// note: std::vector does not have methods named  get or length
class SimpleList: public ListModel, public std::vector<int>
{
public:
  std::size_t length(){
    return std::vector<int>::size();
  }
  int get(std::size_t index){
    return (*this)[index];
  }
};

// needed because I am doing this all in one file
#include "example2.moc"

int main(int argc, char *argv[])
{
  SimpleList alist;

  alist.push_back(0);
  alist.push_back(1);
  alist.push_back(2);
  alist.push_back(3);

  QApplication app(argc, argv);

  ListView view;
  view.setModel(&alist);
  
  view.show();

  return app.exec();
}
