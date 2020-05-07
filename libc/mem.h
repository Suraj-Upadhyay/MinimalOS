/** @file : mem.h
 *  @brief: This module declares memory utility functions.
 *
 *  Copyright (C) 2020  Suraj Upadhyay
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **/

#ifndef MEM_H
#define MEM_H

/* Copies _size_ bytes of data from src to dest
 * and returns the number of bytes acutally copied.
 */
int mem_cpy(char *dest, char *src, int size);

#endif /* !defined(MEM_H). */
