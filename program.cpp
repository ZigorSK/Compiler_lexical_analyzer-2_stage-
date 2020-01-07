#include "program.h"

Base_NeTerminal * program::getSyntaxTree()
{
	return nullptr;
}

Base_NeTerminal * program::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//������� ��������
	//<program> ::= main();{<progBlock>}^

	//main
	try
	{
		if ((lexem.get_type() == KEYWORD) && (lexem.get_name() == "main"))//������ �� ��, ������ ����� ���������
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "main");//�������� ������ ��� ���� ���������
			add(child);//��������� ������
			(*_now_lex)++;//��������� �������
		}
		else
		{
			throw lexem;//������
		}
	}
	catch (Token err)
	{
		cout << "��������� main" << endl;
		Error obg( err, this );
	}

	lexem = _All_table->get_stream_of_token().get_table()[*_now_lex];
	//<program> ::= main();{<progBlock>}^
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

	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//)
	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ")"))//������ �� ��, ������ ����� ���������
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, ")");//�������� ������ ��� ���� ���������
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

	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//;
	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ";"))//������ �� ��, ������ ����� ���������
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, ";");//�������� ������ ��� ���� ���������
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
		cout << "��������� ;" << endl;
		Error obg(err, this);
	}

	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//{
	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "{"))//������ �� ��, ������ ����� ���������
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, "{");//�������� ������ ��� ���� ���������
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
		cout << "��������� {" << endl;
		Error obg(err, this);
	}

	//<program> ::= main();{<progBlock>}^
	//<progBlock>

	Base_NeTerminal *  prBlock = new progBlock(_now_lex, _All_table, this, "progBlock");
	if (*prBlock->derivation(_now_lex, _All_table, _My_check) == true)//���� ��� ����������� ������� ����������, �� �� ��)
		//����� ���������� ������������ ������. ���������� �� �������� ������ ���������
	{
		add(prBlock);
	}
	else
	{
		delete prBlock;//������ � ���� main �����
	}

	//
	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//}
	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "}"))//������ �� ��, ������ ����� ���������
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, "}");//�������� ������ ��� ����� ���� ���������
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
		cout << "��������� }" << endl;
		Error obg(err, this);
	}

	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//End_of_file

	if ((lexem.get_type() == END_OF_programM) && (lexem.get_name() == ""))//������ �� ��
	{
		return this;
	}
	else
	{
		cout << "��������� ����� ���������" << endl;
		Error(lexem, this);
		
	}
	return this;
}

