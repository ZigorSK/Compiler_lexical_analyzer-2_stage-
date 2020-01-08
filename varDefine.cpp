#include "varDefine.h"


Base_NeTerminal * varDefine::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	//������� _My_check
	_My_check->get_MyCheck().clear();
	_MyVectorOp->get_VectorOfOP().clear();
	//

	//<varDefine> ::= <type><idSeq>;
	//<type>
	Base_NeTerminal *myType = new type(_now_lex, _All_table, this, "type");

	if (*myType->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
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
		return this;
	}


	//������������� ����
	//��������� ��� �� ��������������� ���������� � ������� � ����� Identifier ��, ��� ������ ��� ���������� � �� ���
	string MyType = _My_check->get_MyCheck().front()->get_childs().front()->get_name();
	_My_check->get_MyCheck().erase(_My_check->get_MyCheck().begin());//������� ���(������ �������)

	for (auto Id_ptr : _My_check->get_MyCheck())
	{
		//�������� �� ��������� ����������
		int num = Id_ptr->get_num_inTdTable();
		Identifier &itId = _All_table->get_table_of_identifier()[num];
		if (itId.get_dec() == false)
		{
			itId.set_dec(true);//������ ������������� ��������
			itId.set_id_type(MyType);//������������� ��� id
		}
		else
		{
			//error
			cout << "������������� " << itId.get_name()<<" ��� ��������" << endl;
			system("pause");
			exit(0);
		}
	}
	_My_check->get_MyCheck().clear();//������� ������
	//
	//���� ����������
	//OPZ �� ��������� ������ id = const id id id = const, ��������
	Base_NeTerminal *op_left, *op_right;
	op_left = _MyVectorOp->get_VectorOfOP()[0];
	int size = _MyVectorOp->get_VectorOfOP().size();
	for (int i = 1; i < size; i++)
	{
		op_right = _MyVectorOp->get_VectorOfOP()[i];
		if (op_right->get_name() == "=")
		{
			//������ ����������� �������������
			i++;
			op_right = _MyVectorOp->get_VectorOfOP()[i];
			string tp = _All_table->get_table_of_constant().get_table()[op_right->get_num_inTdTable()].get_const_type();
			//left = right;
			string value;
			if (tp == "char")
			{
				value = op_right->get_childs()[1]->get_name();
			}
			else
			{
				value = op_right->get_childs()[0]->get_name();
			}
			_All_table->get_table_of_identifier().get_table()[op_left->get_num_inTdTable()].set_value(value);//������������� ��������

			i++;
			if (i == size)
				break;
			op_left = _MyVectorOp->get_VectorOfOP()[i];

		}
		else
		{
			op_left = op_right;
		}
	}

	_MyVectorOp->get_VectorOfOP().clear();
	//
	return this;
}

