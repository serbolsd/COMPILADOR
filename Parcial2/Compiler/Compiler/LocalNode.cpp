#include "stdafx.h"
#include "LocalNode.h"


Compiler::LocalNode::LocalNode()
{
}

Compiler::LocalNode::~LocalNode()
{
}

void Compiler::LocalNode::reset()
{
	if (m_nodolocal!=nullptr)
	{
		m_nodolocal->reset();
	}
	delete m_nodolocal;
	m_nodolocal = nullptr;
}
