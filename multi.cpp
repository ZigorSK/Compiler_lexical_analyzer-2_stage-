#include "multi.h"

Base_NeTerminal * multi::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	//<multi> ::= <primary><MULTI>
	//<primary>
	Base_NeTerminal *myprimary = new primary(_now_lex, _All_table, this, "primary");

	if (*myprimary->derivation(_now_lex, _All_table, _My_check) == true)//���� ����������� ������� ����������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(myprimary);//������ ��� ������� ��������, ��������� ���, ��� ������ ������� ����
	}
	else
	{
		delete  myprimary;
	}

	//<multi> ::= <primary><MULTI>
	//<MULTI>
	Base_NeTerminal *myMULTI = new MULTI(_now_lex, _All_table, this, "MULTI");

	if (*myMULTI->derivation(_now_lex, _All_table, _My_check) == true)//���� ����������� ������� ����������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(myMULTI);//������ ��� ������� ��������, ��������� ���, ��� ������ ������� ����
	}
	else
	{
		delete myMULTI;
	}

	return this;
}
