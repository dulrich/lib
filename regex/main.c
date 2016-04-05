// lib: basic data structures and algorithms
// Copyright (C) 2016  David Ulrich
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

#include "regex.h"

int main(int argc, char** argv) {
	struct Node* pattern;
	int pattern_length = 100;
	struct Match* match;

	if (argc != 3) {
		debug(L_PROD, "usage: regex <pattern> <input>");
		return X_MISSING_ARGS;
	}

	pattern = malloc(sizeof(struct Node) * pattern_length);

	pattern_create(pattern, &pattern_length, argv[1]);

	match = pattern_match(pattern, pattern_length, argv[2]);

	if (match == NULL) {
		debug(L_PROD, "no match found");
	}
	else {
		debug(L_PROD, "best match is (%d,%d): %.*s",
			match->pos_start,
			match->pos_cur,
			(match->pos_cur - match->pos_start + 1),
			(argv[2] + match->pos_start - 1));
	}

	free(match);
	free(pattern);

	debug(L_DBUG, "done");

	return 0;
}
