//expr
#pragma once
#include"Parser.h"

class Base_NeTerminal;

class expr : public Base_NeTerminal
{
	expr() = delete;

public:
	expr(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "expr" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table) override;
};