/*
 * fonts.h
 *
 * Library of fonts
 * Large: 8x8
 */
#ifndef FONTS_H_
#define FONTS_H_


#include <avr/pgmspace.h>
#define FONTLENGTH 100
// Font 8x8 - Large


const unsigned char PROGMEM font[FONTLENGTH][8] = { //to use the oled_print_char add 32 to the numbers
	{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, //		0
	{0b00000000,0b00000110,0b01011111,0b01011111,0b00000110,0b00000000,0b00000000,0b00000000}, // !		1
	{0b00000000,0b00000111,0b00000111,0b00000000,0b00000111,0b00000111,0b00000000,0b00000000}, // "		2
	{0b00010100,0b01111111,0b01111111,0b00010100,0b01111111,0b01111111,0b00010100,0b00000000}, // #		3
	{0b00100100,0b00101110,0b01101011,0b01101011,0b00111010,0b00010010,0b00000000,0b00000000}, // $		4
	{0b01000110,0b01100110,0b00110000,0b00011000,0b00001100,0b01100110,0b01100010,0b00000000}, // %		5
	{0b00110000,0b01111010,0b01001111,0b01011101,0b00110111,0b01111010,0b01001000,0b00000000}, // &		6
	{0b00000100,0b00000111,0b00000011,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // '		7
	{0b00000000,0b00011100,0b00111110,0b01100011,0b01000001,0b00000000,0b00000000,0b00000000}, // (		8
	{0b00000000,0b01000001,0b01100011,0b00111110,0b00011100,0b00000000,0b00000000,0b00000000}, // )		9
	{0b00001000,0b00101010,0b00111110,0b00011100,0b00011100,0b00111110,0b00101010,0b00001000}, // *		10
	{0b00001000,0b00001000,0b00111110,0b00111110,0b00001000,0b00001000,0b00000000,0b00000000}, // +		11
	{0b00000000,0b10100000,0b11100000,0b01100000,0b00000000,0b00000000,0b00000000,0b00000000}, // ,		12
	{0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00000000,0b00000000}, // -		13
	{0b00000000,0b00000000,0b01100000,0b01100000,0b00000000,0b00000000,0b00000000,0b00000000}, // .		14
	{0b01100000,0b00110000,0b00011000,0b00001100,0b00000110,0b00000011,0b00000001,0b00000000}, // /		15
	{0b00111110,0b01111111,0b01011001,0b01001101,0b01111111,0b00111110,0b00000000,0b00000000}, // 0		16
	{0b01000010,0b01000010,0b01111111,0b01111111,0b01000000,0b01000000,0b00000000,0b00000000}, // 1		17
	{0b01100010,0b01110011,0b01011001,0b01001001,0b01101111,0b01100110,0b00000000,0b00000000}, // 2		18
	{0b00100010,0b01100011,0b01001001,0b01001001,0b01111111,0b00110110,0b00000000,0b00000000}, // 3		19
	{0b00011000,0b00011100,0b00010110,0b00010011,0b01111111,0b01111111,0b00010000,0b00000000}, // 4		20
	{0b00100111,0b01100111,0b01000101,0b01000101,0b01111101,0b00111001,0b00000000,0b00000000}, // 5		21
	{0b00111100,0b01111110,0b01001011,0b01001001,0b01111001,0b00110000,0b00000000,0b00000000}, // 6		22	
	{0b00000011,0b01100011,0b01110001,0b00011001,0b00001111,0b00000111,0b00000000,0b00000000}, // 7		23	
	{0b00110110,0b01111111,0b01001001,0b01001001,0b01111111,0b00110110,0b00000000,0b00000000}, // 8		24
	{0b00000110,0b01001111,0b01001001,0b01101001,0b00111111,0b00011110,0b00000000,0b00000000}, // 9		25
	{0b00000000,0b00000000,0b01101100,0b01101100,0b00000000,0b00000000,0b00000000,0b00000000}, // :		26
	{0b00000000,0b10100000,0b11101100,0b01101100,0b00000000,0b00000000,0b00000000,0b00000000}, // ;		27
	{0b00001000,0b00011100,0b00110110,0b01100011,0b01000001,0b00000000,0b00000000,0b00000000}, // <		28
	{0b00010100,0b00010100,0b00010100,0b00010100,0b00010100,0b00010100,0b00000000,0b00000000}, // =		29
	{0b00000000,0b01000001,0b01100011,0b00110110,0b00011100,0b00001000,0b00000000,0b00000000}, // >		30
	{0b00000010,0b00000011,0b01010001,0b01011001,0b00001111,0b00000110,0b00000000,0b00000000}, // ?		31
	{0b00111110,0b01111111,0b01000001,0b01011101,0b01011101,0b00011111,0b00011110,0b00000000}, // @		32
	{0b01111100,0b01111110,0b00010011,0b00010011,0b01111110,0b01111100,0b00000000,0b00000000}, // A		33
	{0b01000001,0b01111111,0b01111111,0b01001001,0b01001001,0b01111111,0b00110110,0b00000000}, // B		34
	{0b00011100,0b00111110,0b01100011,0b01000001,0b01000001,0b01100011,0b00100010,0b00000000}, // C		35
	{0b01000001,0b01111111,0b01111111,0b01000001,0b01100011,0b01111111,0b00011100,0b00000000}, // D		36
	{0b01000001,0b01111111,0b01111111,0b01001001,0b01011101,0b01000001,0b01100011,0b00000000}, // E		37
	{0b01000001,0b01111111,0b01111111,0b01001001,0b00011101,0b00000001,0b00000011,0b00000000}, // F		38
	{0b00011100,0b00111110,0b01100011,0b01000001,0b01010001,0b01110011,0b01110010,0b00000000}, // G		39
	{0b01111111,0b01111111,0b00001000,0b00001000,0b01111111,0b01111111,0b00000000,0b00000000}, // H		40
	{0b00000000,0b01000001,0b01111111,0b01111111,0b01000001,0b00000000,0b00000000,0b00000000}, // I		41
	{0b00110000,0b01110000,0b01000000,0b01000001,0b01111111,0b00111111,0b00000001,0b00000000}, // J		42
	{0b01000001,0b01111111,0b01111111,0b00001000,0b00011100,0b01110111,0b01100011,0b00000000}, // K		43
	{0b01000001,0b01111111,0b01111111,0b01000001,0b01000000,0b01100000,0b01110000,0b00000000}, // L		44
	{0b01111111,0b01111111,0b00000110,0b00001100,0b00000110,0b01111111,0b01111111,0b00000000}, // M		45
	{0b01111111,0b01111111,0b00000110,0b00001100,0b00011000,0b01111111,0b01111111,0b00000000}, // N		46
	{0b00011100,0b00111110,0b01100011,0b01000001,0b01100011,0b00111110,0b00011100,0b00000000}, // O		47
	{0b01000001,0b01111111,0b01111111,0b01001001,0b00001001,0b00001111,0b00000110,0b00000000}, // P		48
	{0b00011110,0b00111111,0b00100001,0b01110001,0b01111111,0b01011110,0b00000000,0b00000000}, // Q		49
	{0b01000001,0b01111111,0b01111111,0b00011001,0b00111001,0b01101111,0b01000110,0b00000000}, // R		50
	{0b00100110,0b01100111,0b01001101,0b01011001,0b01111011,0b00110010,0b00000000,0b00000000}, // S		51
	{0b00000011,0b01000001,0b01111111,0b01111111,0b01000001,0b00000011,0b00000000,0b00000000}, // T		52
	{0b01111111,0b01111111,0b01000000,0b01000000,0b01111111,0b01111111,0b00000000,0b00000000}, // U		53
	{0b00011111,0b00111111,0b01100000,0b01100000,0b00111111,0b00011111,0b00000000,0b00000000}, // V		54
	{0b01111111,0b01111111,0b00110000,0b00011000,0b00110000,0b01111111,0b01111111,0b00000000}, // W		55
	{0b01100011,0b01110111,0b00011100,0b00001000,0b00011100,0b01110111,0b01100011,0b00000000}, // X		56
	{0b00000111,0b01001111,0b01111000,0b01111000,0b01001111,0b00000111,0b00000000,0b00000000}, // Y		57
	{0b01100111,0b01110011,0b01011001,0b01001101,0b01000111,0b01100011,0b01110001,0b00000000}, // Z		58
	{0b00000000,0b01111111,0b01111111,0b01000001,0b01000001,0b00000000,0b00000000,0b00000000}, // [		59
	{0b00000001,0b00000011,0b00000110,0b00001100,0b00011000,0b00110000,0b01100000,0b00000000}, // "\"	60	
	{0b00000000,0b01000001,0b01000001,0b01111111,0b01111111,0b00000000,0b00000000,0b00000000}, // ]		61
	{0b00001000,0b00001100,0b00000110,0b00000011,0b00000110,0b00001100,0b00001000,0b00000000}, // ^		62
	{0b10000000,0b10000000,0b10000000,0b10000000,0b10000000,0b10000000,0b10000000,0b10000000}, // _		63
	{0b00000000,0b00000000,0b00000011,0b00000111,0b00000100,0b00000000,0b00000000,0b00000000}, // `		64
	{0b00100000,0b01110100,0b01010100,0b01010100,0b00111100,0b01111000,0b01000000,0b00000000}, // a		65
	{0b01000001,0b00111111,0b01111111,0b01000100,0b01000100,0b01111100,0b00111000,0b00000000}, // b		66
	{0b00111000,0b01111100,0b01000100,0b01000100,0b01101100,0b00101000,0b00000000,0b00000000}, // c		67
	{0b00110000,0b01111000,0b01001000,0b01001001,0b00111111,0b01111111,0b01000000,0b00000000}, // d		68
	{0b00111000,0b01111100,0b01010100,0b01010100,0b01011100,0b00011000,0b00000000,0b00000000}, // e		69
	{0b01001000,0b01111110,0b01111111,0b01001001,0b00000011,0b00000010,0b00000000,0b00000000}, // f		70
	{0b10011000,0b10111100,0b10100100,0b10100100,0b11111000,0b01111100,0b00000100,0b00000000}, // g		71
	{0b01000001,0b01111111,0b01111111,0b00001000,0b00000100,0b01111100,0b01111000,0b00000000}, // h		72
	{0b00000000,0b01000100,0b01111101,0b01111101,0b01000000,0b00000000,0b00000000,0b00000000}, // i		73
	{0b01000000,0b11000100,0b10000100,0b11111101,0b01111101,0b00000000,0b00000000,0b00000000}, // j		74
	{0b01000001,0b01111111,0b01111111,0b00010000,0b00111000,0b01101100,0b01000100,0b00000000}, // k		75
	{0b00000000,0b01000001,0b01111111,0b01111111,0b01000000,0b00000000,0b00000000,0b00000000}, // l		76
	{0b01111100,0b01111100,0b00001100,0b00011000,0b00001100,0b01111100,0b01111000,0b00000000}, // m		77
	{0b01111100,0b01111100,0b00000100,0b00000100,0b01111100,0b01111000,0b00000000,0b00000000}, // n		78
	{0b00111000,0b01111100,0b01000100,0b01000100,0b01111100,0b00111000,0b00000000,0b00000000}, // o		79
	{0b10000100,0b11111100,0b11111000,0b10100100,0b00100100,0b00111100,0b00011000,0b00000000}, // p		80
	{0b00011000,0b00111100,0b00100100,0b10100100,0b11111000,0b11111100,0b10000100,0b00000000}, // q		81
	{0b01000100,0b01111100,0b01111000,0b01000100,0b00011100,0b00011000,0b00000000,0b00000000}, // r		82
	{0b01001000,0b01011100,0b01010100,0b01010100,0b01110100,0b00100100,0b00000000,0b00000000}, // s		83
	{0b00000000,0b00000100,0b00111110,0b01111111,0b01000100,0b00100100,0b00000000,0b00000000}, // t		84
	{0b00111100,0b01111100,0b01000000,0b01000000,0b00111100,0b01111100,0b01000000,0b00000000}, // u		85
	{0b00011100,0b00111100,0b01100000,0b01100000,0b00111100,0b00011100,0b00000000,0b00000000}, // v		86
	{0b00111100,0b01111100,0b01100000,0b00110000,0b01100000,0b01111100,0b00111100,0b00000000}, // w		87	
	{0b01000100,0b01101100,0b00111000,0b00010000,0b00111000,0b01101100,0b01000100,0b00000000}, // x		88
	{0b10011100,0b10111100,0b10100000,0b10100000,0b11111100,0b01111100,0b00000000,0b00000000}, // y		89
	{0b01001100,0b01100100,0b01110100,0b01011100,0b01001100,0b01100100,0b00000000,0b00000000}, // z		90
	{0b00001000,0b00001000,0b00111110,0b01110111,0b01000001,0b01000001,0b00000000,0b00000000}, // {		91
	{0b00000000,0b00000000,0b00000000,0b01110111,0b01110111,0b00000000,0b00000000,0b00000000}, // |		92
	{0b01000001,0b01000001,0b01110111,0b00111110,0b00001000,0b00001000,0b00000000,0b00000000}, // }		93
	{0b00000010,0b00000011,0b00000001,0b00000011,0b00000010,0b00000011,0b00000001,0b00000000}, // ~		94
	{0b01100110,0b10000110,0b10110000,0b01110000,0b01110000,0b10110000,0b10000110,0b01100110}, // skull 95
	{0b00000000,0b01111110,0b01000010,0b01000010,0b01000010,0b01000010,0b01111110,0b00000000}, // box0	96
	{0b00000000,0b01111110,0b01111110,0b01111110,0b01111110,0b01111110,0b01111110,0b00000000}, // box1	97
	{0b11111111,0b10000000,0b10000000,0b10000000,0b10000000,0b10000000,0b10000000,0b10000000}, // corner1	98
	{0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b11111111}, // corner2	99
};
#endif
/*
00000000000000000000000000000000
00000000000000000000000000000000
00000000000000000000000000000000
00000000000000000001111111000000
00000000000000011110101111110000
00000000000001100000101011001100
00000000000010000000101001000010
00000000001100000000010110000010
00000000010000000000011001100001
00000000100000000000010011110001
00000000100000000000001010110001
00100001000000000000001010010001
01010010000000000110000101100010
01010010000100011000000100001100
10011110001011100010000001110000
11100010000100011100001110000000
00011110001000100001110000000000
00000010000101000110000000000000
00000010000010001100000000000000
00000001000000000010000000000000
00001001000000001101000000000000
*/