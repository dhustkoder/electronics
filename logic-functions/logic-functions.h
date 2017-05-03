#ifndef LOGIC_FUNCTIONS_H_
#define LOGIC_FUNCTIONS_H_


typedef unsigned char (*LogicFunc) (unsigned char x, unsigned char y);


static inline unsigned char and(const unsigned char x, const unsigned char y)
{
	return x & y;
}


static inline unsigned char or(const unsigned char x, const unsigned char y)
{
	return x | y;
}


static inline unsigned char not(const unsigned char x)
{
	return ~x;
}


static inline unsigned char nand(const unsigned char x, const unsigned char y)
{
	return ~(x & y);
}


static inline unsigned char nor(const unsigned char x, const unsigned char y)
{
	return ~(x | y);
}


static inline unsigned char xor(const unsigned char x, const unsigned char y)
{
	return x ^ y;
}


static inline unsigned char xnor(const unsigned char x, const unsigned char y)
{
	return ~(x ^ y);
}


#endif

