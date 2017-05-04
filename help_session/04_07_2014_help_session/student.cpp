#include "student.h"
#include "grade.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>


Student::Student() {
	Student("", "", INT_MAX);
}

Student::Student(QString lastnme, QString firstnme, int studentId) {
	lastname = lastnme;
	firstname = firstnme;
	id = studentId;
}

Student::Student(const Student & s) {
	lastname = s.lastname;
	firstname = s.firstname;
	id = s.id;
	grades = s.grades;
}

Student & Student::operator=(const Student& s) {
	// check for self-assignment
	if (&s == this)
		return *this;

	lastname = s.lastname;
	firstname = s.firstname;
	id = s.id;
	grades = s.grades;

	return *this;

}

Student Student::fromJSON(QString json) {
	QJsonParseError error;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8(), &error);
	if (error.error != QJsonParseError::NoError) {
		throw error;
	}
	QJsonObject obj = jsonDoc.object();
	QJsonValue lastName = obj["lastname"];
	QJsonValue firstName = obj["firstname"];
	QJsonValue id = obj["id"];
	Student newStudent(lastName.toString(), firstName.toString(), id.toInt());
	QJsonArray grades = obj["grades"].toArray();
	for (QJsonValue gradeValue : grades) {
		QJsonObject gradeObj = gradeValue.toObject();
		Grade theGrade(gradeObj["assigment"].toString(), gradeObj["grade"].toInt(), gradeObj["max_grade"].toInt());
		newStudent.addGrade(theGrade);
	}
	return newStudent;
}

bool Student::operator==(const Student& s) {
	return (lastname == s.lastname && firstname == s.firstname && id == s.id && grades == s.grades);
}

void Student::addGrade(const Grade &grade) {
	//append copies grade
	grades.append(grade);
}


QJsonArray Student::getGradeJsonArray() {
	QJsonArray gradeArray;
	QJsonObject gradeTmpJsonObj;

	for(QList<Grade>::iterator it = grades.begin(); it != grades.end(); it++){
		gradeTmpJsonObj = it->toJSONObject();
		gradeArray.append(QJsonValue(gradeTmpJsonObj));
	}
	return gradeArray;
}

QJsonObject Student::toJsonObject() {
	QJsonArray grades = getGradeJsonArray();
	QJsonObject studentObj;
	studentObj["lastname"] = lastname;
	studentObj["firstname"] = firstname;
	studentObj["id"] = id;
	studentObj["grades"] = grades;
	return studentObj;
}

//stub
QString Student::toJson() {

	QJsonObject jsonObj = toJsonObject();
	return QJsonDocument(jsonObj).toJson();
}
