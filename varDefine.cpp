#include "varDefine.h"


Base_NeTerminal * varDefine::derivation(int * now_lex, Scaner * table)
{

	//<varDefine> ::= <type><idSeq>;
	//<type>
	Base_NeTerminal *myType = new type(_now_lex, _All_table, this, "type");

	if (*myType->derivation(_now_lex, _All_table) == true)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
	{
		add(myType);
	}
	else
	{
		_flag_choice = false;
		delete myType;
		return this;//Значит правило varDefine не подходит для progBlock
	}

	//<varDefine> ::= <type><idSeq>;
	//<idSeq>

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


	//<varDefine> ::= <type><idSeq>;
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

