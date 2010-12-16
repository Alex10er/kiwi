// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include "TextWriter.hpp"
#include "kiwi/utils/modulo.hpp"

namespace kiwi{
namespace text{




TextWriter::TextWriter( AbstractTextContainer& container 
	, portIndex_t index )
{
	init(container, index);
}

TextWriter::TextWriter( core::Node::WriterInputPort& port )
{
	AbstractTextContainer* tc = dynamic_cast<AbstractTextContainer*>(
		port.connectedOutput()->subPort()->node() );
	
	if( tc ) init( *tc, port.connectedOutput()->subPort()->index() );
	else
	{
		Debug::error() 
			<< "TextWriter::constructor error:"
			<<" Unable to determine the Container type."
			<< endl();
	}
}

TextWriter::TextWriter( core::Node::WriterOutputPort& port )
{
	AbstractTextContainer* tc = dynamic_cast<AbstractTextContainer*>(
		port.subPort()->node() );
	
	if( tc ) init( *tc, port.subPort()->index() );
	else
	{
		Debug::error() 
			<< "TextWriter::constructor error:"
			<<" Unable to determine the Container type."
			<< endl();
	}
}

void TextWriter::init( AbstractTextContainer& container
	, portIndex_t portIndex )
{
	_container = &container;
	_currentLine = container.getLine(0);
	_currentLineNb = 0;
}

kiwi::uint32_t TextWriter::nbLines() const
{
	return _container->nbLines();
}

kiwi::uint32_t TextWriter::nbChars() const
{
	return _currentLine->size();
}

kiwi::uint32_t TextWriter::currentLine() const
{
	return _currentLineNb;
}

bool TextWriter::gotoLine(kiwi::int32_t lineNumber)
{
	lineNumber  =utils::modulo<int>( lineNumber, nbLines() );
	_currentLine = _container->getLine(lineNumber);
	if(_currentLine ) _currentLineNb = lineNumber;
}

bool TextWriter::gotoNextLine()
{
	assert(utils::modulo<int>( _currentLineNb + 1, nbLines() ) < nbLines() );
	gotoLine( utils::modulo<int>( _currentLineNb + 1, nbLines() ) );
}

bool TextWriter::gotoPreviousLine()
{
	assert(utils::modulo<int>( _currentLineNb + 1, nbLines() ) < nbLines() );
	gotoLine( utils::modulo<int>( _currentLineNb - 1, nbLines() ) );
}

bool TextWriter::endOfText() const // TODO this won't work abecause of the modulo
{
	return (_currentLineNb >= _container->nbLines() );
}

kiwi::string& TextWriter::getLine() const
{
	return *_currentLine;
}

kiwi::uint8_t TextWriter::getChar(int32_t charNumber) const
{
	return (*_currentLine)[charNumber];
}

void TextWriter::setChar(int32_t charNumber, kiwi::int8_t value)
{
	//ScopedBlockMacro(__scop, "TextWriter::setChar")
	// TODO: This is really dirty code... we'll have to change it someday..
	int diff = charNumber - _currentLine->size() ;
	if(diff >= 0)
	{
		//Debug::print() << "adding chars to the line" << endl();
		for(int i = 0; i < diff-1; ++i)
		{
			//Debug::print() << "x" <<endl();
			char space = ' ';
			(*_currentLine).append(&space,1);
		}
		(*_currentLine).append((char*)&value,1);
		return;
	}
	else
	{
		(*_currentLine)[charNumber] = value;
	}
}

StringIterator TextWriter::getStringIterator() const
{
	return StringIterator( 
		&((*_currentLine)[0])
		, &((*_currentLine)[_currentLine->size()-1]) 
		);
}

void TextWriter::insertLine( 
	const kiwi::string& newLineCopy
	, int position 
	, int tag )
{
//ScopedBlockMacro(__scop, "TextWriter::insertLine")

	uint32_t myNbLines = nbLines();
	if(position < 0) position = utils::modulo<int>(position, myNbLines+1 );
	//Debug::print() << ">> " << position<< "  " << myNbLines << endl();
	
	while( position-1 >= myNbLines )
	{
		_container->insertLine( kiwi::string(""), myNbLines++ );
		//Debug::print() << ">> " << position<< "  " << myNbLines << endl();
		
	}

	_container->insertLine( newLineCopy, position + tag);
	
}

void TextWriter::removeLine(kiwi::uint32_t position)
{
	uint32_t nbl = nbLines();
	if(position > nbl ) position = utils::modulo(position, nbl);
	Debug::print() << "TextWriter::removeLine " << position << endl();
	_container->removeLine(position);
}	

void TextWriter::reset() 
{
	_container->reset();
	_currentLineNb = 0;
}
	
	
}// namespace	
}// namespace	
