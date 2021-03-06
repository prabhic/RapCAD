/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2013 Giles Bathgate
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

#include "expression.h"

Expression::Expression()
{
}

Expression::~Expression()
{
}

QString Expression::getOpString() const
{
	QString result;
	switch(this->getOp()) {
	case Exponent:
		result.append('^');
		break;
	case Multiply:
		result.append('*');
		break;
	case Concatenate:
		result.append("~");
		break;
	case Append:
		result.append("~=");
		break;
	case ComponentwiseMultiply:
		result.append(".*");
		break;
	case Divide:
		result.append('/');
		break;
	case ComponentwiseDivide:
		result.append("./");
		break;
	case Increment:
		result.append("++");
		break;
	case Decrement:
		result.append("--");
		break;
	case OuterProduct:
		result.append("**");
		break;
	case Modulus:
		result.append('%');
		break;
	case Dot:
		result.append('.');
		break;
	case Add:
		result.append('+');
		break;
	case Subtract:
		result.append('-');
		break;
	case LessThan:
		result.append('<');
		break;
	case LessOrEqual:
		result.append("<=");
		break;
	case Equal:
		result.append("==");
		break;
	case NotEqual:
		result.append("!=");
		break;
	case GreaterOrEqual:
		result.append(">=");
		break;
	case GreaterThan:
		result.append('>');
		break;
	case LogicalAnd:
		result.append("&&");
		break;
	case LogicalOr:
		result.append("||");
		break;
	case Invert:
		result.append('!');
		break;
	case Index:
		result.append("[]");
		break;
	default:
		result.append("Unknown");
	}
	return result;
}

bool Expression::postFix()
{
	return op==Increment||op==Decrement;
}

void Expression::setOp(Operator_e op)
{
	this->op = op;
}

Expression::Operator_e Expression::getOp() const
{
	return this->op;
}
