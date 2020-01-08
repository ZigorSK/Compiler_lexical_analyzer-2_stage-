#include "M_MULTI.h"

Base_NeTerminal * MULTI::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//Текущий терминал

	//<MULTI> ::= *<primary><MULTI> | /<primary><MULTI> | ε
	if (lexem.get_name() == "*")//*<primary><MULTI>
	{
		//*
		Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "*");//Выделяем память под лист терминала
		add(child);//Добавляем ребёнка
		_My_check->push_back(child);//Добавляем терминал *
		_MyVectorOp->push_back(child);
		(*_now_lex)++;
		
	}
	else
	{
		if (lexem.get_name() == "/")// /<primary><MULTI>
		{
			// /
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "/");//Выделяем память под лист терминала
			add(child);//Добавляем ребёнка
			_My_check->push_back(child);//Добавляем терминал /
			_MyVectorOp->push_back(child);
			(*_now_lex)++;
		}
		else//ε
		{
			_flag_choice = false;//пустой символ
			return this;
		}
	}
	//<primary><MULTI> 
	//<primary>
	Base_NeTerminal *myprimary = new primary(_now_lex, _All_table, this, "primary");

	if (*myprimary->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если последующее правило свернулось, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myprimary);//Значит это правило подходит, добавляем его, как ребёнок данного узла
	}
	else
	{
		delete  myprimary;
	}

	//<multi> ::= <primary><MULTI>
	//<MULTI>
	Base_NeTerminal *myMULTI = new MULTI(_now_lex, _All_table, this, "MULTI");

	if (*myMULTI->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если последующее правило свернулось, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myMULTI);//Значит это правило подходит, добавляем его, как ребёнок данного узла
	}
	else
	{
		delete myMULTI;
	}

	return this;
}
