#include "Base_NeTerminal.h"

Base_NeTerminal::~Base_NeTerminal()
{
	for (auto child : _childs)
		delete child;
}

Base_NeTerminal * Base_NeTerminal::getSyntaxTree()
{

	return nullptr;
}

Base_NeTerminal * Base_NeTerminal::derivation(int * now_lex, Scaner * table)
{
	return this;
}

void Base_NeTerminal::add(Base_NeTerminal * child)
{
	static int id = 0;

	child->set_num_node(id);
	id++;
	child->set_parent(this);
	_childs.push_back(child);
}

bool Base_NeTerminal::operator==(bool op)
{
	if (_flag_choice == op)
	{
		return true;
	}
	else
		return false; 
}

