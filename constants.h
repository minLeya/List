#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include "mystructs.h"

const std::string DEFAULT_NAME_IN_OUT{ "MyDataFile.txt" };
const unsigned char DEFAULT_COL{ 9 };
enum class EMPLOYEE_FIELD {
	SURNAME = 0,
	MIDDLENAME = 1,
	NAME = 2,
	AGE = 3,
	MARITALSTATUS = 4
};

const DefaultEmployee DEFAULT_EMPLOYEE{
	"Фамилия",
	"Имя",
	"Отчество",
	"Возраст",
	"Семейное положение"
};

#endif /* CONSTANTS_H_ */