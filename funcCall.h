//funcCall
#pragma once
#include"Parser.h"

class Base_NeTerminal;

class funcCall : public Base_NeTerminal
{
	funcCall() = delete;

public:
	funcCall(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "funcCall" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table) override;
};
