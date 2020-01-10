#include "funcCall.h"

Base_NeTerminal * funcCall::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	//<funcCall> ::= <id>(<idSeq>)
	Token lexem = _All_table->get_stream_of_token().get_table()[*_now_lex + 1];//Текущий терминал

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "("))
	{
		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//id
		Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

		if (*myid->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
		{
			add(myid);
		}
		else
		{
			delete myid;//
			cout << "Ожидается идентификатор" << endl;
			Error(_All_table->get_stream_of_token().get_table()[*(_now_lex)], this);
		}

		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//(
		try
		{
			if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "("))//Значит всё ок, создаём класс терминала
			{
				Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "(");//Выделяем память под лист терминала
				add(child);//Добавляем ребёнка
				_My_check->push_back(child);//Добавляем терминал = 
				(*_now_lex)++;
			}
			else
			{
				throw lexem;
			}
		}
		catch (Token err)
		{
			cout << "Ожидается (" << endl;
			Error obg(err, this);
		}

		//idSeq
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

		//
		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//)

		try
		{
			if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ")"))//Значит всё ок, создаём класс терминала
			{
				Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, ")");//Выделяем память под лист терминала
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
			cout << "Ожидается )" << endl;
			Error obg(err, this);
		}


		//Семантический блок проверка соответсвия типов.
		vector <Base_NeTerminal *>Myvector;
	
		while (_My_check->get_MyCheck().back()->get_name() != "(")
		{
			Myvector.push_back(_My_check->get_MyCheck().back());
			_My_check->get_MyCheck().pop_back();//Удаляем последний элемент
		}
		_My_check->get_MyCheck().pop_back();//Удаляем последний элемент

		Base_NeTerminal * Id_func = _My_check->get_MyCheck().back();//Для генерации(id функции)
		vector <Base_NeTerminal *> Vector_arg = Myvector;//Аргументы для генерации
		//таким образом в Myvector имеем список аргументов а последний элемент _My_check - имя функции
		
		int num = _My_check->get_MyCheck().back()->get_num_inTdTable();
		Identifier & itId = _All_table->get_table_of_identifier()[num];

		//проверка обявлены ли аргументы функций?
		for (auto i : Myvector)
		{
			int num1 = i->get_num_inTdTable();
			Identifier & itId1 = _All_table->get_table_of_identifier()[num1];
			if (itId1.get_dec() == false)
			{
				cout << "Идентификатор " << itId1.get_name()<<" не обявлен!!!" << endl;
				system("pause");
				exit(0);
			}

		}
		//

		if (_My_check->get_MyCheck().back()->get_childs().back()->get_name() == "print")
		{
			if (Myvector.size() < 1)
			{
				cout << "У функции print не может быть меньше 1 параметра!!!" << endl;
				system("pause");
				exit(0);
			}
			//all ok)
			string s = "void";
			itId.set_dec(true);//Теперь идентификатор объявлен
			itId.set_id_type(s);//Устанавливаем тип id
		}
		else
		{
			if (_My_check->get_MyCheck().back()->get_childs().back()->get_name() == "length")
			{
				
				if ((Myvector.size() == 1) &&(_All_table->get_table_of_identifier()[Myvector.back()->get_num_inTdTable()].get_id_type() == "string"))
				{
					//all ok)
					string s = "int";
					itId.set_dec(true);//Теперь идентификатор объявлен
					itId.set_id_type(s);//Устанавливаем тип id
				}
				else
				{
					cout << "У функции lenght Должен быть 1 аргумент типа string!!!" << endl;
					system("pause");
					exit(0);
				}
			}
			else
			{
				cout << "Язык не поддерживает данную функцию!!!" << endl;
				system("pause");
				exit(0);
			}
		}
		//
		//Блок генерации(выполнение функций)
		//Base_NeTerminal * Id_func = _My_check->get_MyCheck().back();//Для генерации(id функции)
		//vector <Base_NeTerminal *> Vector_arg;//Аргументы для генерации
		if (Id_func->get_childs().back()->get_name() == "print")//Если функция print
		{
			//Печатаем все аргументы
			//Проверка объявлены ли аргументы
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
					cout << "Идентификатор " << itId2.get_name() << " не Инициализирован" << endl;
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

		if (Id_func->get_childs().back()->get_name() == "length")//Если функция lenght
		{
			//Вычисляем значение и призваиваем идентификатору lenght
			int n = Vector_arg.back()->get_num_inTdTable();
			Identifier & itId2 = _All_table->get_table_of_identifier()[n];
			int size = itId2.get_value().length();//длинна строки

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
