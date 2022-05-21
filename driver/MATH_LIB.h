

#ifndef LIB_MATH_LIB_H_
#define LIB_MATH_LIB_H_

#define SET_BIT(value, pos) (value |= (1U<< pos))
#define CLEAR_BIT(value, pos) (value &= (~(1U<< pos)))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)

#endif /* LIB_MATH_LIB_H_ */

