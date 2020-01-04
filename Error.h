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
		while (node = node->get_parent())
		{ }
		delete node;//Очищаем дерево
		cout << "Встречена лексема, нарушающая синтаксис: " << err.get_name() << ", тип: " << err.get_type() << endl;
		cout << "Выполнение компиляции прекращается." << endl;
		system("pause");
		exit(0);
	};
};