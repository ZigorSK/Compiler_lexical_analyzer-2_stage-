#include "primary.h"

Base_NeTerminal * primary::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//Текущий терминал

	//<primary> ::= (<Add>) |<id> | <const> |<funcCall>
	//(

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "("))//Значит всё ок, создаём класс терминала
	{
		//(<Add>)
		//(
		Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "(");//Выделяем память под лист терминала
		add(child);//Добавляем ребёнка
		_MyVectorOp->push_back(child);
		(*_now_lex)++;
		
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

		//
		lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//Текущий терминал
		//)
		try
		{
			if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ")"))//Значит всё ок, создаём класс терминала
			{
				Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, ")");//Выделяем память под лист терминала
				add(child);//Добавляем ребёнка
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
			cout << "Ожидается )" << endl;
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

			if (*myConst->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
			{
				add(myConst);
			}
			else
			{
				delete myConst;
				//id
				Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

				if (*myid->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
				{
					add(myid);
				}
				else
				{
					delete myid;
					_flag_choice = false;
					//Ошибка
					cout << "Ожирается идентивикатор или константа" << endl;
					Error(lexem, this);
				}
			}
		}
	}
	return this;
}
