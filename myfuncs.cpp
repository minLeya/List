#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "mystructs.h"
#include "myfuncs.h"
#include "ArrayNineStrings.h"
#include "constants.h"


//�������� �������
//����� ������ �� ����� � ������������ ������
bool LoadingList(const std::string fileName, Employee*& head)
{
	std::ifstream out_DataFile(fileName);
	if (!out_DataFile)
	{
		std::cerr << "�� ������� ������� ����!" << '\n';
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

//����� ������ �� ������������� ������ � ����
bool UnloadingList(const std::string fileName, Employee* head)
{
	Employee* tail{ head };
	std::ofstream in_DataFile(fileName);
	if (!in_DataFile)
	{
		std::cerr << "�� ������� ������� ����!" << '\n';
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
				std::cout << "������ � �������� " << clean_ptr->data.surname << ",... ��������� � ������� �� ����������� ������." << '\n';
				delete clean_ptr;
				if (tail == head)
					break;
			}
		}

		in_DataFile.close();
		return true;
	}
}

//��� case1 - ���������� ��������� ������������� ������
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

//��� case3 - ������ ������ �� �������
void PrintList(const Employee* head)
{
	const Employee* tail{ head };
	if (head != nullptr)
	{
		int index_number{};
		std::cout << "\t\t��� ������:" << '\n';
		do {
			index_number++;
			std::cout << index_number << ") " << tail->data.surname << ";" << tail->data.name << ";" << tail->data.middlename << ";" << tail->data.age << ";" << tail->data.maritalstatus << '\n';
			tail = tail->next;
		} while (tail != head);
	}
	else
	{
		std::cout << "������ ����." << '\n';
	}
}


//��������������� �������
//���������� ������ ������ �� ����� 
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


//��������� ������ �������� �� ��������� � ��������������� ����
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

//����������� ������ ������ � �������������� ���� �������� ������������� ������ � ������������� �� � ���������
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


//������ �������� � ������������ ������� � ������������
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
		{
			return choice[0];
		}
		else
		{
			std::cout << '\n' << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 5). ��������� ����:" << '\n';
		}
	}
}

////��������� ������ �������� � ������������ (��� ��������)
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
//			std::cout << "������ �����, �� ����� �� �����. ��������� ����:\n";
//		}
//		else if (num != static_cast<int>(num))
//		{
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			std::cout << "�� ����� �� ����������� �����. ��������� ����:\n ";
//		}
//		else
//		{
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			return num;
//		}
//	}
//}


//���������������� �������
//���������������� ����
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << '\n' <<
		"1) ���������� ����� ��������� ������." << '\n' <<
		"2) ������� �������� ������� �� ������ �� ����." << '\n' <<
		"3) ������ ���� ��������� (����� �� �������)." << '\n' <<
		"4) ����� �������� ���� ��������� (��� �������� ��������� ����� ��������)." << '\n' <<
		"5) �����." << '\n';
}

//������ ���������� ��������� � ������ �������������
void case1(Employee* head)
{
	unsigned length = ListLength(head);
	std::cout << "����� ������ ������ �� ������ ������: " << length << '\n';
}
//��������
//�������� ������������ ����
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
//�������� �������� �� ����
void deleteElement(Employee*& head, std::string userField, int choice)
{
	if (head == nullptr) {
		std::cout << "������ ������.";
		return;
	}
	Employee* temp{ head };
	Employee* prev{ nullptr };
	// ������� ������ ������� ���� ��������� ����
	if (checkIfEqual(head, userField, choice))
	{
		// ������� ��������� �������
		while (temp->next != head)
			temp = temp->next;

		// ������ ��������� � ���������� �������� �� ������ ������ �������
		temp->next = head->next;
		delete head;
		head = temp->next;
		return;
	}
	// ������ ���������� ������� � ���������������� ��� next � ������ �������� temp 
	while (true) {
		prev = temp;
		temp = temp->next;
		if (temp == head) {
			break;
		}
		if (checkIfEqual(temp, userField, choice)) {
			std::cout << "����� �������: " << temp->data.surname << '\n';
			// �������������
			prev->next = temp->next;
			delete temp;
			return;
		}
	}
	std::cout << "������� �� ������.\n";
}

//������ �������� �������� � ������ � �������������
void case2(Employee*& head)
{
	if (head != nullptr)
	{
		Employee* current{ head }, * search{ head };
		int num{};
		std::cout << "�� ������ ���� �������� ��������?" << '\n';
		std::cout << "1. �� �������\n2. �� �����\n3. �� ��������\n4. �� ��������\n5. �� ��������� ���������" << '\n';
		std::cin >> num;
		std::string userField{};
		switch (num)
		{
		case 1:
			std::cout << "������� �������: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		case 2:
			std::cout << "������� ���: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		case 3:
			std::cout << "������� ��������: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;

		case 4:
			std::cout << "������� �������: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		case 5:
			std::cout << "������� �������� ���������: ";
			std::cin >> userField;
			deleteElement(head, userField, num);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
}
	
//������ ������ ������ � �������������
void case3(const Employee* head)
{
	PrintList(head);
}

//�������� ������� � ���������������� - ������ ������ �������� ��������� � ������ � �������������
void case4(Employee* head)
{
	if (head != nullptr)
	{
		Employee* tail{ head };
		std::cout << "�� �������?" << '\n' <<
			"�� - 1" << '\n' <<
			"��� - 2" << '\n';
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
				std::cout << "������ ��� ��������: ��� �������� ��������� ��������." << '\n';
				break;
			}
			else if (sm == '2')
			{
				break;
			}
			else
			{
				std::cout << "������ �����. ������� 1 ��� 2: \n";
			}
		}
	}
	else
	{
		std::cerr << "������ ����, ������ �������� �� ����� ���� ���������." << '\n';
	}
}