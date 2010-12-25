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

/**
 * @file TextReader.hpp
 * @brief Reader for AbstractTextContainer based containers.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva) 
 */

#pragma once

#ifndef KIWI_TEXTREADER_HPP
#define KIWI_TEXTREADER_HPP

#include "kiwi/text/AbstractTextContainer.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/generic/ArrayIterator.hpp"
#include "kiwi/core/Node.hpp"

namespace kiwi{
namespace text{

typedef kiwi::generic::ArrayConstIterator<kiwi::int8_t> StringConstIterator;
	
class TextReader
{
public:
	TextReader( AbstractTextContainer& container, portIndex_t index );
	TextReader( core::Node::ReaderInputPort& port );
	TextReader( core::Node::ReaderOutputPort& port );

	typedef kiwi::int8_t char_t;
	
	kiwi::uint32_t nbLines() const;
	kiwi::uint32_t nbChars() const;

	const kiwi::text::Line& line(kiwi::int32_t lineNb) const {}//todo
	char_t getChar(int32_t charNumber) const;

/*
	LineConstIterator getLineIterator(
			kiwi::int32_t line
			, kiwi::int32_t lastLine
			, bool lock = false	 ) const;

	TextConstIterator getCharIterator(
			kiwi::int32_t firstline, kiwi::int32_t fCharPos 
			, kiwi::int32_t lastLine, kiwi::int32_t lCharPos
			, bool lock = false	 ) const;
*/
protected:
	AbstractTextContainer* _container;

private:
	void init( AbstractTextContainer& container, portIndex_t index );
};	
	
}// namespace	
}// namespace	

#endif
