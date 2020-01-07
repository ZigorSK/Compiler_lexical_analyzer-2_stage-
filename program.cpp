#include "program.h"

Base_NeTerminal * program::getSyntaxTree()
{
	return nullptr;
}

Base_NeTerminal * program::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check)
{
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//Текущий терминал
	//<program> ::= main();{<progBlock>}^

	//main
	try
	{
		if ((lexem.get_type() == KEYWORD) && (lexem.get_name() == "main"))//Значит всё ок, создаём класс терминала
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, "main");//Выделяем память под лист терминала
			add(child);//Добавляем ребёнка
			(*_now_lex)++;//Следубщая лексема
		}
		else
		{
			throw lexem;//Ошибка
		}
	}
	catch (Token err)
	{
		cout << "Ожидается main" << endl;
		Error obg( err, this );
	}

	lexem = _All_table->get_stream_of_token().get_table()[*_now_lex];
	//<program> ::= main();{<progBlock>}^
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

	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//)
	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ")"))//Значит всё ок, создаём класс терминала
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, ")");//Выделяем память под лист терминала
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

	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//;
	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == ";"))//Значит всё ок, создаём класс терминала
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, ";");//Выделяем память под лист терминала
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

	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//{
	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "{"))//Значит всё ок, создаём класс терминала
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, "{");//Выделяем память под лист терминала
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
		cout << "Ожидается {" << endl;
		Error obg(err, this);
	}

	//<program> ::= main();{<progBlock>}^
	//<progBlock>

	Base_NeTerminal *  prBlock = new progBlock(_now_lex, _All_table, this, "progBlock");
	if (*prBlock->derivation(_now_lex, _All_table, _My_check) == true)//Если все последующие правила свернулись, то всё ок)
		//вызов рекурсивно полиморфного метода. Определяем по крайнему левому терминалу
	{
		add(prBlock);
	}
	else
	{
		delete prBlock;//Значит в теле main пусто
	}

	//
	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//}
	try
	{
		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "}"))//Значит всё ок, создаём класс терминала
		{
			Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, "}");//Выделяем память под новый лист терминала
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
		cout << "Ожидается }" << endl;
		Error obg(err, this);
	}

	lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];
	//<program> ::= main();{<progBlock>}^
	//End_of_file

	if ((lexem.get_type() == END_OF_programM) && (lexem.get_name() == ""))//Значит всё ок
	{
		return this;
	}
	else
	{
		cout << "Ожидается конец программы" << endl;
		Error(lexem, this);
		
	}
	return this;
}

