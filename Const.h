#pragma once

#include"Parser.h"

class Base_NeTerminal;
class varDefine;

class Const : public Base_NeTerminal
{
	Const() = delete;

public:
	Const(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "Const" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table, MyCheckVector *_MyCheck, VectorOfOP * _MyVectorOp) override;
};