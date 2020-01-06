#include "Parser.h"

Parser::Parser()
{
	_All_table = new Scaner();
	_All_table->to_scan();//Получаем все лексемы в таблицы
	_now_lex = new int;
	*_now_lex = 0;//Рассматриваем с первой лексемы
	_root = nullptr;
}

Parser::~Parser()
{
	delete _All_table;
	delete _now_lex;
	delete _root;
}

Base_NeTerminal * Parser::finde_syntaxTree()
{
	_root = new program(_now_lex, _All_table, nullptr, "program");
	_All_table->print_stream_of_lex();

	_root->derivation( _now_lex, _All_table );//Строим дерево
	
	ofstream parse("parse_tree.dot");
	if (!parse)
		cout << "Не удалось создать файл" << endl;
	parse << "digraph A" << endl;
	parse << "{" << endl;
	_root->PrintTree(parse);
	parse << "}" << endl;
	parse.close();
	system("graphviz-2.38\\bin\\dot -Tpng parse_tree.dot -o parse_tree.png");
	system("pause");
	return _root;
	//return nullptr;
}


