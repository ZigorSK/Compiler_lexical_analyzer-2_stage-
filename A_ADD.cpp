#include "A_ADD.h"

Base_NeTerminal * ADD::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//Текущий терминал

	//<ADD> :: = +<multi><ADD> | -<multi><ADD> | ε
	if (lexem.get_name() == "+")// +<primary><MULTI>
	{
		//+
		Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "+");//Выделяем память под лист терминала
		add(child);//Добавляем ребёнка
		_MyVectorOp->push_back(child);
		_My_check->push_back(child);//Добавляем терминал = 
		(*_now_lex)++;

	}
	else
	{
		if (lexem.get_name() == "-")// -<primary><MULTI>
		{
			// -
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "-");//Выделяем память под лист терминала
			add(child);//Добавляем ребёнка
			_My_check->push_back(child);//Добавляем терминал = 
			_MyVectorOp->push_back(child);
			(*_now_lex)++;
		}
		else//ε
		{
			_flag_choice = false;//пустой символ
			return this;
		}
	}
	//<multi><ADD> 
	//<multi>
	Base_NeTerminal *mymulti = new multi(_now_lex, _All_table, this, "multi");

	if (*mymulti->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если последующее правило свернулось, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(mymulti);//Значит это правило подходит, добавляем его, как ребёнок данного узла
	}
	else
	{
		delete  mymulti;
	}

	//<multi><ADD> 
	//<ADD> 
	Base_NeTerminal *myADD = new ADD(_now_lex, _All_table, this, "ADD");

	if (*myADD->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если последующее правило свернулось, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myADD);//Значит это правило подходит, добавляем его, как ребёнок данного узла
	}
	else
	{
		delete myADD;
	}

	return this;
}
