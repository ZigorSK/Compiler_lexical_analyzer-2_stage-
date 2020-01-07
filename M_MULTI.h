//MULTI
#pragma once

#include"Parser.h"

class Base_NeTerminal;

class MULTI : public Base_NeTerminal
{
	MULTI() = delete;

public:
	MULTI(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "MULTI" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table, MyCheckVector *_MyCheck) override;
};