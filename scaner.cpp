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
	
	//������� �������� ��������� � ��������� ������ ������ ��������

	do {
		if ((c1 == ' ') || (c1 == '\t') || (c1 == '\n'))
		{
			//flag = false;
			if (!in_main.eof())
				c1 = in_main.get();//��������� ������� char
		}
		else
		{
			break;
		}
	} while (!in_main.eof());
		
	if (keeper_last_char =='\0')
	{
		if (!in_main.eof())
			c1 = in_main.get();//��������� ������� char
	}
	
	if (!in_main.eof())
		c2 = in_main.get();//��������� ������� char
	


	while (!in_main.eof())
	{
		//c2 = in_main.get();//��������� ������� char


		//������ ����������, ���� �������� �1 =/ �2 =/ ��� �1 =/ �2 = *
		if (delete_coment(c1, c2))//������� �����������
		{
			flag = true;
			//������� �������� ��������� � ��������� ������ ������ �������� ����� �������� �����������
			while(!in_main.eof())
			{
				if (!in_main.eof())
					c1 = in_main.get();;
				if ((c1 == ' ') || (c1 == '\t') || (c1 == '\n'))
				{
					flag = false;
					if (!in_main.eof())
						c1 = in_main.get();//��������� ������� char
				}
				else
				{
					break;
				}
			} 
			if (!in_main.eof())
				c2 = in_main.get();//��������� ������� char2
		}

		//��������� �������
		bufer += c1;
		t_str = c2;
		//���� �1 ����������� ��� �2 ����������� ��� ������ ������������ ��� ������� ������ �������� �������
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

	bufer.clear();//��� ����������� ������ ������ - �������� ���������
	return bufer;
}

bool Scaner::delete_coment(char c1, char c2)
{
	if (c1 == '/')
	{
		if (c2 == '/')//������������ ����������
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
			if (c2 == '*')//������������� ����������
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
