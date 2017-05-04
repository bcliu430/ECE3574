#include <cstdlib>
#include <QJsonDocument>
#include <QJsonArray>
#include "student.h"
#include "grade.h"
#include <QDebug>
#include <QFile>
#include <assert.h>
#define NUMGRADES 10


int main(void) {

	/*
	*	How to read objects into a file in JSON format
	*/
	//open the file
	QFile file("student.txt");
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
		return EXIT_FAILURE;
	//make a stream of the file
	QTextStream out(&file);

	Student john("Doe", "John", 1);
	for (int i = 0; i < NUMGRADES; i++) {
		john.addGrade(Grade("AssignName", i, 100));
	}

	QString json = john.toJson();
	out << json;

	out.flush();
	file.close();

	/*
	*	How to take JSON and convert it into C++ objects
	*/

	Student newStudent;
	//json[json.size()-2] = ' ';
	try {
		newStudent = Student::fromJSON(json);
	} catch (QJsonParseError error) {
		qDebug() << error.errorString();
	}

	assert(newStudent == john);
	return EXIT_SUCCESS;
}
