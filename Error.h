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
		while (ptr = node)//������� ������ � ��� �������� ����
		{
			node = node->get_parent();
			delete ptr;
		}
		cout << "��������� �������, ���������� ��������� " << err.get_name() << ", ���: " << err.get_type() << endl;
		cout << "���������� ���������� ������������." << endl;
		system("pause");
		exit(0);
	};
};