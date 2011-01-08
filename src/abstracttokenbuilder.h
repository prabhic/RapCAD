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

#ifndef ABSTRACTTOKENBUILDER_H
#define ABSTRACTTOKENBUILDER_H

#include <QString>
#include <QChar>
#include <QDir>

class AbstractTokenBuilder
{
public:
	virtual ~AbstractTokenBuilder() {}
	virtual void buildIncludeStart()=0;
	virtual void buildIncludeFile(QString)=0;
	virtual void buildIncludePath(QString)=0;
	virtual void buildIncludeFinish()=0;
	virtual void buildUseStart()=0;
	virtual unsigned int buildUse(QString)=0;
	virtual void buildUseFinish()=0;
	virtual unsigned int buildModule()=0;
	virtual unsigned int buildFunction()=0;
	virtual unsigned int buildTrue()=0;
	virtual unsigned int buildFalse()=0;
	virtual unsigned int buildUndef()=0;
	virtual unsigned int buildConst()=0;
	virtual unsigned int buildParam()=0;
	virtual unsigned int buildIf()=0;
	virtual unsigned int buildAs()=0;
	virtual unsigned int buildElse()=0;
	virtual unsigned int buildFor()=0;
	virtual unsigned int buildReturn()=0;
	virtual unsigned int buildLessEqual()=0;
	virtual unsigned int buildGreatEqual()=0;
	virtual unsigned int buildEqual()=0;
	virtual unsigned int buildNotEqual()=0;
	virtual unsigned int buildAnd()=0;
	virtual unsigned int buildOr()=0;
	virtual unsigned int buildComponentwiseMultiply()=0;
	virtual unsigned int buildComponentwiseDivide()=0;
	virtual unsigned int buildOuterProduct()=0;
	virtual unsigned int buildLegalChar(unsigned int)=0;
	virtual unsigned int buildNumber(QString)=0;
	virtual unsigned int buildIdentifier(QString)=0;
	virtual void buildStringStart()=0;
	virtual void buildString(QChar)=0;
	virtual void buildString(QString)=0;
	virtual unsigned int buildStringFinish()=0;
	virtual void buildCommentStart()=0;
	virtual unsigned int buildComment(QString)=0;
	virtual void buildCommentFinish()=0;
	virtual void buildWhiteSpaceError()=0;
	virtual void buildFileStart(QDir)=0;
	virtual void buildFileFinish()=0;
};

#endif // ABSTRACTTOKENBUILDER_H