// lib: basic data structures and algorithms
// Copyright (C) 2015 - 2016  David Ulrich
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DULIB_LIB_H
#define DULIB_LIB_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint xcode;

enum {
	 X_SUCCESS
	,X_NULL_PARAM
	,X_ALLOC_FAILURE
	,X_LIST_UNDERFLOW
	,X_STACK_UNDERFLOW
	,X_QUEUE_UNDERFLOW
};

#endif // DULIB_LIB_H
