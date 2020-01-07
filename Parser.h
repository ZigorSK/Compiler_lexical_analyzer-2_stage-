#pragma once
#include"scaner.h"
#include"All_headers.h"
#include<stack>
#include"MyCheckVector.h"

class Base_NeTerminal;
class MyCheckVector;
class program;
class Scaner;

class Parser
{
	Scaner *_All_table;
	int *_now_lex;
	Base_NeTerminal *_root;
	MyCheckVector *_MyCheck;
public:
	Parser();
	~Parser();
	
	Base_NeTerminal * finde_syntaxTree();
};