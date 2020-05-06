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

#endif /* defined PORTS_H. */
