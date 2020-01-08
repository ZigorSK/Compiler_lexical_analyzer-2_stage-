//expr
#pragma once
#include"Parser.h"

class Base_NeTerminal;

class expr : public Base_NeTerminal
{
	expr() = delete;

public:
	expr(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "expr" } {	};

	Base_NeTerminal *derivation(int *now_lex, Scaner *table, MyCheckVector *_MyCheck, VectorOfOP * _MyVectorOp) override;
	string &convert_to_OPW(VectorOfOP * _MyVectorOp);
	int prior(string obg)
	{
		if ((obg == "+") || (obg == "-"))
		{
			return 2;
		}
		else
		{
			if ((obg == "*") || (obg == "/"))
			{
				return 1;
			}
			else
			{
				if (obg == "(")
				{
					return 3;
				}
				else
				{
					if (obg == ")")
					{
						return 3;
					}
					else
					{
						return 0;
					}
				}
			}
		}
	};
	string& calcul(string op1, string op2, string oper);//str 1 opn[1] str2 
};