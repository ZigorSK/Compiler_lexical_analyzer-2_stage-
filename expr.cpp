#include "expr.h"

Base_NeTerminal * expr::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	//<expr> ::= <id>=<add>
	Token lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)+1];//������� ��������

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "="))
	{
		_My_check->get_MyCheck().clear();//������� ������


		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//
		Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

		if (*myid->derivation(_now_lex, _All_table, _My_check) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
		{
			add(myid);//
		}
		else
		{
			delete myid;//
			cout << "��������� �������������" << endl;
			Error(_All_table->get_stream_of_token().get_table()[*(_now_lex)], this);
		}
		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];

		//=
		try
		{
			if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "="))//������ �� ��, ������ ����� ���������
			{
				Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "=");//�������� ������ ��� ���� ���������
				add(child);//��������� ������
				_My_check->push_back(child);//��������� �������� = 
				(*_now_lex)++;
			}
			else
			{
				throw lexem;
			}
		}
		catch (Token err)
		{
			cout << "��������� =" << endl;
			Error obg(err, this);
		}


		//<Add>
		Base_NeTerminal *myadd = new Add(_now_lex, _All_table, this, "Add");

		if (*myadd->derivation(_now_lex, _All_table, _My_check) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
		{
			add(myadd);
		}
		else
		{
			delete myadd;//������ ��������� � ��������� �������, ���� ��� �����
		}

		//������������� ���� ����� ������ id = id*const +id � �� 
		//���� �� � string = char + char + char..
		//char = char 
		// int = length(��� int, ��������� ��������� � print ��� void );
		//
		string t1;
		string t2;
		if (_My_check->get_MyCheck().back()->get_name() == "Const")//���������
		{
			t1 = _All_table->get_table_of_constant().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_const_type();
		}

		if (_My_check->get_MyCheck().back()->get_name() == "id")//Id
		{
			t1 = _All_table->get_table_of_identifier().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_id_type();
		}
		_My_check->get_MyCheck().pop_back();//������� ��������� �������

		while (_My_check->get_MyCheck().back()->get_name() != "=")
		{
			if ((_My_check->get_MyCheck().back()->get_name() == "Const") || ((_My_check->get_MyCheck().back()->get_name() == "id")))
			{
				if (_My_check->get_MyCheck().back()->get_name() == "Const")//���������
				{
					t2 = _All_table->get_table_of_constant().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_const_type();
				}

				if (_My_check->get_MyCheck().back()->get_name() == "id")//Id
				{
					t2 = _All_table->get_table_of_identifier().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_id_type();
				}
				_My_check->get_MyCheck().pop_back();//������� ��������� �������


				if (t1 != t2)
				{
					//error
					cout << "�������������� ���� " << t1 << " ���� " << t2 << endl;
					system("pause");
					exit(0);
				}

				t1 = t2;
			}
			else
			{
				_My_check->get_MyCheck().pop_back();//������� ��������� �������
			}
		}
		_My_check->get_MyCheck().pop_back();//������� ��������� �������
		bool MyFlag = false;
		t2 = _All_table->get_table_of_identifier().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_id_type();
		//� t2 �������� ������ ������� ������������ � t1 �����
		if ((t2 == "string") && (t1 == "char"))//�� ��
		{
			MyFlag = true;
		}
		if (t1 == t2)//�� ��
		{
			MyFlag = true;
		}
		if (MyFlag == false)
		{
			//error
			cout << "�������������� ���� " << t1 << " ���� " << t2 << endl;
			system("pause");
			exit(0);
		}
		//
		return this;
	}
	else
	{
		_flag_choice = false;
		return this;
	}
}
