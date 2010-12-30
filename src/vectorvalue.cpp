/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010  Giles Bathgate
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

#include "vectorvalue.h"

VectorValue::VectorValue(QVector<Value*> values)
{
	this->children=values;
}

QString VectorValue::getValueString()
{
	QString result;
	result.append("[");
	for(int i=0; i<children.size(); i++) {
		if(i>0)
			result.append(",");
		result.append(children.at(i)->getValueString());
	}
	result.append("]");
	return result;
}
