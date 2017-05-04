#include <QTest>

class MyTest: public QObject
{
  Q_OBJECT

private slots:
  
  void test1();
};

void MyTest::test1()
{
  QVERIFY(true);
}

QTEST_MAIN(MyTest)
#include "mytest.moc"
