#include "grade.h"
#include <QJsonObject>


Grade::Grade(QString assignName, int theGrade, int maxGrade) {
	assignment = assignName;
	grade = theGrade;
	max_grade = maxGrade;
}

Grade::Grade() {
	assignment = "";
	grade = 100;
	max_grade = 100;
}

Grade::Grade(const Grade & gradeObj) {
	assignment = gradeObj.assignment;
	grade = gradeObj.grade;
	max_grade = gradeObj.max_grade;
}



bool Grade::operator==(const Grade& s) {
	return (assignment == s.assignment && grade == s.grade && max_grade == s.max_grade);
}

QJsonObject Grade::toJSONObject() {

	QJsonObject gradeJson;
	gradeJson["assigment"] = assignment;
	gradeJson["grade"] = grade;
	gradeJson["max_grade"] = max_grade;

	return gradeJson;

}

