#pragma once

#include"Parser.h"

class Base_NeTerminal;
class varDefine;


class id : public Base_NeTerminal
{
	id() = delete;

public:
	id(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "id" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table) override;
};