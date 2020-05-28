/** @file : dt.h
 *  @brief: This module declares global and interrupt descriptor tables'
 *          initialization funciton.
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

#ifndef DT_H
#define DT_H

/* init_dt : Initializes and loads the Global Descriptor Table and
 * Interrupt Descriptor Table. */
void init_dt(void);

#endif /* !defined(DT_H). */
