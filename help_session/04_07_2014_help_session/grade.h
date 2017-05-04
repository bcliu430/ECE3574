#include <QString>
#include <QJsonObject>
#include <QObject>

class Grade {

public:
	Grade();
	Grade(QString assignName, int theGrade, int maxGrade);
	Grade(const Grade &);
	bool operator==(const Grade& s);
	QJsonObject toJSONObject();

private:
	QString assignment;
	int grade;
	int max_grade;
};

