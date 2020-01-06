#include "varDefine.h"


Base_NeTerminal * varDefine::derivation(int * now_lex, Scaner * table)
{

	//<varDefine> ::= <type><idSeq>;
	//<type>
	Base_NeTerminal *myType = new type(_now_lex, _All_table, this, "type");

	if (*myType->derivation(_now_lex, _All_table) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(myType);
	}
	else
	{
		_flag_choice = false;
		delete myType;
		return this;//������ ������� varDefine �� �������� ��� progBlock
	}

	//<varDefine> ::= <type><idSeq>;
	//<idSeq>

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


	//<varDefine> ::= <type><idSeq>;
	//;
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//������� ��������

	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ";"))//������ �� ��, ������ ����� ���������
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, ";");//�������� ������ ��� ����� ��������
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
	
	return this;
}

