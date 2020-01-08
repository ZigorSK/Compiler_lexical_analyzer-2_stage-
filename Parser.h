#pragma once
#include"scaner.h"
#include"All_headers.h"

class Base_NeTerminal;
class MyCheckVector;
class VectorOfOP;
class program;
class Scaner;

class Parser
{
	Scaner *_All_table;
	int *_now_lex;
	Base_NeTerminal *_root;

	MyCheckVector *_MyCheck;//Вектор для семантики
	VectorOfOP * _MyVectorOp;//Вектор для генерации
public:
	Parser();
	~Parser();
	
	int toCompile();
	Base_NeTerminal * finde_syntaxTree();
};