//ADD
#pragma once

#include"Parser.h"

class Base_NeTerminal;

class ADD : public Base_NeTerminal
{
	ADD() = delete;

public:
	ADD(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "ADD" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table, MyCheckVector *_MyCheck, VectorOfOP * _MyVectorOp) override;
};