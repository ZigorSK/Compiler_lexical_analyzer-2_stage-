#pragma once
#include"Base_NeTerminal.h"
#include<vector>

using namespace std;

class Base_NeTerminal;

class VectorOfOP
{
	vector <Base_NeTerminal*> _VectorOfOP;

public:
	VectorOfOP() {};
	void push_back(Base_NeTerminal *obg) { _VectorOfOP.push_back(obg); };
	vector <Base_NeTerminal*>& get_VectorOfOP() { return _VectorOfOP; };

	Base_NeTerminal* operator[](int i) { return _VectorOfOP[i]; };
};
