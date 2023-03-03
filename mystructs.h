#ifndef MYSTRUCTS_H_
#define MYSTRUCTS_H_

#include <string>

struct EmployeeData {
	std::string surname;
	std::string name;
	std::string middlename;
	std::string age;
	std::string maritalstatus;
};

struct Employee {
	Employee* next{};
	EmployeeData data{};
};

struct DefaultEmployee {
	std::string def_surname;
	std::string def_name;
	std::string def_middlename;
	std::string def_age;
	std::string def_maritalstatus;
};

#endif /* MYSTRUCTS_H_*/