/*
  rexgen - a tool to create words based on regular expressions
  Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/


#ifndef SRC_LIBREXGEN_ITERATOR_TERMINALREGEXITERATOR_H_
#define SRC_LIBREXGEN_ITERATOR_TERMINALREGEXITERATOR_H_

#include <librexgen/iterator/iterator.h>
#include <librexgen/debug.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/simplestring.h>
#include <librexgen/state/invaliditeratoridexception.h>
#include <string.h>
#include <string>

class TerminalRegexIterator : public Iterator {
 public:
  TerminalRegexIterator(int _id, const wchar_t* _terminal, size_t elements)
          : Iterator(_id) {
    for (size_t idx = 0; idx < elements; ++idx) {
      terminal.append_widechar(_terminal[idx]);
    }
  }

  bool next() {
    const bool res = (getState() == resetted);
    setState(usable);
    return res;
  }

  void value(SimpleString* dst) const {
    dst->append(terminal);
  }

  bool hasNext() const { return getState() == resetted; }

  virtual void updateReferences(IteratorState* /* iterState */) {}
  virtual void updateAttributes(IteratorState* /* iterState */) {}

 private:
  SimpleString terminal;
};

#endif  // SRC_LIBREXGEN_ITERATOR_TERMINALREGEXITERATOR_H_
