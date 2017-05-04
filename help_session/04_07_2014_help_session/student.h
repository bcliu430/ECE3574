#include <QString>
#include <QList>
#include <QJsonObject>
#include <QObject>
class QJsonArray;
class Grade;

class Student {
public:
	Student();
	Student(QString lastnme, QString firstnme, int stdudentId);
	Student(const Student & s);
	Student & operator=(const Student& s);
	bool operator==(const Student& s);
	QString toJson();
	QJsonObject toJsonObject();
	void addGrade(const Grade &grade);
	static Student fromJSON(QString json);

private:
	QJsonArray getGradeJsonArray();
	QString lastname;
	QString firstname;
	int id;
	QList<Grade> grades;
};
