#include "scaner.h"

Scaner::Scaner()
{
	keeper_last_char = '\0';

	in_main.open("main.txt", ios::in);

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
	string bufer, t_str;
	char c1, c2;
	bool flag = true;
	c1 = keeper_last_char;
	
	//Пропуск пробелов табуляций и переносов строки преред лексемой

	do {
		if ((c1 == ' ') || (c1 == '\t') || (c1 == '\n'))
		{
			//flag = false;
			if (!in_main.eof())
				c1 = in_main.get();//Получение символа char
		}
		else
		{
			break;
		}
	} while (!in_main.eof());
		
	if (keeper_last_char =='\0')
	{
		if (!in_main.eof())
			c1 = in_main.get();//Получение символа char
	}
	
	if (!in_main.eof())
		c2 = in_main.get();//Получение символа char
	


	while (!in_main.eof())
	{
		//c2 = in_main.get();//Получение символа char


		//Начало коментария, если встречен с1 =/ с2 =/ Или с1 =/ с2 = *
		if (delete_coment(c1, c2))//Пропуск коментариев
		{
			flag = true;
			//Пропуск пробелов табуляций и переносов строки преред лексемой после пропуска коментариев
			while(!in_main.eof())
			{
				if (!in_main.eof())
					c1 = in_main.get();;
				if ((c1 == ' ') || (c1 == '\t') || (c1 == '\n'))
				{
					flag = false;
					if (!in_main.eof())
						c1 = in_main.get();//Получение символа char
				}
				else
				{
					break;
				}
			} 
			if (!in_main.eof())
				c2 = in_main.get();//Получение символа char2
		}

		//получение лексемы
		bufer += c1;
		t_str = c2;
		//Если с1 разделитель или с2 разделитель или пробел илитабуляция или перенос строки получить лексему
		if (table_of_dividers == bufer)//
		{
			keeper_last_char = c2;
			return bufer;
		}
		if ((table_of_dividers == t_str) || (c2 == ' ') || (c2 == '\t') || (c2 == '\n'))
		{
			keeper_last_char = c2;
			return bufer;
		}

		c1 = c2;

		if (!in_main.eof())
			c2 = in_main.get();
	} 

	bufer.clear();//При возвращении пустой строки - конечное состояние
	return bufer;
}

bool Scaner::delete_coment(char c1, char c2)
{
	if (c1 == '/')
	{
		if (c2 == '/')//Однострочный коментарий
		{
			char c1;
			do { 
				if (!in_main.eof())
					c1 = in_main.get();
			} while (c1 != '\n');
			return true;
			
		}
		else
		{
			if (c2 == '*')//многострочный коментарий
			{
				while (!in_main.eof())
				{
					if (!in_main.eof())
						c1 = in_main.get();
					if (c1 == '*')
					{
						if (in_main.eof())
							return false;
						if (!in_main.eof())
							c2 = in_main.get();
						
						if (c2 == '/')
							return true;
					
					}
				}
			}
		}
	}
	return false;
}
