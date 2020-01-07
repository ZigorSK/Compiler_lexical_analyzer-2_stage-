#include "varDefine.h"


Base_NeTerminal * varDefine::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	//������� _My_check
	_My_check->get_MyCheck().clear();
	//

	//<varDefine> ::= <type><idSeq>;
	//<type>
	Base_NeTerminal *myType = new type(_now_lex, _All_table, this, "type");

	if (*myType->derivation(_now_lex, _All_table, _My_check) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
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
	if (*myidSeq->derivation(_now_lex, _All_table, _My_check) == true)//���� ��� ����������� ������� ��������, �� �� ��) �������� ���������� ����������� ����� � ���������� �� �������� ������
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

	return this;
}

