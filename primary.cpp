#include "primary.h"

Base_NeTerminal * primary::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//������� ��������

	//<primary> ::= (<Add>) |<id> | <const> |<funcCall>
	//(

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "("))//������ �� ��, ������ ����� ���������
	{
		//(<Add>)
		//(
		Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "(");//�������� ������ ��� ���� ���������
		add(child);//��������� ������
		_MyVectorOp->push_back(child);
		(*_now_lex)++;
		
		//<Add>
		Base_NeTerminal *myadd = new Add(_now_lex, _All_table, this, "Add");

		if (*myadd->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
		{
			add(myadd);
		}
		else
		{
			delete myadd;//������ ��������� � ��������� �������, ���� ��� �����
		}

		//
		lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//������� ��������
		//)
		try
		{
			if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ")"))//������ �� ��, ������ ����� ���������
			{
				Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, ")");//�������� ������ ��� ���� ���������
				add(child);//��������� ������
				_MyVectorOp->push_back(child);
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

	}
	else
	{
		//funcCall

		Base_NeTerminal *  myFuncCall = new funcCall(_now_lex, _All_table, this, "funcCall");

		if (*myFuncCall->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)
		{
			add(myFuncCall);
		}
		else
		{
			delete myFuncCall;

			Base_NeTerminal *myConst = new Const(_now_lex, _All_table, this, "Const");

			if (*myConst->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
			{
				add(myConst);
			}
			else
			{
				delete myConst;
				//id
				Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

				if (*myid->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
				{
					add(myid);
				}
				else
				{
					delete myid;
					_flag_choice = false;
					//������
					cout << "��������� ������������� ��� ���������" << endl;
					Error(lexem, this);
				}
			}
		}
	}
	return this;
}
