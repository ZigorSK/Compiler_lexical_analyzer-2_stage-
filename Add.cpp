#include "Add.h"

Base_NeTerminal * Add::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	//<Add> ::= <multi><ADD>
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

	//<Add> ::= <multi><Add>
	//<ADD>
	Base_NeTerminal *myADD = new ADD(_now_lex, _All_table, this, "ADD");

	if (*myADD->derivation(_now_lex, _All_table, _My_check, _MyVectorOp) == true)//Если последующее правило свернулось, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myADD);//Значит это правило подходит, добавляем его, как ребёнок данного узла
	}
	else
	{
		delete  myADD;
	}
	return this;
}
