#include <iostream>
#include "myfuncs.h"
#include "constants.h"

int main()
{

	setlocale(LC_ALL, "Rus");
	std::system("chcp 1251 > nul");
	Employee* head_ptr{ nullptr };
	if (LoadingList(DEFAULT_NAME_IN_OUT, head_ptr))
	{
		std::cout << "Список загружен . . ." << '\n' << '\n';
		bool cycle{ true };
		while (cycle) {
			switch (getCase())
			{
			case '1':
				std::cout << '\n';
				case1(head_ptr);
				std::cout << '\n';
				break;
			case '2':
				std::cout << '\n';
				case2(head_ptr);
				std::cout << '\n';
				break;
			case '3':
				std::cout << '\n';
				case3(head_ptr);
				std::cout << '\n';
				break;
			case '4':
				std::cout << '\n';
				case4(head_ptr);
				std::cout << '\n';
				break;
			case '5':
				std::cout << '\n';
				cycle = false;
			}
		}
		if (UnloadingList(DEFAULT_NAME_IN_OUT, head_ptr))
		{
			std::cout << '\n' << "Список выгружен и удалён из оперативной памяти . . ." << '\n';
			std::system("chcp 866 > nul");
		}
	}
	return 0;
}
   