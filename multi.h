//multi
#pragma once

#include"Parser.h"

class Base_NeTerminal;
class varDefine;

class multi : public Base_NeTerminal
{
	multi() = delete;

public:
	multi(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "multi" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table, MyCheckVector *_MyCheck) override;
};