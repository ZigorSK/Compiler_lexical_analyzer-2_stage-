#include "scaner.h"

Scaner::Scaner()
{
	string str;

	//Чтение ключевых слов 
	try
	{
		ifstream in_KW;
		in_KW.open("keywords.txt", ios::in);

		if (!in_KW.is_open())
			throw in_KW;

		while (!in_KW.eof())
		{
			in_KW >> str;
			if (!str.empty())
				KW_vector.push_back(str);
			
		}
		in_KW.close();
	}
	catch (ifstream &i)
	{
		cout << "Ошибка Открытия файла Keyword" << endl;
		system("pause");
		system("cls");
	}
	
	//Чтение разделителей
	try
	{
		ifstream in_DIVIDER;
		in_DIVIDER.open("dividers.txt", ios::in);

		if (!in_DIVIDER.is_open())
			throw in_DIVIDER;

		while (!in_DIVIDER.eof())
		{
			in_DIVIDER >> str;
			if (!str.empty())
				DIVIDER_vector.push_back(str);

		}

		in_DIVIDER.close();
	}
	catch (ifstream &i)
	{
		cout << "Ошибка Открытия файла divider" << endl;
		system("pause");
		system("cls");
	}

	for (int i = 0; i < KW_vector.size(); i++)
		cout << KW_vector[i]<<endl;

	system("pause");
}

bool Scaner::try_KW(string & A)
{


	return false;
}
