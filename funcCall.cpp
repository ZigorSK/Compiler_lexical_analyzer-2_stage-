#include "funcCall.h"

Base_NeTerminal * funcCall::derivation(int * now_lex, Scaner * table)
{
	//<funcCall> ::= <id>(<idSeq>)
	Token lexem = _All_table->get_stream_of_token().get_table()[*_now_lex + 1];//Текущий терминал

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "("))
	{
		lexem = _All_table->get_stream_of_token().get_table()[*(_now_lex)];
		//id
		Base_NeTerminal *myid = new id(_now_lex, _All_table, this, "id");

		if (*myid->derivation(_now_lex, _All_table) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
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
		if (*myidSeq->derivation(_now_lex, _All_table) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
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

		return this;
	}
	else
	{
		_flag_choice = false;
		return this;
	}
}
