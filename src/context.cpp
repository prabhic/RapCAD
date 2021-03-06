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

#include "context.h"
#include "modulescope.h"

Context::Context(QTextStream& s) : output(s)
{
	parent=NULL;
	currentValue=NULL;
	returnValue=NULL;
	currentScope=NULL;
}

void Context::setParent(Context* value)
{
	parent=value;
}

void Context::setCurrentScope(Scope* value)
{
	currentScope=value;
}

Scope* Context::getCurrentScope()
{
	return currentScope;
}

void Context::setReturnValue(Value* value)
{
	returnValue=value;
}

Value* Context::getReturnValue()
{
	return returnValue;
}

Value* Context::getCurrentValue()
{
	return currentValue;
}

void Context::setCurrentValue(Value* value)
{
	currentValue=value;
}

QString Context::getCurrentName()
{
	return currentName;
}

void Context::setCurrentName(QString value)
{
	currentName=value;
}

Module* Context::lookupModule(QString name)
{
	if(!modules.contains(name)) {
		foreach(Declaration* d,currentScope->getDeclarations()) {
			Module* mod = dynamic_cast<Module*>(d);
			if(mod && mod->getName() == name) {
				modules.insert(name,mod);
				return mod;
			}
		}
		if(parent)
			return parent->lookupModule(name);
	}

	return modules.value(name);
}

Function* Context::lookupFunction(QString name)
{
	if(!functions.contains(name)) {
		//We are not looking for the function within the function
		//scope (which is invalid syntax) but rather in the current
		//scope which could be a module or script
		foreach(Declaration* d,currentScope->getDeclarations()) {
			Function* func = dynamic_cast<Function*>(d);
			if(func && func->getName() == name) {
				functions.insert(name,func);
				return func;
			}
		}
		if(parent)
			return parent->lookupFunction(name);
	}

	return functions.value(name);
}

bool Context::addVariable(Value* v)
{
	QString name=v->getName();
	if(!variables.contains(name)) {
		variables.insert(name,v);
		return true;
	}
	return false;
}

void Context::setVariable(Value* v)
{
	variables.insert(v->getName(),v);
}

Value* Context::lookupVariable(QString name,Variable::StorageClass_e& c)
{
	if(variables.contains(name)) {
		Value* v=variables.value(name);
		c=v->getStorageClass();
		return v;
	} else if(parent) {
		return parent->lookupVariable(name,c);
	} else {
		Value* v=new Value(); //undef
		v->setStorageClass(c);
		return v;
	}
}

void Context::addModule(Module* mod)
{
	modules.insert(mod->getName(),mod);
}

void Context::addFunction(Function* func)
{
	functions.insert(func->getName(),func);
}

void Context::setArguments(QList<Value*> args, QList<Value*> params)
{
	for(int i=0; i<params.size(); i++) {
		Value* val=params.at(i);
		QString paramName=val->getName();
		for(int j=0; j<args.size(); j++) {
			Value* arg=args.at(j);
			QString argName=arg->getName();
			if((i==j && argName.isEmpty()) || argName==paramName) {
				if(arg->isDefined()) {
					val=arg;
					break;
				}
			}
		}
		variables.insert(paramName,val);
	}
}

QList<Value*> Context::getArguments()
{
	return arguments;
}

void Context::addArgument(Value* value)
{
	arguments.append(value);
}

void Context::clearArguments()
{
	arguments.clear();
}

Value* Context::getArgument(int index, QString name)
{
	//TODO make matchLast work for name ending with any digit
	bool matchLast = name.endsWith('1') || name.endsWith('2');

	return matchArgumentIndex(true,matchLast,index,name);
}

Value* Context::getArgumentDeprecated(int index, QString name, QString deprecated)
{
	Value* v = matchArgumentIndex(true,false,index,name);
	if(!v) {
		v = matchArgumentIndex(false,false,index,deprecated);
		if(v)
			output << "Warning '" << deprecated << "' parameter is deprecated use '" << name << "' instead\n";
	}

	return v;
}

QList<Value*> Context::getParameters()
{
	return parameters;
}

void Context::clearParameters()
{
	parameters.clear();
}

void Context::addParameter(Value* value)
{
	parameters.append(value);
}

void Context::setInputNodes(QList<Node*> value)
{
	inputNodes=value;
}

QList<Node*> Context::getInputNodes()
{
	return inputNodes;
}

void Context::setCurrentNodes(QList<Node*> value)
{
	currentNodes=value;
}

QList<Node*> Context::getCurrentNodes()
{
	return currentNodes;
}

void Context::addCurrentNode(Node* value)
{
	currentNodes.append(value);
}

Value* Context::getArgumentSpecial(QString name)
{
	Value* v=matchArgument(false,false,name);
	if(v && v->getStorageClass()==Variable::Special)
		return v;

	return NULL;
}

Value* Context::matchArgumentIndex(bool allowChar,bool matchLast, int index, QString name)
{
	if(index >= arguments.size())
		return NULL;

	Value* arg = arguments.at(index);
	QString argName = arg->getName();
	if(argName.isEmpty() || match(allowChar,matchLast,argName,name))
		return arg;

	return matchArgument(allowChar,matchLast,name);
}

Value* Context::matchArgument(bool allowChar,bool matchLast, QString name)
{
	foreach(Value* namedArg,arguments) {
		QString namedArgName = namedArg->getName();
		if(match(allowChar,matchLast,namedArgName,name))
			return namedArg;
	}

	return NULL;
}

bool Context::match(bool allowChar,bool matchLast, QString a,QString n)
{
	if(allowChar) {
		if(matchLast&&a.length()==2)
			return a.left(1)==n.left(1) && a.right(1)==n.right(1);
		if(!matchLast&&a.length()==1)
			return a.left(1)==n.left(1);
	}
	return a==n;
}
