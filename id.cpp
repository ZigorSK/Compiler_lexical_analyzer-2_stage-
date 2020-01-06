#include "id.h"

Base_NeTerminal * id::derivation(int * now_lex, Scaner * table)
{
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//������� ��������

	//id
	if (lexem.get_type() == IDENTIFIER)//������ �� ��, ������ ����� ���������
	{
		Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//�������� ������ ��� ����� ��������
		add(child);//��������� ������
		(*_now_lex)++;
	}
	else
	{
		_flag_choice = false;
	}

	return this;
}
