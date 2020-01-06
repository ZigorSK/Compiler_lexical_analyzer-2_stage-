#include "Const.h"

Base_NeTerminal * Const::derivation(int * now_lex, Scaner * table)
{

	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//Текущий терминал

	if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "'"))//Символьная константа
	{
		Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//Выделяем память под новый терминал
		add(child);//Добавляем ребёнка
		(*_now_lex)++;

		lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];

		if (lexem.get_type() == CONSTANT) //Символьная константа
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//Выделяем память под новый терминал
			add(child);//Добавляем ребёнка
			(*_now_lex)++;
		}
		else
		{
			_flag_choice = false;
			cout << "Ожидается константа" << endl;
			Error obg(lexem, this);
			return this;
		}

		lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];

		if ((lexem.get_type() == DIVIDER) && (lexem.get_name() == "'"))//Символьная константа
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//Выделяем память под новый терминал
			add(child);//Добавляем ребёнка
			(*_now_lex)++;
		}
		else
		{
			_flag_choice = false;
			return this;
		}
	}
	else//Числовая константа
	{
		if (lexem.get_type() == CONSTANT) //Символьная константа
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//Выделяем память под новый терминал
			add(child);//Добавляем ребёнка
			(*_now_lex)++;
		}
		else
		{
			_flag_choice = false;
			return this;
		}
	}

	return this;
}

