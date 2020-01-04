#pragma once

#include"Parser.h"

class Base_NeTerminal;
class varDefine;

class idSeq : public Base_NeTerminal
{
	idSeq() = delete;

public:
	idSeq(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "Terminal" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table) override;
};