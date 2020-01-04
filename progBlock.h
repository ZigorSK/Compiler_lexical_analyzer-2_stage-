#pragma once
#pragma once
#include"Parser.h"

class Base_NeTerminal;
class program;

class progBlock : public Base_NeTerminal
{
	progBlock() = delete;

public:
	progBlock(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "ProgBlock" }{ };

	Base_NeTerminal *derivation(int *now_lex, Scaner *table) override;
};