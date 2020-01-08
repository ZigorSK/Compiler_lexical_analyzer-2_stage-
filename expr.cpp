#include "expr.h"

Base_NeTerminal * expr::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	_My_check->get_MyCheck().clear();
	_MyVectorOp->get_VectorOfOP().clear();
	//<expr> ::= <id>=<add>
	Token lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)+1];//Текущий терминал

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "="))
	{
		_My_check->get_MyCheck().clear();//Очищаем вектор


		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//
		Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

		if (*myid->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
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
				_MyVectorOp->push_back(child);
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

		if (*myadd->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
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
		_My_check->get_MyCheck().clear();


		//Генерация
		int num = _MyVectorOp->get_VectorOfOP()[0]->get_num_inTdTable();
		Identifier & itId = _All_table->get_table_of_identifier()[num];
		_MyVectorOp->get_VectorOfOP().erase(_MyVectorOp->get_VectorOfOP().begin());//id 
		_MyVectorOp->get_VectorOfOP().erase(_MyVectorOp->get_VectorOfOP().begin());// = 

		if(itId.get_id_type() == "string")//Для строки слияние char ов
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
						cout << "Для строк применима только операция +" << endl;
						system("pause");
						exit(0);
					}
				}
				_MyVectorOp->get_VectorOfOP().erase(_MyVectorOp->get_VectorOfOP().begin());
			}
			itId.set_value(str);

		}
		else//для int
		{
			//Проверка на инициализацию
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
		if (i->get_name() == "Const")//константа
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
					cout << "Идентификатор "<< _All_table->get_table_of_identifier().get_table()[i->get_num_inTdTable()].get_name() <<" не инициализирован!!!" << endl;
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
		
	//ПОлучаем вектор во значениями
	//Преобразование в оПЗ
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
			OPN.push_back(i);//Если операнд, помещаем в Вых строку
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

	//Имеем выражение в обратной польской записи
	//вычислить его
	int count = 0;

	for (int i = 0; i< OPN.size(); i++)
	{
		if (prior(OPN[i]) == 0)//Значит это не оператор
		{
			MyStack.push(OPN[i]);
		}
		else
		{
			//вычисляем
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
	//Назад в строку
	result = to_string(RESULT);
	return result;
}
