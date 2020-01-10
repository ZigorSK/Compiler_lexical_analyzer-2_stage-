#include "funcCall.h"

Base_NeTerminal * funcCall::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	//<funcCall> ::= <id>(<idSeq>)
	Token lexem = _All_table->get_stream_of_token().get_table()[*_now_lex + 1];//������� ��������

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "("))
	{
		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//id
		Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

		if (*myid->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
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
			cout << "��������� (" << endl;
			Error obg(err, this);
		}

		//idSeq
		Base_NeTerminal *myidSeq = new idSeq(_now_lex, _All_table, this, "idSeq");
		if (*myidSeq->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
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


		//������������� ���� �������� ����������� �����.
		vector <Base_NeTerminal *>Myvector;
	
		while (_My_check->get_MyCheck().back()->get_name() != "(")
		{
			Myvector.push_back(_My_check->get_MyCheck().back());
			_My_check->get_MyCheck().pop_back();//������� ��������� �������
		}
		_My_check->get_MyCheck().pop_back();//������� ��������� �������

		Base_NeTerminal * Id_func = _My_check->get_MyCheck().back();//��� ���������(id �������)
		vector <Base_NeTerminal *> Vector_arg = Myvector;//��������� ��� ���������
		//����� ������� � Myvector ����� ������ ���������� � ��������� ������� _My_check - ��� �������
		
		int num = _My_check->get_MyCheck().back()->get_num_inTdTable();
		Identifier & itId = _All_table->get_table_of_identifier()[num];

		//�������� �������� �� ��������� �������?
		for (auto i : Myvector)
		{
			int num1 = i->get_num_inTdTable();
			Identifier & itId1 = _All_table->get_table_of_identifier()[num1];
			if (itId1.get_dec() == false)
			{
				cout << "������������� " << itId1.get_name()<<" �� �������!!!" << endl;
				system("pause");
				exit(0);
			}

		}
		//

		if (_My_check->get_MyCheck().back()->get_childs().back()->get_name() == "print")
		{
			if (Myvector.size() < 1)
			{
				cout << "� ������� print �� ����� ���� ������ 1 ���������!!!" << endl;
				system("pause");
				exit(0);
			}
			//all ok)
			string s = "void";
			itId.set_dec(true);//������ ������������� ��������
			itId.set_id_type(s);//������������� ��� id
		}
		else
		{
			if (_My_check->get_MyCheck().back()->get_childs().back()->get_name() == "length")
			{
				
				if ((Myvector.size() == 1) &&(_All_table->get_table_of_identifier()[Myvector.back()->get_num_inTdTable()].get_id_type() == "string"))
				{
					//all ok)
					string s = "int";
					itId.set_dec(true);//������ ������������� ��������
					itId.set_id_type(s);//������������� ��� id
				}
				else
				{
					cout << "� ������� lenght ������ ���� 1 �������� ���� string!!!" << endl;
					system("pause");
					exit(0);
				}
			}
			else
			{
				cout << "���� �� ������������ ������ �������!!!" << endl;
				system("pause");
				exit(0);
			}
		}
		//
		//���� ���������(���������� �������)
		//Base_NeTerminal * Id_func = _My_check->get_MyCheck().back();//��� ���������(id �������)
		//vector <Base_NeTerminal *> Vector_arg;//��������� ��� ���������
		if (Id_func->get_childs().back()->get_name() == "print")//���� ������� print
		{
			//�������� ��� ���������
			//�������� ��������� �� ���������
			stack < string >myStack;

			for (auto arg : Vector_arg)
			{
				int num2 = arg->get_num_inTdTable();
				Identifier & itId2 = _All_table->get_table_of_identifier()[num2];
				if (itId2.get_value() != "")
				{
					myStack.push(itId2.get_value());
					_MyVectorOp->get_VectorOfOP().pop_back();
				}
				else
				{
					cout << "������������� " << itId2.get_name() << " �� ���������������" << endl;
					system("pause");
					exit(0);
				}
			}
			//
			_MyVectorOp->get_VectorOfOP().pop_back();

			while (!myStack.empty())
			{
				cout << myStack.top();
				myStack.pop();
			}

			cout << endl;
		}

		if (Id_func->get_childs().back()->get_name() == "length")//���� ������� lenght
		{
			//��������� �������� � ����������� �������������� lenght
			int n = Vector_arg.back()->get_num_inTdTable();
			Identifier & itId2 = _All_table->get_table_of_identifier()[n];
			int size = itId2.get_value().length();//������ ������

			string str = to_string(size);

			 n = Id_func->get_num_inTdTable();
			Identifier & itId3 = _All_table->get_table_of_identifier()[n];
			itId3.set_value(str);
			_MyVectorOp->get_VectorOfOP().pop_back();
		}
		return this;
	}
	else
	{
		_flag_choice = false;
		return this;
	}
}
