/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2011 Giles Bathgate
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "modulescope.h"

ModuleScope::ModuleScope()
{
}

ModuleScope::~ModuleScope()
{
	for(int i=0; i<declarations.size(); i++)
		delete declarations.at(i);
}

void ModuleScope::setDeclarations(QVector<Declaration*> decls)
{
	this->declarations = decls;
}

QVector<Declaration*> ModuleScope::getDeclarations()
{
	return this->declarations;
}

void ModuleScope::accept(Visitor& v)
{
	v.visit(this);
}