/** @file : ports.h
 *  @brief: This module defines interface for I/O bus register manipulation.
 *
 *  Copyright (C) 2020  Suraj Upadhyay <usuraj35@gmail.com>
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

#ifndef PORTS_H
#define PORTS_H

/* Read a byte from the specified port. */
unsigned char port_byte_in(unsigned short port);

/* Write a byte data to the specified port. */
void port_byte_out(unsigned short port, unsigned char data);

/* Read a word from the specified port. */
unsigned short port_word_in(unsigned short port);

/* Write a word data to the specified port. */
void port_word_out(unsigned short port, unsigned short data);

#endif /* !defined(PORTS_H). */
