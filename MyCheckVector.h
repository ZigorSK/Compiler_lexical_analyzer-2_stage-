#pragma once
#include"Base_NeTerminal.h"
#include<vector>

using namespace std;


class Base_NeTerminal;

class MyCheckVector
{
	vector <Base_NeTerminal*> _myCheck;

public:
	MyCheckVector() {};
	void push_back(Base_NeTerminal *obg) { _myCheck.push_back(obg); };
	vector <Base_NeTerminal*>& get_MyCheck() { return _myCheck; };

	Base_NeTerminal* operator[](int i) { return _myCheck[i]; };
};

