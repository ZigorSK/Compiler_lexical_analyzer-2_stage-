#include "progBlock.h"

Base_NeTerminal * progBlock::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	//<progBlock> :: = <varDefine><progBlock> | <operBlock><progBlock>| e
	//<varDefine>
	Base_NeTerminal *myVarDefine = new varDefine(_now_lex, _All_table, this, "varDefine");

	if (*myVarDefine->derivation(_now_lex, _All_table, _My_check) == true)//���� ����������� ������� ����������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(myVarDefine);//������ ��� ������� ��������, ��������� ���, ��� ������ ������� ����
	}
	else
	{
		delete  myVarDefine;//���� �� ���������� �������� �������, �� ������������� ���������

		//<operBlock>
		Base_NeTerminal *  myOperBlock = new operBlock(_now_lex, _All_table, this, "operBlock");

		if (*myOperBlock->derivation(_now_lex, _All_table, _My_check) == true)
		{
			add(myOperBlock);
		}
		else
		{
			_flag_choice = false;
			delete myOperBlock;//������ ������ ������
			return this;
		}
	}

	//���� ��� <varDefine>|<operBlock>, �� ������ <progBlock>
	//<progBlock>

	Base_NeTerminal *  myProgBlock = new progBlock(_now_lex, _All_table, this, "progBlock");

	if (*myProgBlock->derivation(_now_lex, _All_table, _My_check) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(myProgBlock);
	}
	else
	{
		delete myProgBlock;//������ ������������� � ������ ������
	}

	return this;
}
