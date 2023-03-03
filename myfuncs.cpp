#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "mystructs.h"
#include "myfuncs.h"
#include "ArrayNineStrings.h"
#include "constants.h"


//ОСНОВНЫЕ ФУНКЦИИ
//Вывод данных из файла в динамический список
bool LoadingList(const std::string fileName, Employee*& head)
{
	std::ifstream out_DataFile(fileName);
	if (!out_DataFile)
	{
		std::cerr << "Не удалось открыть файл!" << '\n';
		return false;
	}
	else
	{
		if (getListFromFile(head, out_DataFile))
			return true;
		else
			return false;
	}
}

//Вывод данных из динамического списка в файл
bool UnloadingList(const std::string fileName, Employee* head)
{
	Employee* tail{ head };
	std::ofstream in_DataFile(fileName);
	if (!in_DataFile)
	{
		std::cerr << "Не удалось открыть файл!" << '\n';
		return false;
	}
	else
	{
		if (head != nullptr)
		{
			do {
				if (tail->next != head)
				{
					in_DataFile << tail->data.surname << ";" << tail->data.name << ";" << tail->data.middlename << ";" << tail->data.age << ";" << tail->data.maritalstatus << '\n';
					tail = tail->next;
				}
				else
				{
					in_DataFile << tail->data.surname << ";" << tail->data.name << ";" << tail->data.middlename << ";" << tail->data.age << ";" << tail->data.maritalstatus;
					tail = tail->next;
				}
			} while (tail != head);
			while (true)
			{
				Employee* clean_ptr{ tail };
				tail = tail->next;
				std::cout << "Данные о человеке " << clean_ptr->data.surname << ",... выгружены и удалены из оперативной памяти." << '\n';
				delete clean_ptr;
				if (tail == head)
					break;
			}
		}

		in_DataFile.close();
		return true;
	}
}

//Для case1 - количество элементов динамического списка
unsigned ListLength(Employee* head)
{
	Employee* current{ head };
	unsigned length{ 0 };
	if (head != nullptr)
	{
		if (current->next != head)
		{
			while (current->next != head)
			{
				length++;
				current = current->next;
			}
			return ++length;
		}
		else
		{
			return ++length;
		}
	}
	else
	{
		return length;
	}
}

//Для case3 - печать списка на консоль
void PrintList(const Employee* head)
{
	const Employee* tail{ head };
	if (head != nullptr)
	{
		int index_number{};
		std::cout << "\t\tВаш список:" << '\n';
		do {
			index_number++;
			std::cout << index_number << ") " << tail->data.surname << ";" << tail->data.name << ";" << tail->data.middlename << ";" << tail->data.age << ";" << tail->data.maritalstatus << '\n';
			tail = tail->next;
		} while (tail != head);
	}
	else
	{
		std::cout << "Список пуст." << '\n';
	}
}


//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
//Построчное чтение данных из файла 
bool getListFromFile(Employee*& head, std::ifstream& fileName)
{
	int count_str{ 0 }, flag{};
	std::string DataLine{};
	while (!fileName.eof())
	{
		if (std::getline(fileName, DataLine))
		{
			count_str++;
			flag++;
			std::stringstream lineStream{ DataLine };
			getNewTrade(head, lineStream);
		}
	}
	return true;
}


//Получение нового элемента по указателю и информационному полю
void getNewTrade(Employee*& head, std::stringstream& lineStream)
{
	if (head == nullptr)
	{
		head = new Employee{};
		InitializationNewTrade(lineStream, head);
		head->next = head;
	}
	else
	{
		Employee* tail{ head };
		while (tail->next != head)
		{
			tail = tail->next;
		}
		tail->next = new Employee{};
		tail = tail->next;
		InitializationNewTrade(lineStream, tail);
		tail->next = head;
	}
}

//Обеспечение записи данных в информационное поле элемента динамического списка с привязыванием их к указателю
void InitializationNewTrade(std::stringstream& lineStream, Employee*& init_head)
{
	std::string data{};
	std::array<std::string, DEFAULT_COL> str_value;
	int index_head{ 0 };
	while (std::getline(lineStream, data, ';'))
	{
		str_value[index_head] = data;
		index_head++;
	}

	init_head->data.surname = str_value[0];
	init_head->data.name = str_value[1];
	init_head->data.middlename = str_value[2];
	init_head->data.age = str_value[3];
	init_head->data.maritalstatus = str_value[4];
}


//Запрос действий с динамическим списком у пользователя
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
		{
			return choice[0];
		}
		else
		{
			std::cout << '\n' << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 5). Повторите ввод:" << '\n';
		}
	}
}

////Получение номера элемента у пользователя (для удаления)
//double GetNumber()
//{
//	while (true)
//	{
//		double num;
//		std::cin >> num;
//		if (std::cin.fail())
//		{
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			std::cout << "Ошибка ввода, Вы ввели не число. Повторите ввод:\n";
//		}
//		else if (num != static_cast<int>(num))
//		{
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			std::cout << "Вы ввели не натуральное число. Повторите ввод:\n ";
//		}
//		else
//		{
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			return num;
//		}
//	}
//}


//ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ
//Пользовательское меню
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << '\n' <<
		"1) Подсчитать число элементов списка." << '\n' <<
		"2) Удалить заданный элемент из списка по полю." << '\n' <<
		"3) Печать всех элементов (вывод на консоль)." << '\n' <<
		"4) Сброс значений всех элементов (все значения элементов будут обнулены)." << '\n' <<
		"5) Выход." << '\n';
}

//Запрос количества элементов в списке пользователем
void case1(Employee* head)
{
	unsigned length = ListLength(head);
	std::cout << "Длина Вашего списка на данный момент: " << length << '\n';
}
//удаление
//проверка соответствия поля
bool checkIfEqual(Employee*& currElement, std::string userField, int choice)
{
	switch (choice)
	{
	case 1: 
		if (currElement->data.surname.contains(userField))
			return true;
		else break;
	case 2:
		if (currElement->data.name.contains(userField))
			return true;
		else break;
	case 3:
		if (currElement->data.middlename.contains(userField))
			return true;
		else break;
	case 4:
		if (currElement->data.age.contains(userField))
			return true;
		else break;
	case 5:
		if (currElement->data.maritalstatus.contains(userField))
			return true;
		else break;
	}
	return false;
}
//удаление элемента по полю
void deleteElement(Employee*& head, std::string userField, int choice)
{
	if (head == nullptr) {
		std::cout << "Список пустой.";
		return;
	}
	Employee* temp{ head };
	Employee* prev{ nullptr };
	// удаляем первый элемент если совпадают поля
	if (checkIfEqual(head, userField, choice))
	{
		// находим последний элемент
		while (temp->next != head)
			temp = temp->next;

		// ставим указатель с последнего элемента на второй вместо первого
		temp->next = head->next;
		delete head;
		head = temp->next;
		return;
	}
	// храним предыдущий элемент и переадресовываем его next в случае удаления temp 
	while (true) {
		prev = temp;
		temp = temp->next;
		if (temp == head) {
			break;
		}
		if (checkIfEqual(temp, userField, choice)) {
			std::cout << "Удалён элемент: " << temp->data.surname << '\n';
			// переадресация
			prev->next = temp->next;
			delete temp;
			return;
		}
	}
	std::cout << "Элемент не найден.\n";
}

//Запрос удаления элемента в списке у пользователем
void case2(Employee*& head)
{
	if (head != nullptr)
	{
		Employee* current{ head }, * search{ head };
		int num{};
		std::cout << "По какому полю провести удаление?" << '\n';
		std::cout << "1. По фамилии\n2. По имени\n3. По отчеству\n4. По возрасту\n5. По семейному положению" << '\n';
		std::cin >> num;
		std::string userField{};
		switch (num)
		{
		case 1:
			std::cout << "Введите фамилию: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		case 2:
			std::cout << "Введите имя: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		case 3:
			std::cout << "Введите отчество: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;

		case 4:
			std::cout << "Введите возраст: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		case 5:
			std::cout << "Введите семейное положение: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
}
	
//Запрос печати списка у пользователем
void case3(const Employee* head)
{
	PrintList(head);
}

//Основная функция и пользовательская - запрос сброса значений элементов в списке у пользователем
void case4(Employee* head)
{
	if (head != nullptr)
	{
		Employee* tail{ head };
		std::cout << "Вы уверены?" << '\n' <<
			"Да - 1" << '\n' <<
			"Нет - 2" << '\n';
		while (true)
		{
			char sm;
			std::cin >> sm;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (sm == '1')
			{
				do {
					tail->data.surname = DEFAULT_EMPLOYEE.def_surname;
					tail->data.name = DEFAULT_EMPLOYEE.def_name;
					tail->data.middlename = DEFAULT_EMPLOYEE.def_middlename;
					tail->data.age = DEFAULT_EMPLOYEE.def_age;
					tail->data.maritalstatus = DEFAULT_EMPLOYEE.def_maritalstatus;
					tail = tail->next;
				} while (tail != head);
				std::cout << "Список был обновлен: все значения элементов сброшены." << '\n';
				break;
			}
			else if (sm == '2')
			{
				break;
			}
			else
			{
				std::cout << "Ошибка ввода. Введите 1 или 2: \n";
			}
		}
	}
	else
	{
		std::cerr << "Список пуст, данное действие не может быть выполнено." << '\n';
	}
}