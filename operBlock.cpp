#include "operBlock.h"

Base_NeTerminal * operBlock::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	//<operBlock> ::= <expr><operBlock>; | <funcCall><operBlock>; | ε
	//<expr>
	Base_NeTerminal *myExpr = new expr(_now_lex, _All_table, this, "expr");

	if (*myExpr->derivation(_now_lex, _All_table, _My_check) == true)//Если последующее правило свернулось, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myExpr);//Значит это правило подходит, добавляем его, как ребёнок данного узла
	}
	else
	{
		delete  myExpr;//Если не получилось свернуть правило, то рассматриваем следующее

		//<funcCall>
		Base_NeTerminal *  myFuncCall = new funcCall(_now_lex, _All_table, this, "operBlock");

		if (*myFuncCall->derivation(_now_lex, _All_table, _My_check) == true)
		{
			add(myFuncCall);
		}
		else
		{
			_flag_choice = false;
			delete myFuncCall;//Значит пустой симовл
			return this;
		}
	}

	//<operBlock> :: = <expr>; | <funcCall>; | ε
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
	}

	return this;
}