#include "idSeq.h"

Base_NeTerminal * idSeq::derivation(int * now_lex, Scaner * table)
{

	Token lexem = _All_table->get_stream_of_token().get_table()[(*(_now_lex+1))];//Следующий терминал - костыль(для рассмотрения ,)
	// < idSeq > :: = <id> | <id>, <idSeq>
	//< idSeq > :: = <id> 
	//<id>
	Base_NeTerminal *  myid = new id(_now_lex, _All_table, this, "id");
	if (myid->derivation(_now_lex, _All_table) != nullptr)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
		add(myid);
	else
	{
		delete myid;
		Error(_All_table->get_stream_of_token().get_table()[(*(_now_lex))], this);
	}

	if (lexem.get_name() == ",")//< idSeq > :: = <id>, <idSeq>
	{
		//,
		try
		{
			if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ","))//Значит всё ок, создаём класс терминала
			{
				Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, "Terminal");//Выделяем память под новый терминал
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
			Error obg(err, this);
		}

		//<idSeq>
		Base_NeTerminal *  myidSeq = new idSeq(_now_lex, _All_table, this, "idSeq");
		if (myidSeq->derivation(_now_lex, _All_table) != nullptr)//Если все последующие правила проходят, то всё ок) вызываем рекурсивно полиморфный метод и определяем по крайнему левому
			add(myidSeq);
		else
		{
			delete myidSeq;//
			Error(_All_table->get_stream_of_token().get_table()[(*(_now_lex))], this);
		}
	}

	
	return this;
}
