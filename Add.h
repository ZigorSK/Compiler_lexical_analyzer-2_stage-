//Add
#pragma once

#include"Parser.h"

class Base_NeTerminal;
class varDefine;

class Add : public Base_NeTerminal
{
	Add() = delete;

public:
	Add(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "Add" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table) override;
};