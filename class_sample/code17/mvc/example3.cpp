#include <QWidget>
#include <QTextEdit>
#include <QTreeView>
#include <QLayout>
#include <QDebug>
#include <QApplication>
#include <QFileSystemModel>

class Controller: public QWidget
{
  Q_OBJECT

public:
  
  Controller(){

    QHBoxLayout *layout = new QHBoxLayout;
    
    textView = new QTextEdit;
    treeView = new QTreeView;
    
    model = new QFileSystemModel;
    model->setRootPath(QDir::homePath()); 
    treeView->setModel(model);

    QObject::connect(treeView, SIGNAL(activated(const QModelIndex&)),
		     this, SLOT(activated(const QModelIndex&)));
  
    layout->addWidget(treeView);
    layout->addWidget(textView);

    setLayout(layout);
  }

public slots:  

  void activated(const QModelIndex & index){
    QFileInfo info = model->fileInfo(index);
    if(!info.isDir()){
      qDebug() << info.fileName();

      // could load the file
      // and set as the document of the textEdit Widget
    }
  }
  
private:

  QTextEdit *textView;
  QTreeView *treeView;
  QFileSystemModel * model;
};

#include "example3.moc"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  Controller control;
  control.show();
  
  return app.exec();  
}
