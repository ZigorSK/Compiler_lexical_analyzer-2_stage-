#include "progBlock.h"

Base_NeTerminal * progBlock::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	//<progBlock> :: = <varDefine><progBlock> | <operBlock><progBlock>| e
	//<varDefine>
	Base_NeTerminal *myVarDefine = new varDefine(_now_lex, _All_table, this, "varDefine");

	if (*myVarDefine->derivation(_now_lex, _All_table, _My_check) == true)//Если последующее правило свернулось, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myVarDefine);//Значит это правило подходит, добавляем его, как ребёнок данного узла
	}
	else
	{
		delete  myVarDefine;//Если не получилось свернуть правило, то рассматриваем следующее

		//<operBlock>
		Base_NeTerminal *  myOperBlock = new operBlock(_now_lex, _All_table, this, "operBlock");

		if (*myOperBlock->derivation(_now_lex, _All_table, _My_check) == true)
		{
			add(myOperBlock);
		}
		else
		{
			_flag_choice = false;
			delete myOperBlock;//Значит пустой симовл
			return this;
		}
	}

	//Если Это <varDefine>|<operBlock>, то создаём <progBlock>
	//<progBlock>

	Base_NeTerminal *  myProgBlock = new progBlock(_now_lex, _All_table, this, "progBlock");

	if (*myProgBlock->derivation(_now_lex, _All_table, _My_check) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myProgBlock);
	}
	else
	{
		delete myProgBlock;//Значит сварачивается в пустой символ
	}

	return this;
}
