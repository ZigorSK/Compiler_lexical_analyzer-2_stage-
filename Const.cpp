#include "Const.h"

Base_NeTerminal * Const::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//������� ��������

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "'"))//���������� ���������
	{
		Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//�������� ������ ��� ����� ��������
		add(child);//��������� ������
		(*_now_lex)++;

		lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];

		if (lexem.get_type() == CONSTANT) //���������� ���������
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//�������� ������ ��� ����� ��������
			add(child);//��������� ������

			//���������� ����� � ������� ��������(��������� ������)
			_num_in_IdTable = _All_table->get_table_of_constant().finde_num(lexem.get_name());//���������� ����� � ������� ��������
			//

			(*_now_lex)++;
		}
		else
		{
			_flag_choice = false;
			cout << "��������� ���������" << endl;
			Error obg(lexem, this);
			return this;
		}

		lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];

		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "'"))//���������� ���������
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//�������� ������ ��� ����� ��������
			add(child);//��������� ������
			(*_now_lex)++;
		}
		else
		{
			_flag_choice = false;
			cout << " ��������� '''" << endl;
			Error obg(lexem, this);
			return this;
		}
	}
	else//�������� ���������
	{
		if (lexem.get_type() == CONSTANT) 
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//�������� ������ ��� ����� ��������
			add(child);//��������� ������
			//
			_num_in_IdTable = _All_table->get_table_of_constant().finde_num(lexem.get_name());//���������� ����� � ������� ��������
			//
			(*_now_lex)++;
		}
		else
		{
			_flag_choice = false;
			return this;
		}
	}
	if( _My_check->get_MyCheck().front()->get_name() != "type")
		_My_check->push_back(this);//��������� ��������� �� ��������� � ������
	return this;
}

