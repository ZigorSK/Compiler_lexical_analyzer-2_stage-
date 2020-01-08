#include "idSeq.h"

Base_NeTerminal * idSeq::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{

	//< idSeq > :: = <id> 

	Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

	if (*myid->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
	{
		add(myid);
	}
	else
	{
		delete myid;
		_flag_choice = false;
		return this;
	}

	Token lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];//��������� ��������, ���� '='
	// <id>=<Const> 
	if (lexem.get_name() == "=")
	{
		//��������� ���� - �������� '='
		Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//�������� ������ ��� ����� ��������
		add(child);//��������� ������

		_MyVectorOp->push_back(child);//��������� = ��� ���������

		(*_now_lex)++;

		Base_NeTerminal *  myConst = new Const(_now_lex, _All_table, this, "Const");

		if (*myConst->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
		{
			add(myConst);
		}
		else
		{
			delete myConst;
			_flag_choice = false;
			cout << "��������� ���������!";
			return this;
		}

		lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//��������� ��������, ���� ',', �� �.�. ��� id(�������, �.�. ������ ��������� ���� ���������)))))
	}
	
	if (lexem.get_name() == ",")//< idSeq > :: = <id>, <idSeq>
	{
		//��������� ���� - �������� ','
		Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//�������� ������ ��� ����� ��������
		add(child);//��������� ������
		(*_now_lex)++;

		//<idSeq>
		Base_NeTerminal *  myidSeq = new idSeq(_now_lex, _All_table, this, "idSeq");
		if (*myidSeq->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
		{
			add(myidSeq);
		}
		else
		{
			delete myidSeq;
			_flag_choice = false;
		}
	}

	
	return this;
}
