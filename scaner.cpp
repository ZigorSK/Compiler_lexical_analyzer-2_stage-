#include "scaner.h"

Scaner::Scaner()
{
	string str;

	in_main.open("keywords.txt", ios::in);

	if (!in_main.is_open())
	{
		cout << "Error opening file main.txt" << endl;
		system("pause");
		system("cls");
	}
	
}

Scaner::~Scaner()
{
	in_main.close();
}

string Scaner::get_lex()
{
	//Написать удаление коментариев, если встречен // Или /*
	//Написать удаление лексемы
	
	return string();
}
