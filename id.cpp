#include "id.h"

Base_NeTerminal * id::derivation(int * now_lex, Scaner * table)
{
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//������� ��������

	
	//id
	try
	{
		if (lexem.get_type() == IDENTIFIER)//������ �� ��, ������ ����� ���������
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, "id");//�������� ������ ��� ����� ��������
			add(child);//��������� ������
			(*_now_lex)++;
		}
		else
		{
			throw lexem;
		}
	}
	catch (Token err)
	{
		return nullptr;
	}

	return this;
}
