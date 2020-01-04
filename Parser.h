#pragma once
#include"scaner.h"
#include"All_headers.h"

class Base_NeTerminal;

class program;

class Scaner;

class Parser
{
	Scaner *_All_table;
	int *_now_lex;
	Base_NeTerminal *_root;
public:
	Parser();
	~Parser();
	
	Base_NeTerminal * finde_syntaxTree();
};