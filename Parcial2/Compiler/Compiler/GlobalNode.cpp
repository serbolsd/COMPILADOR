#include "stdafx.h"
#include "GlobalNode.h"


Compiler::GlobalNode::GlobalNode()
{
}

Compiler::GlobalNode::~GlobalNode()
{
}

void Compiler::GlobalNode::reset()
{
	if (m_nodolocal!=nullptr)
	{
		m_nodolocal->reset();
	}

}
