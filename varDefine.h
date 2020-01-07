#pragma once

#include"Parser.h"

class varDefine : public Base_NeTerminal
{
	varDefine() = delete;

public:
	varDefine(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "varDefine" }{	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table, MyCheckVector *_MyCheck) override;
};