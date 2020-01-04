#include "progBlock.h"

Base_NeTerminal * progBlock::derivation(int * now_lex, Scaner * table)
{
	//<progBlock> :: = <varDefine><progBlock> | <operBlock><progBlock> | <func><progBlock> | e
	//<varDefine>
	Base_NeTerminal *myVarDefine = new varDefine(_now_lex, _All_table, this, "varDefine");

	if (*myVarDefine->derivation(_now_lex, _All_table) == true)//���� ����������� ������� ����������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(myVarDefine);//������ ��� ������� ��������, ��������� ���, ��� ������ ������� ����
	}
	else
	{
		delete  myVarDefine;//���� �� ���������� �������� �������, �� ������������� ���������

		//<operBlock>
		Base_NeTerminal *  myOperBlock = new operBlock(_now_lex, _All_table, this, "operBlock");

		if (*myOperBlock->derivation(_now_lex, _All_table) == true)
		{
			add(myOperBlock);
		}
		else
		{
			delete myOperBlock;//
			//���� �� ���������� �������� �������, �� ������������� ���������
			
			//<func>
			Base_NeTerminal *  myFunc = new func(_now_lex, _All_table, this, "func");

			if (*myFunc->derivation(_now_lex, _All_table) == true)
			{
				add(myFunc);
			}
			else
			{
				_flag_choice = false;
				delete  myFunc;//������ ������ ������
				return this;
			}
		}
	}

	//���� ��� <varDefine>|<operBlock>|<func>, �� ������ <progBlock>
	//<progBlock>

	Base_NeTerminal *  myProgBlock = new progBlock(_now_lex, _All_table, this, "progBlock");

	if (*myProgBlock->derivation(_now_lex, _All_table) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(myProgBlock);
	}
	else
	{
		delete myProgBlock;//������ ������������� � ������ ������
	}

	return this;
}
