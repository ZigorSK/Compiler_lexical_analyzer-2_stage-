#include "varDefine.h"


Base_NeTerminal * varDefine::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	//Очищаем _My_check
	_My_check->get_MyCheck().clear();
	_MyVectorOp->get_VectorOfOP().clear();
	//

	//<varDefine> ::= <type><idSeq>;
	//<type>
	Base_NeTerminal *myType = new type(_now_lex, _All_table, this, "type");

	if (*myType->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myType);
	}
	else
	{
		_flag_choice = false;
		delete myType;
		return this;//Значит правило varDefine не подходит для progBlock
	}

	//<varDefine> ::= <type><idSeq>;
	//<idSeq>

	Base_NeTerminal *myidSeq = new idSeq(_now_lex, _All_table, this, "idSeq");
	if (*myidSeq->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myidSeq);
	}
	else
	{
		delete myidSeq;//
		cout << "Ожидается идентификатор" << endl;
		Error(_All_table->get_stream_of_token().get_table()[*(_now_lex)], this);
	}


	//<varDefine> ::= <type><idSeq>;
	//;
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//Текущий терминал

	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ";"))//Значит всё ок, создаём класс терминала
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, ";");//Выделяем память под новый терминал
			add(child);//Добавляем ребёнка
			(*_now_lex)++;
		}
		else
		{
			throw lexem;
		}
	}
	catch (Token err)
	{
		cout << "Ожидается ;" << endl;
		Error obg(err, this);
		return this;
	}


	//Семантический блок
	//Проверяем нет ли переопределения переменных и заносим в класс Identifier то, что теперь они определены и их тип
	string MyType = _My_check->get_MyCheck().front()->get_childs().front()->get_name();
	_My_check->get_MyCheck().erase(_My_check->get_MyCheck().begin());//Удаляем тип(первый элемент)

	for (auto Id_ptr : _My_check->get_MyCheck())
	{
		//Проверка на повторную декларацию
		int num = Id_ptr->get_num_inTdTable();
		Identifier &itId = _All_table->get_table_of_identifier()[num];
		if (itId.get_dec() == false)
		{
			itId.set_dec(true);//Теперь идентификатор объявлен
			itId.set_id_type(MyType);//Устанавливаем тип id
		}
		else
		{
			//error
			cout << "Идентификатор " << itId.get_name()<<" уже объявлен" << endl;
			system("pause");
			exit(0);
		}
	}
	_My_check->get_MyCheck().clear();//Очищаем вектор
	//
	//блок выполнения
	//OPZ не требуется вектор id = const id id id = const, например
	Base_NeTerminal *op_left, *op_right;
	op_left = _MyVectorOp->get_VectorOfOP()[0];
	int size = _MyVectorOp->get_VectorOfOP().size();
	for (int i = 1; i < size; i++)
	{
		op_right = _MyVectorOp->get_VectorOfOP()[i];
		if (op_right->get_name() == "=")
		{
			//Значит изначальная инициализация
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
			_All_table->get_table_of_identifier().get_table()[op_left->get_num_inTdTable()].set_value(value);//Устанавливаем значение

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

