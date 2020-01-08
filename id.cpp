#include "id.h"

Base_NeTerminal * id::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{

	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//������� ��������

	//id
	if (lexem.get_type() == IDENTIFIER)//������ �� ��, ������ ����� ���������
	{
		Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//�������� ������ ��� ����� ��������
		add(child);//��������� ������

		//���������� ����� � ������� ID (��������� ������)
		_num_in_IdTable = _All_table->get_table_of_identifier().finde_num(lexem.get_name());//����� ������� ID � �������
		_My_check->push_back(this);//��������� ��������� �� ID � ������
		_MyVectorOp->push_back(this);//��������� � ������ id ��� ��������� 
		//
		(*_now_lex)++;
	}
	else
	{
		_flag_choice = false;
	}

	return this;
}
