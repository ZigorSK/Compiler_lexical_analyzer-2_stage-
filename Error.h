#pragma once
#include"scaner.h"
#include"AllStruct.h"

class Base_NeTerminal;
class Token;

class Error
{
	Error() = delete;
public:
	Error(Token &err, Base_NeTerminal * node)
	{
		Base_NeTerminal *ptr = node;
		while (ptr = node)//Очищаем дерево и все созданые узлы
		{
			node = node->get_parent();
			delete ptr;
		}
		cout << "Встречена лексема, нарушающая граматику " << err.get_name() << ", тип: " << err.get_type() << endl;
		cout << "Выполнение компиляции прекращается." << endl;
		system("pause");
		exit(0);
	};
};