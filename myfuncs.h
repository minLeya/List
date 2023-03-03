#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystructs.h"
#include "constants.h"
#include "ArrayNineStrings.h"
#include <string>
#include <functional>

//Основные функции
bool LoadingList(const std::string fileName, Employee* &head);
bool UnloadingList(const std::string fileName, Employee* head);
unsigned ListLength(Employee* head);
void PrintList(const Employee* head);
void deleteElement(Employee*& head, std::string userField, int choice);

//Вспомгательные функции
bool getListFromFile(Employee*& head, std::ifstream& fileName);
void getNewTrade(Employee*& head, std::stringstream& lieStream);
void InitializationNewTrade(std::stringstream& lineStream, Employee*& init_head);
char getCase();
//double GetNumber();
bool checkIfEqual(Employee*& currElement, std::string userField, int choice);



//Пользовательские функции
void MenuForChoices();
void case1(Employee* head);
void case2(Employee*& head);
void case3(const Employee* head);
void case4(Employee* head);
void case5(Employee* head);

#endif /* MYFUNCS_H_ */
