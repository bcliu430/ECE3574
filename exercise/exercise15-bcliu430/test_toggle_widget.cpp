#include <QtTest/QtTest>
#include <QtWidgets>
#include <QDebug>

#include "toggle_widget.h"

class TestToggleWidget : public QObject {
  Q_OBJECT

private slots:
  void testClick();
  // Define tests here

private:
  ToggleWidget Toggle;
};

// Implement the tests here

void TestToggleWidget::testClick(){
    auto pb = Toggle.findChild<QPushButton *>();
    QVERIFY(pb);
    auto rb = Toggle.findChild<QRadioButton *>();
    QVERIFY(rb);

    QTest::mouseClick(pb, Qt::LeftButton, Qt::NoModifier);
    QVERIFY(rb->isChecked());
}

QTEST_MAIN(TestToggleWidget)
#include "test_toggle_widget.moc"
