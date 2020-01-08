//operBlock
#pragma once
#include"Parser.h"

class Base_NeTerminal;

class operBlock : public Base_NeTerminal
{
	operBlock() = delete;

public:
	operBlock(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "operBlock" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table, MyCheckVector *_MyCheck, VectorOfOP * _MyVectorOp) override;
};