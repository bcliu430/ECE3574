#include <QTest>

#include <QCheckBox>
#include <QDial>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpression>

#include "example_widget.h"

class TestExampleWidget : public QObject {
  Q_OBJECT

private slots:

  void testFindByName();
  void testFindByType();
  void testFindByRegExp();

private:
  ExampleWidget widget;
};

void TestExampleWidget::testFindByName() {
  auto op = widget.findChild<QCheckBox *>("Option 1 CheckBox");
  
  QVERIFY2(op, "Could not find widget with name: 'Option 1 CheckBox'");
}

void TestExampleWidget::testFindByType() {
  auto d = widget.findChild<QCheckBox *>();
  
  QVERIFY2(d, "Could not find widget with type: QDial");
}

void TestExampleWidget::testFindByRegExp() {
  auto children =
      widget.findChildren<QCheckBox *>(QRegularExpression("^Option"));
  
  QVERIFY2(children.size() == 3, "Could not find all three option checkboxes");
}

QTEST_MAIN(TestExampleWidget)
#include "test_example_widget.moc"
