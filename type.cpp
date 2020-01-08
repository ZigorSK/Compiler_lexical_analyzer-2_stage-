#include "type.h"

Base_NeTerminal * type::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//������� ��������

	//<type> :: = char | int | float | double | string
	//

		if (((lexem.get_type() == KEYWORD) && (lexem.get_name() == "char"))||
			((lexem.get_type() == KEYWORD) && (lexem.get_name() == "int")) ||
			((lexem.get_type() == KEYWORD) && (lexem.get_name() == "float"))||
			((lexem.get_type() == KEYWORD) && (lexem.get_name() == "double"))||
			((lexem.get_type() == KEYWORD) && (lexem.get_name() == "string")))//������ �� ��, ������ ���� - ����� ���������
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//�������� ������ ��� ����� ��������
			add(child);//��������� ������

			_My_check->push_back(this);//��������� ��������� �� ����� type � ������

			(*_now_lex)++;
		}
		else
		{
			_flag_choice = false;
		}

	return this;
}
