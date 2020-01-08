#include "id.h"

Base_NeTerminal * id::derivation(int * now_lex, Scaner * table, MyCheckVector *_My_check, VectorOfOP * _MyVectorOp)
{

	Token lexem = _All_table->get_stream_of_token().get_table()[(*_now_lex)];//Текущий терминал

	//id
	if (lexem.get_type() == IDENTIFIER)//Значит всё ок, создаём класс терминала
	{
		Base_NeTerminal * child = new Terminal(_now_lex, _All_table, this, lexem.get_name());//Выделяем память под новый терминал
		add(child);//Добавляем ребёнка

		//Определить номер в таблице ID (ПРоверить работу)
		_num_in_IdTable = _All_table->get_table_of_identifier().finde_num(lexem.get_name());//Номер данного ID в таблице
		_My_check->push_back(this);//Добавляем указатель на ID в Вектор
		_MyVectorOp->push_back(this);//Добавляем в вектор id для генерации 
		//
		(*_now_lex)++;
	}
	else
	{
		_flag_choice = false;
	}

	return this;
}
