#ifndef TRANSFORMATIONNODE_H
#define TRANSFORMATIONNODE_H

#include "node.h"

class TransformationNode : public Node
{
public:
	TransformationNode();
	void accept(NodeVisitor&);
	double matrix[16];
};

#endif // TRANSFORMATIONNODE_H
