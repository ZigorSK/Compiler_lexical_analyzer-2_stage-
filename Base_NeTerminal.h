#pragma once
#include<string>
#include<vector>
#include"scaner.h"
#include<stack>
using namespace std;

class Scaner;



class Base_NeTerminal
{
protected:
	Base_NeTerminal() = delete;

	string _name;//��� ������� ����(�����������), (���� ��������, �� ��� ���������)
	Base_NeTerminal * _parent;//��������� �� ��������
	vector <Base_NeTerminal *> _childs;//���� ������� ���� 
	int _num_node;//����� ���� 

	int *_now_lex;//��������� �� ����� ������ ������� � ������ ������
	Scaner * _All_table;//��������� �� ��� �������

	bool _flag_choice;//���� ������ �������, true, ���� ������� ��������

public:

	Base_NeTerminal(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) :_now_lex(now_lex), _All_table(All_table), _parent(parent), _name(name), _num_node(0), _flag_choice(true) {};
	virtual ~Base_NeTerminal();

	virtual Base_NeTerminal *getSyntaxTree();//���������� ��������� �� ������
	virtual Base_NeTerminal *derivation(int *now_lex, Scaner *table);
	virtual void add(Base_NeTerminal * child);

	void set_num_node(int num_node) { _num_node = num_node; };
	void set_parent(Base_NeTerminal *d) { _parent = d; };

	bool operator==( bool op);
	Base_NeTerminal *get_parent() { return _parent; };

	void PrintTree(ostream &stream)
	{
		for (auto &ch : _childs)
		{
			stream << "\t\"" << "nodeId = " << _num_node << " | " << _name << "\"->\"" << "nodeId = " << ch->_num_node << " | " << ch->_name << "\";" << endl;
			ch->PrintTree(stream);
		}
	};
}; 
