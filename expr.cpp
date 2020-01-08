#include "expr.h"

Base_NeTerminal * expr::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	_My_check->get_MyCheck().clear();
	_MyVectorOp->get_VectorOfOP().clear();
	//<expr> ::= <id>=<add>
	Token lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)+1];//������� ��������

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "="))
	{
		_My_check->get_MyCheck().clear();//������� ������


		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//
		Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

		if (*myid->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
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
				_MyVectorOp->push_back(child);
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

		if (*myadd->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
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
		_My_check->get_MyCheck().clear();


		//���������
		int num = _MyVectorOp->get_VectorOfOP()[0]->get_num_inTdTable();
		Identifier & itId = _All_table->get_table_of_identifier()[num];
		_MyVectorOp->get_VectorOfOP().erase(_MyVectorOp->get_VectorOfOP().begin());//id 
		_MyVectorOp->get_VectorOfOP().erase(_MyVectorOp->get_VectorOfOP().begin());// = 

		if(itId.get_id_type() == "string")//��� ������ ������� char ��
		{ 
			string str = itId.get_value();

			while (_MyVectorOp->get_VectorOfOP().size() != 0)
			{
				if (_MyVectorOp->get_VectorOfOP().front()->get_name() == "id")//Id
				{
					str += _All_table->get_table_of_identifier().get_table()[_MyVectorOp->get_VectorOfOP().front()->get_num_inTdTable()].get_value();
				}
				else
				{
					
					if (_MyVectorOp->get_VectorOfOP().front()->get_name() != "+")
					{
						cout << "��� ����� ��������� ������ �������� +" << endl;
						system("pause");
						exit(0);
					}
				}
				_MyVectorOp->get_VectorOfOP().erase(_MyVectorOp->get_VectorOfOP().begin());
			}
			itId.set_value(str);

		}
		else//��� int
		{
			//�������� �� �������������
			string& str = convert_to_OPW(_MyVectorOp);
			itId.set_value(str);
		}

		_MyVectorOp->get_VectorOfOP().clear();
		return this;
	}
	else
	{
		_flag_choice = false;
		return this;
	}
}

string & expr::convert_to_OPW(VectorOfOP * _MyVectorOp)
{
	vector <string> Vect;
	vector<string> OPN;
	stack<string> MyStack;
	static string value;
	value.clear();

	for (auto i : _MyVectorOp->get_VectorOfOP())
	{
		if (i->get_name() == "Const")//���������
		{
			Vect.push_back( _All_table->get_table_of_constant().get_table()[i->get_num_inTdTable()].get_name());
		}
		else
		{
			if (i->get_name() == "id")//Id
			{
				Vect.push_back(_All_table->get_table_of_identifier().get_table()[i->get_num_inTdTable()].get_value());
				if (Vect.back() == "")
				{
					cout << "������������� "<< _All_table->get_table_of_identifier().get_table()[i->get_num_inTdTable()].get_name() <<" �� ���������������!!!" << endl;
					system("pause");
					exit(0);
				}
			}
			else
			{
				Vect.push_back(i->get_name());
			}
		}
	}

	if (Vect.size() == 1)
		return value = Vect.back();
		
	//�������� ������ �� ����������
	//�������������� � ���
	for (auto i : Vect)
	{
		int pr = prior(i);

		if (i == ")")
		{
			while (MyStack.top() != "(")
			{
				OPN.push_back(MyStack.top());
				MyStack.pop();
			}
			MyStack.pop();

			continue;
		}

		if (pr == 0)
		{
			OPN.push_back(i);//���� �������, �������� � ��� ������
			continue;
		}


		if (i == "(")
		{
			MyStack.push(i);
			continue;
		}


		while (!(MyStack.empty()))
		{
			if (!(pr >= prior(MyStack.top())))
				break;
			OPN.push_back(MyStack.top());
			MyStack.pop();
		}
		MyStack.push(i);
	}
	while (!MyStack.empty())
	{
		OPN.push_back(MyStack.top());
		MyStack.pop();
	}

	//����� ��������� � �������� �������� ������
	//��������� ���
	int count = 0;

	for (int i = 0; i< OPN.size(); i++)
	{
		if (prior(OPN[i]) == 0)//������ ��� �� ��������
		{
			MyStack.push(OPN[i]);
		}
		else
		{
			//���������
			string op1, op2;
			op2 = MyStack.top();
			MyStack.pop();
			op1 = MyStack.top();
			MyStack.pop();

			string rezult = calcul(op1, op2, OPN[i]);//str 1 opn[1] str2 
			MyStack.push(rezult);
		}
	}

	//
	value = MyStack.top();
	return value;
}

string & expr::calcul(string op1, string op2, string oper)//str 1 opn[1] str2 
{
	static string result;
	int OP1 = atoi(op1.c_str()), OP2 = atoi(op2.c_str()), RESULT = 0;
	

	if (oper == "+")
	{
		RESULT = OP1 + OP2;
	}
	if (oper == "-")
	{
		RESULT = OP1 - OP2;
	}
	if (oper == "*")
	{
		RESULT = OP1 * OP2;
	}
	if (oper == "/")
	{
		RESULT = OP1 / OP2;
	}
	//����� � ������
	result = to_string(RESULT);
	return result;
}
