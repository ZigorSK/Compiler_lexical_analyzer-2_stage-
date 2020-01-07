#include "expr.h"

Base_NeTerminal * expr::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	//<expr> ::= <id>=<add>
	Token lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)+1];//Текущий терминал

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "="))
	{
		_My_check->get_MyCheck().clear();//Очищаем вектор


		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//
		Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

		if (*myid->derivation(_now_lex, _All_table, _My_check) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
		{
			add(myid);//
		}
		else
		{
			delete myid;//
			cout << "Ожидается идентификатор" << endl;
			Error(_All_table->get_stream_of_token().get_table()[*(_now_lex)], this);
		}
		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];

		//=
		try
		{
			if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "="))//Значит всё ок, создаём класс терминала
			{
				Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "=");//Выделяем память под лист терминала
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
			cout << "Ожидается =" << endl;
			Error obg(err, this);
		}


		//<Add>
		Base_NeTerminal *myadd = new Add(_now_lex, _All_table, this, "Add");

		if (*myadd->derivation(_now_lex, _All_table, _My_check) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
		{
			add(myadd);
		}
		else
		{
			delete myadd;//Ошибка вызовется в следующих классах, если она будет
		}

		//Семантический блок имеем вектор id = id*const +id и тд 
		//Типы мб б string = char + char + char..
		//char = char 
		// int = length(тип int, аргументы проверены у print тип void );
		//
		string t1;
		string t2;
		if (_My_check->get_MyCheck().back()->get_name() == "Const")//константа
		{
			t1 = _All_table->get_table_of_constant().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_const_type();
		}

		if (_My_check->get_MyCheck().back()->get_name() == "id")//Id
		{
			t1 = _All_table->get_table_of_identifier().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_id_type();
		}
		_My_check->get_MyCheck().pop_back();//Удаляем последний элемент

		while (_My_check->get_MyCheck().back()->get_name() != "=")
		{
			if ((_My_check->get_MyCheck().back()->get_name() == "Const") || ((_My_check->get_MyCheck().back()->get_name() == "id")))
			{
				if (_My_check->get_MyCheck().back()->get_name() == "Const")//константа
				{
					t2 = _All_table->get_table_of_constant().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_const_type();
				}

				if (_My_check->get_MyCheck().back()->get_name() == "id")//Id
				{
					t2 = _All_table->get_table_of_identifier().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_id_type();
				}
				_My_check->get_MyCheck().pop_back();//Удаляем последний элемент


				if (t1 != t2)
				{
					//error
					cout << "Несоответствие типа " << t1 << " Типу " << t2 << endl;
					system("pause");
					exit(0);
				}

				t1 = t2;
			}
			else
			{
				_My_check->get_MyCheck().pop_back();//Удаляем последний элемент
			}
		}
		_My_check->get_MyCheck().pop_back();//Удаляем последний элемент
		bool MyFlag = false;
		t2 = _All_table->get_table_of_identifier().get_table()[_My_check->get_MyCheck().back()->get_num_inTdTable()].get_id_type();
		//В t2 значение правой стороны присваивания в t1 левой
		if ((t2 == "string") && (t1 == "char"))//всё ок
		{
			MyFlag = true;
		}
		if (t1 == t2)//всё ок
		{
			MyFlag = true;
		}
		if (MyFlag == false)
		{
			//error
			cout << "Несоответствие типа " << t1 << " Типу " << t2 << endl;
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
