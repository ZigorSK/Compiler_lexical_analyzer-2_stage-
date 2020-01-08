#include "Add.h"

Base_NeTerminal * Add::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	//<Add> ::= <multi><ADD>
	//<multi>
	Base_NeTerminal *mymulti = new multi(_now_lex, _All_table, this, "multi");

	if (*mymulti->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ����������� ������� ����������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(mymulti);//������ ��� ������� ��������, ��������� ���, ��� ������ ������� ����
	}
	else
	{
		delete  mymulti;
	}

	//<Add> ::= <multi><Add>
	//<ADD>
	Base_NeTerminal *myADD = new ADD(_now_lex, _All_table, this, "ADD");

	if (*myADD->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ����������� ������� ����������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(myADD);//������ ��� ������� ��������, ��������� ���, ��� ������ ������� ����
	}
	else
	{
		delete  myADD;
	}
	return this;
}
