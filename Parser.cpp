#include "Parser.h"

Parser::Parser()
{
	_All_table = new Scaner();
	_All_table->to_scan();//�������� ��� ������� � �������
	_now_lex = new int;
	*_now_lex = 0;//������������� � ������ �������
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
	_root = _root->getSyntaxTree();//�������� ��������� �� ������

	return _root;
}


