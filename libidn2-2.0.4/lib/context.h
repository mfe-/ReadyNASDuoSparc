/* context.h - check contextual rule on label
   Copyright (C) 2011-2017 Simon Josefsson

   Libidn2 is free software: you can redistribute it and/or modify it
   under the terms of either:

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version.

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version.

   or both in parallel, as here.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdbool.h>

int _idn2_contextj_rule (const uint32_t * label, size_t llen, size_t pos) _GL_ATTRIBUTE_PURE;

int _idn2_contexto_rule (const uint32_t * label, size_t llen, size_t pos) _GL_ATTRIBUTE_PURE;

bool _idn2_contexto_with_rule (uint32_t cp) _GL_ATTRIBUTE_CONST;
