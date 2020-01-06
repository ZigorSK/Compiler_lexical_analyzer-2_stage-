#include "funcCall.h"

Base_NeTerminal * funcCall::derivation(int * now_lex, Scaner * table)
{
	//<funcCall> ::= <id>(<idSeq>)
	Token lexem = _All_table->get_stream_of_token().get_table()[*_now_lex + 1];//������� ��������

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "("))
	{
		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//id
		Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

		if (*myid->derivation(_now_lex, _All_table) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
		{
			add(myid);
		}
		else
		{
			delete myid;//
			cout << "��������� �������������" << endl;
			Error(_All_table->get_stream_of_token().get_table()[*(_now_lex)], this);
		}

		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//(
		try
		{
			if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "("))//������ �� ��, ������ ����� ���������
			{
				Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "(");//�������� ������ ��� ���� ���������
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
			cout << "��������� (" << endl;
			Error obg(err, this);
		}

		//idSeq
		Base_NeTerminal *myidSeq = new idSeq(_now_lex, _All_table, this, "idSeq");
		if (*myidSeq->derivation(_now_lex, _All_table) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
		{
			add(myidSeq);
		}
		else
		{
			delete myidSeq;//
			cout << "��������� �������������" << endl;
			Error(_All_table->get_stream_of_token().get_table()[*(_now_lex)], this);
		}

		//
		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//)

		try
		{
			if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ")"))//������ �� ��, ������ ����� ���������
			{
				Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, ")");//�������� ������ ��� ���� ���������
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
			cout << "��������� )" << endl;
			Error obg(err, this);
		}

		return this;
	}
	else
	{
		_flag_choice = false;
		return this;
	}
}
