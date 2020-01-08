#include "type.h"

Base_NeTerminal * type::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{
	
	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//Текущий терминал

	//<type> :: = char | int | float | double | string
	//

		if (((lexem.get_type() == KEYWORD) && (lexem.get_name() == "char"))||
			((lexem.get_type() == KEYWORD) && (lexem.get_name() == "int")) ||
			((lexem.get_type() == KEYWORD) && (lexem.get_name() == "float"))||
			((lexem.get_type() == KEYWORD) && (lexem.get_name() == "double"))||
			((lexem.get_type() == KEYWORD) && (lexem.get_name() == "string")))//Значит всё ок, создаём лист - класс терминала
		{
			Base_NeTerminal *child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//Выделяем память под новый терминал
			add(child);//Добавляем ребёнка

			_My_check->push_back(this);//Добавляем указатель на класс type в Вектор

			(*_now_lex)++;
		}
		else
		{
			_flag_choice = false;
		}

	return this;
}
