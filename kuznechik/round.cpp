#include "stdafx.h"
#include "round.h"
#include "C:\Users\Константин\Desktop\УНИВЕР\3 Курс\МП\Курсовая_Магма\Kuznechik\kuz_code\table.h"
#include "Wipe.h"

//// Вспомогательный ключ, при условии что последний блок полный длиный
UCHAR K_1[16];
//// Вспомогательный ключ, если последний блок неполной длины
UCHAR K_2[16];

//struct keySize {
//	UCHAR* key;
//	UCHAR size;
//	keySize(UCHAR* k, UCHAR s) : key(k), size(s) {}
//};

class clearKey{
	clearKey() : cK_1(K_1, 16), cK_2(K_2, 16) {}
	~clearKey() {
		wipeK(cK_1);
	}
private:
	keySize cK_1; //Вспомогательный ключ 1
	keySize cK_2; //Вспомогательный ключ 2
	//keySize cK;    // Раундовые ключи(10)
};

	const unsigned char l_vec[16] = {
		148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148,1 };


	const unsigned char Pi[256] = {
		0xfc, 0xee, 0xdd, 0x11, 0xcf, 0x6e, 0x31, 0x16, 0xfb, 0xc4, 0xfa, 0xda,
		0x23, 0xc5, 0x04, 0x4d, 0xe9, 0x77, 0xf0, 0xdb, 0x93, 0x2e, 0x99, 0xba,
		0x17, 0x36, 0xf1, 0xbb, 0x14, 0xcd, 0x5f, 0xC1, 0xF9, 0x18, 0x65, 0x5A,
		0xE2, 0x5C, 0xEF, 0x21, 0x81, 0x1C, 0x3C, 0x42, 0x8B, 0x01, 0x8E, 0x4F,
		0x05, 0x84, 0x02, 0xAE, 0xE3, 0x6A, 0x8F, 0xA0, 0x06, 0x0b, 0xED, 0x98,
		0x7F, 0xD4, 0xD3, 0x1F, 0xEB, 0x34, 0x2C, 0x51, 0xEA, 0xC8, 0x48, 0xAB,
		0xF2, 0x2A, 0x68, 0xA2, 0xFD, 0x3A, 0xCE, 0xCC, 0xB5, 0x70, 0x0e, 0x56,
		0x08, 0x0c, 0x76, 0x12, 0xBF, 0x72, 0x13, 0x47, 0x9C, 0xB7, 0x5D, 0x87,
		0x15, 0xA1, 0x96, 0x29, 0x10, 0x7B, 0x9A, 0xC7, 0xF3, 0x91, 0x78, 0x6F,
		0x9D, 0x9E, 0xB2, 0xB1, 0x32, 0x75, 0x19, 0x3D, 0xFF, 0x35, 0x8A, 0x7E,
		0x6D, 0x54, 0xC6, 0x80, 0xC3, 0xBD, 0x0D, 0x57, 0xDF, 0xF5, 0x24, 0xA9,
		0x3E, 0xA8, 0x43, 0xC9, 0xD7, 0x79, 0xD6, 0xF6, 0x7C, 0x22, 0xB9, 0x03,
		0xE0, 0x0f, 0xEC, 0xDE, 0x7A, 0x94, 0xB0, 0xBC, 0xDC, 0xE8, 0x28, 0x50,
		0x4E, 0x33, 0x0A, 0x4A, 0xA7, 0x97, 0x60, 0x73, 0x1E, 0x00, 0x62, 0x44,
		0x1A, 0xB8, 0x38, 0x82, 0x64, 0x9F, 0x26, 0x41, 0xAD, 0x45, 0x46, 0x92,
		0x27, 0x5E, 0x55, 0x2F, 0x8C, 0xA3, 0xA5, 0x7D, 0x69, 0xD5, 0x95, 0x3B,
		0x07, 0x58, 0xB3, 0x40, 0x86, 0xAC, 0x1D, 0xF7, 0x30, 0x37, 0x6B, 0xE4,
		0x88, 0xD9, 0xE7, 0x89, 0xE1, 0x1B, 0x83, 0x49, 0x4C, 0x3F, 0xF8, 0xFE,
		0x8D, 0x53, 0xAA, 0x90, 0xCA, 0xD8, 0x85, 0x61, 0x20, 0x71, 0x67, 0xA4,
		0x2D, 0x2B, 0x09, 0x5B, 0xCB, 0x9B, 0x25, 0xD0, 0xBE, 0xE5, 0x6C, 0x52,
		0x59, 0xA6, 0x74, 0xD2, 0xE6, 0xF4, 0xB4, 0xC0, 0xD1, 0x66, 0xAF, 0xC2,
		0x39, 0x4B, 0x63, 0xb6 };
	const unsigned char Reverse_Pi[256] = {
		0xA5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0, 0x54, 0xE6, 0x9E, 0x39,
		0x55, 0x7E, 0x52, 0x91, 0x64, 0x03, 0x57, 0x5A, 0x1C, 0x60, 0x07, 0x18,
		0x21, 0x72, 0xA8, 0xD1, 0x29, 0xC6, 0xA4, 0x3F, 0xE0, 0x27, 0x8D, 0x0C,
		0x82, 0xEA, 0xAE, 0xB4, 0x9A, 0x63, 0x49, 0xE5, 0x42, 0xE4, 0x15, 0xB7,
		0xC8, 0x06, 0x70, 0x9D, 0x41, 0x75, 0x19, 0xC9, 0xAA, 0xFC, 0x4D, 0xBF,
		0x2A, 0x73, 0x84, 0xD5, 0xC3, 0xAF, 0x2B, 0x86, 0xA7, 0xB1, 0xB2, 0x5B,
		0x46, 0xD3, 0x9F, 0xFD, 0xD4, 0x0F, 0x9C, 0x2F, 0x9B, 0x43, 0xEF, 0xD9,
		0x79, 0xB6, 0x53, 0x7F, 0xC1, 0xF0, 0x23, 0xE7, 0x25, 0x5E, 0xB5, 0x1E,
		0xA2, 0xDF, 0xA6, 0xFE, 0xAC, 0x22, 0xF9, 0xE2, 0x4A, 0xBC, 0x35, 0xCA,
		0xEE, 0x78, 0x05, 0x6B, 0x51, 0xE1, 0x59, 0xA3, 0xF2, 0x71, 0x56, 0x11,
		0x6A, 0x89, 0x94, 0x65, 0x8C, 0xBB, 0x77, 0x3C, 0x7B, 0x28, 0xAB, 0xD2,
		0x31, 0xDE, 0xC4, 0x5F, 0xCC, 0xCF, 0x76, 0x2C, 0xB8, 0xD8, 0x2E, 0x36,
		0xDB, 0x69, 0xB3, 0x14, 0x95, 0xBE, 0x62, 0xA1, 0x3B, 0x16, 0x66, 0xE9,
		0x5C, 0x6C, 0x6D, 0xAD, 0x37, 0x61, 0x4B, 0xB9, 0xE3, 0xBA, 0xF1, 0xA0,
		0x85, 0x83, 0xDA, 0x47, 0xC5, 0xB0, 0x33, 0xFA, 0x96, 0x6F, 0x6E, 0xC2,
		0xF6, 0x50, 0xFF, 0x5D, 0xA9, 0x8E, 0x17, 0x1B, 0x97, 0x7D, 0xEC, 0x58,
		0xF7, 0x1F, 0xFB, 0x7C, 0x09, 0x0D, 0x7A, 0x67, 0x45, 0x87, 0xDC, 0xE8,
		0x4F, 0x1D, 0x4E, 0x04, 0xEB, 0xF8, 0xF3, 0x3E, 0x3D, 0xBD, 0x8A, 0x88,
		0xDD, 0xCD, 0x0B, 0x13, 0x98, 0x02, 0x93, 0x80, 0x90, 0xD0, 0x24, 0x34,
		0xCB, 0xED, 0xF4, 0xCE, 0x99, 0x10, 0x44, 0x40, 0x92, 0x3A, 0x01, 0x26,
		0x12, 0x1A, 0x48, 0x68, 0xF5, 0x81, 0x8B, 0xC7, 0xD6, 0x20, 0x0A, 0x08,
		0x00, 0x4C, 0xD7, 0x74 };

	/*
	// Элементы поля через степени примитивного эл-та(x=2)
	const uint8_t elementsTable[256] = {
		1, 2, 4, 8, 16, 32, 64, 128, 195, 69, 138, 215, 109, 218, 119, 238,
		32, 62, 124, 248, 51, 102, 204, 91, 182, 175, 157, 249, 49, 98, 196, 75,
		150, 239, 29, 58, 116, 232, 19, 38, 76, 152, 243, 37, 74, 148, 235, 21,
		42, 84, 168, 147, 229, 9, 18, 36, 72, 144, 227, 5, 10, 20, 40, 80,
		160, 131, 197, 73, 146, 231, 13, 26, 52, 104, 208, 99, 198, 79, 158, 255,
		61,	122, 244, 43, 86, 172, 155, 245, 41, 82, 164, 139, 213, 105, 210,
		206, 95, 190, 191, 189, 185, 177, 161, 129, 193, 65, 130, 199, 77, 154, 247,
		45, 90, 180, 171, 149, 233, 17, 34, 68, 136, 211, 101, 202, 87, 174, 159,
		253, 57, 114, 228, 11, 22, 44, 88, 176, 163, 133, 201, 81, 162, 135, 205,
		89,	178,167, 141, 217, 113, 226, 7, 14, 28, 56, 112, 224, 3, 6, 12,
		24, 48, 96, 192, 67, 134, 207, 93, 186, 183, 173, 153, 241, 33, 66, 132,
		203, 85, 170, 151, 237, 25, 50, 100, 200, 83, 166, 143, 221, 121, 242, 39,
		78, 156, 251, 53, 106, 212, 107, 214, 111, 222, 127, 254, 63, 126, 252, 59,
		118, 236, 27, 54, 108, 216, 115, 230, 15, 30, 60, 120, 240, 35, 70, 140,
		219, 117, 234, 23, 46, 92, 184, 179, 165, 137, 209, 97, 194, 71, 142, 223,
		125, 250, 55, 110, 220, 123, 246, 47, 94, 188, 187, 181, 169, 145, 225, 1 };
		*/
		// XOR
	void X(const unsigned char* a, const unsigned char* b, unsigned char* c) {
		for (int i = 0; i < b_size; i++)
			c[i] = a[i] ^ b[i];
	}

	// S преобразование
	void S(const unsigned char* in_data, unsigned char* out_data) {
		int i;
		for (i = 0; i < b_size; i++)
			out_data[i] = Pi[in_data[i]];
	}

	void Reverse_S(const unsigned char* in_data, unsigned char* out_data) {
		int i;
		for (i = 0; i < b_size; i++)
			out_data[i] = Reverse_Pi[in_data[i]];
	}

	// умножение в поле GF(2^8)
	unsigned char mult(unsigned char a, unsigned char b) {
		unsigned char c = 0;
		/* uint8_t hi_bit; // старший бит
		 int i;
		 for (i = 0; i < 8; i++) {
		 if (b & 1)
		 c ^= a;
		 hi_bit = a & 0x80;
		 a <<= 1;
		 if (hi_bit)
		 a ^= 0xc3; // Полином x^8 + x^7 + x^6 + x + 1
		 b >>= 1;
		 }
		 */
		c ^= multTable[a * 256 + b];
		return c;
	}

	void R(unsigned char* data) {
		//int i;
		unsigned char a_15 = 0;
		vect tmp;
		for (int i = 1; i <= 16; ++i) {     // i >= 0
			if (i == 16) {
				a_15 ^= mult(data[i - 1], l_vec[i - 1]);
				break;
			}
			else
				tmp[i] = data[i - 1]; // <-- байты
			a_15 ^= mult(data[i - 1], l_vec[i - 1]);
		}
		tmp[0] = a_15;
		memcpy(data, tmp, b_size);
	}
	//void R(unsigned char* data) {
	//	//int i;
	//	unsigned char a_15 = 0;
	//	vect tmp;
	//	for (int i = 15; i >= 0; --i) {     // i >= 0
	//		if (i == 0) {
	//			a_15 ^= mult(data[i], l_vec[i]);
	//			break;
	//		}
	//		else	
	//			tmp[i] = data[i-1]; // <-- байты
	//		a_15 ^= mult(data[i], l_vec[i]);
	//	}
	//	tmp[0] = a_15;
	//	memcpy(data, tmp, b_size);
	//}


	void Reverse_R(unsigned char* data) {
		int i;
		unsigned char a_0;
		a_0 = data[0];
		vect tmp;
		for (i = 1; i < 16; i++) {
			if (i == 16) {
				a_0 ^= mult(tmp[i - 1], l_vec[i - 1]);
				break;
			}
			tmp[i - 1] = data[i]; // Двигаем все на старые места  -->
			a_0 ^= mult(tmp[i - 1], l_vec[i - 1]);
		}
		tmp[15] = a_0;
		memcpy(data, tmp, b_size);
	}

	// L преобразование
	void L(const unsigned char* in_data, unsigned char* out_data) {
		//int i;
		vect tmp;
		memcpy(tmp, in_data, b_size);
		for (int i = 0; i < 16; ++i)         // i: 0 to 16
			R(tmp);
		memcpy(out_data, tmp, b_size);
	}

	// обратное L преобразование
	void Reverse_L(const unsigned char* in_data, unsigned char* out_data) {
		int i;
		vect tmp;
		memcpy(tmp, in_data, b_size);
		for (i = 0; i < 16; i++)
			Reverse_R(tmp);
		memcpy(out_data, tmp, b_size);
	}

	// Итерационные константы
	//vect C[32] = {
	//{ 0x6e, 0xa2, 0x76, 0x72, 0x6c, 0x48, 0x7a, 0xb8, 0x5d, 0x27, 0xbd, 0x10, 0xdd, 0x84, 0x94, 0x01},
	//{ 0xdc, 0x87, 0xec, 0xe4, 0xd8, 0x90, 0xf4, 0xb3, 0xba, 0x4e, 0xb9, 0x20, 0x79, 0xcb, 0xeb, 0x02},
	//{ 0xb2, 0x25, 0x9a, 0x96, 0xb4, 0xd8, 0x8e, 0x0b, 0xe7, 0x69, 0x04, 0x30, 0xa4, 0x4f, 0x7f, 0x03},
	//{ 0x7b, 0xcd, 0x1b, 0x0b, 0x73, 0xe3, 0x2b, 0xa5, 0xb7, 0x9c, 0xb1, 0x40, 0xf2, 0x55, 0x15, 0x04},
	//{ 0x15, 0x6f, 0x6d, 0x79, 0x1f, 0xab, 0x51, 0x1d, 0xea, 0xbb, 0x0c, 0x50, 0x2f, 0xd1, 0x81, 0x05},
	//{ 0xa7, 0x4a, 0xf7, 0xef, 0xab, 0x73, 0xdf, 0x16, 0x0d, 0xd2, 0x08, 0x60, 0x8b, 0x9e, 0xfe, 0x06},
	//{ 0xc9, 0xe8, 0x81, 0x9d, 0xc7, 0x3b, 0xa5, 0xae, 0x50, 0xf5, 0xb5, 0x70, 0x56, 0x1a, 0x6a, 0x07},
	//{ 0xf6, 0x59, 0x36, 0x16, 0xe6, 0x05, 0x56, 0x89, 0xad, 0xfb, 0xa1, 0x80, 0x27, 0xaa, 0x2a, 0x08},
	//{ 0x98, 0xfb, 0x40, 0x64, 0x8a, 0x4d, 0x2c, 0x31, 0xf0, 0xdc, 0x1c, 0x90, 0xfa, 0x2e, 0xbe, 0x09},
	//{ 0x2f, 0xb2, 0x6c, 0x2c, 0x0f, 0x0a, 0xac, 0xd1, 0x99, 0x35, 0x81, 0xc3, 0x4e, 0x97, 0x54, 0x10},
	//{ 0x41, 0x10, 0x1a, 0x5e, 0x63, 0x42, 0xd6, 0x69, 0xc4, 0x12, 0x3c, 0xd3, 0x93, 0x13, 0xc0, 0x11},
	//{ 0xf3, 0x35, 0x80, 0xc8, 0xd7, 0x9a, 0x58, 0x62, 0x23, 0x7b, 0x38, 0xe3, 0x37, 0x5c, 0xbf, 0x12},
	//{ 0x9d, 0x97, 0xf6, 0xba, 0xbb, 0xd2, 0x22, 0xda, 0x7e, 0x5c, 0x85, 0xf3, 0xea, 0xd8, 0x2b, 0x13},
	//{ 0x54, 0x7f, 0x77, 0x27, 0x7c, 0xe9, 0x87, 0x74, 0x2e, 0xa9, 0x30, 0x83, 0xbc, 0xc2, 0x41, 0x14},
	//{ 0x3a, 0xdd, 0x01, 0x55, 0x10, 0xa1, 0xfd, 0xcc, 0x73, 0x8e, 0x8d, 0x93, 0x61, 0x46, 0xd5, 0x15},
	//{ 0x88, 0xf8, 0x9b, 0xc3, 0xa4, 0x79, 0x73, 0xc7, 0x94, 0xe7, 0x89, 0xa3, 0xc5, 0x09, 0xaa, 0x16},
	//{ 0xe6, 0x5a, 0xed, 0xb1, 0xc8, 0x31, 0x09, 0x7f, 0xc9, 0xc0, 0x34, 0xb3, 0x18, 0x8d, 0x3e, 0x17},
	//{ 0xd9, 0xeb, 0x5a, 0x3a, 0xe9, 0x0f, 0xfa, 0x58, 0x34, 0xce, 0x20, 0x43, 0x69, 0x3d, 0x7e, 0x18},
	//{ 0xb7, 0x49, 0x2c, 0x48, 0x85, 0x47, 0x80, 0xe0, 0x69, 0xe9, 0x9d, 0x53, 0xb4, 0xb9, 0xea, 0x19},
	//{ 0x5e, 0xa7, 0xd8, 0x58, 0x1e, 0x14, 0x9b, 0x61, 0xf1, 0x6a, 0xc1, 0x45, 0x9c, 0xed, 0xa8, 0x20},
	//{ 0x30, 0x05, 0xae, 0x2a, 0x72, 0x5c, 0xe1, 0xd9, 0xac, 0x4d, 0x7c, 0x55, 0x41, 0x69, 0x3c, 0x21},
	//{ 0x82, 0x20, 0x34, 0xbc, 0xc6, 0x84, 0x6f, 0xd2, 0x4b, 0x24, 0x78, 0x65, 0xe5, 0x26, 0x43, 0x22},
	//{ 0xec, 0x82, 0x42, 0xce, 0xaa, 0xcc, 0x15, 0x6a, 0x16, 0x03, 0xc5, 0x75, 0x38, 0xa2, 0xd7, 0x23},
	//{ 0x25, 0x6a, 0xc3, 0x53, 0x6d, 0xf7, 0xb0, 0xc4, 0x46, 0xf6, 0x70, 0x05, 0x6e, 0xb8, 0xbd, 0x24},
	//{ 0x4b, 0xc8, 0xb5, 0x21, 0x01, 0xbf, 0xca, 0x7c, 0x1b, 0xd1, 0xcd, 0x15, 0xb3, 0x3c, 0x29, 0x25},
	//{ 0xf9, 0xed, 0x2f, 0xb7, 0xb5, 0x67, 0x44, 0x77, 0xfc, 0xb8, 0xc9, 0x25, 0x17, 0x73, 0x56, 0x26},
	//{ 0x97, 0x4f, 0x59, 0xc5, 0xd9, 0x2f, 0x3e, 0xcf, 0xa1, 0x9f, 0x74, 0x35, 0xca, 0xf7, 0xc2, 0x27},
	//{ 0xa8, 0xfe, 0xee, 0x4e, 0xf8, 0x11, 0xcd, 0xe8, 0x5c, 0x91, 0x60, 0xc5, 0xbb, 0x47, 0x82, 0x28},
	//{ 0xc6, 0x5c, 0x98, 0x3c, 0x94, 0x59, 0xb7, 0x50, 0x01, 0xb6, 0xdd, 0xd5, 0x66, 0xc3, 0x16, 0x29},
	//{ 0x71, 0x15, 0xb4, 0x74, 0x11, 0x1e, 0x37, 0xb0, 0x68, 0x5f, 0x40, 0x86, 0xd2, 0x7a, 0xfc, 0x30},
	//{ 0x1f, 0xb7, 0xc2, 0x06, 0x7d, 0x56, 0x4d, 0x08, 0x35, 0x78, 0xfd, 0x96, 0x0f, 0xfe, 0x68, 0x31},
	//{ 0xad, 0x92, 0x58, 0x90, 0xc9, 0x8e, 0xc3, 0x03, 0xd2, 0x11, 0xf9, 0xa6, 0xab, 0xb1, 0x17, 0x32} };
	vect C[32];
	// Раундовые ключи
	vect K[10];
	// номера векторов констант (для генерации  С)

	const vect _c[32] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 26},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32} };


	unsigned char key[32];/* = { //Мастер-Ключ
	 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11, 0x22, 0x33,
	 0x44, 0x55, 0x66, 0x77, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
	 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef}; */

	 /*
	 uint8_t key[32] = {
	  0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc,
	  0xbb, 0xaa, 0x99, 0x88, 0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01,
	  0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
	  */
	unsigned char a[16];/* = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x00,0xff,0xee,0xdd,
	 0xcc,0xbb,0xaa,0x99,0x88 }; Блок открытого текста */

	unsigned char b[16] = { 0 }; // Блок зашифрованного текста
	

	// Итерационные константы 
	constexpr void gen_C() {
		for (int i = 0; i < 32; i++) {
			L(_c[i], C[i]);
		}
	}

	void reverse_key() {
		for (int i = 0; i < 8; i++) {
			unsigned char tmp = key[i];
			key[i] = key[15 - i];
			key[15 - i] = tmp;
		}
		for (int i = 16; i < 24; i++) {
			unsigned char tmp = key[i];
			key[i] = key[31 - (i - 16)];
			key[31 - (i - 16)] = tmp;
		}
	}
	/*
	void gen_K() {
		memcpy(K, key, 16);
		memcpy(K + 1, key + 16, 16);

		vect block_0; //
		vect block_1; // вспомогательные временные переменные для цикла развертки
		//vect tmp; //

		memcpy(block_0, K, 16);
		memcpy(block_1, K + 1, 16);
		vect clear_key;
		int cur_i = 0;
		for (int j = 0; j < 8; j += 2) {
			for (int i = cur_i; i < cur_i + 8; i++) {
				memcpy(clear_key, block_0, 16);
				// запись предыдущего промежуточного ключа
				X(block_0, C[i], block_0);
				S(block_0, block_0);
				L(block_0, block_0);
				X(block_0, block_1, block_0);
				memcpy(block_1, clear_key, 16);
				// запись текущего промежуточного ключа
			}
			cur_i += 8;
			memcpy(K + 2 + j, block_0, 16);
			memcpy(K + 3 + j, block_1, 16);
		}
	}
	*/

	void gen_F(const uint8_t* in_k1, const uint8_t* in_k2, uint8_t* out_k1, uint8_t* out_k2, uint8_t* iter_const) {
		vect internal;
		memcpy(out_k2, in_k1, b_size);

		X(in_k1, iter_const, internal);
		S(internal, internal);
		L(internal, internal);
		X(internal, in_k2, out_k1);
	}
	void gen_K() {
		gen_C();
		// предыдущая пара ключей
		uint8_t iter_1[b_size];
		uint8_t iter_2[b_size];
		memcpy(iter_1, key, b_size);
		memcpy(iter_2, key + 16, b_size);
		// текущая пара ключей
		uint8_t iter_3[b_size];
		uint8_t iter_4[b_size];

		// Первые два итерационных ключа равны паре мастер-ключа
		memcpy(K[0], key, b_size);
		memcpy(K[1], key + 16, b_size);



		for (int i = 0; i < 4; ++i) {

			gen_F(iter_1, iter_2, iter_3, iter_4, C[0 + 8 * i]);
			gen_F(iter_3, iter_4, iter_1, iter_2, C[1 + 8 * i]);
			gen_F(iter_1, iter_2, iter_3, iter_4, C[2 + 8 * i]);
			gen_F(iter_3, iter_4, iter_1, iter_2, C[3 + 8 * i]);
			gen_F(iter_1, iter_2, iter_3, iter_4, C[4 + 8 * i]);
			gen_F(iter_3, iter_4, iter_1, iter_2, C[5 + 8 * i]);
			gen_F(iter_1, iter_2, iter_3, iter_4, C[6 + 8 * i]);
			gen_F(iter_3, iter_4, iter_1, iter_2, C[7 + 8 * i]);
			memcpy(K[2 * i + 2], iter_1, b_size);
			memcpy(K[2 * i + 3], iter_2, b_size);
		}



	}

	//void smth_func() {
	//
	//	// предыдущая пара ключей
	//	//uint8_t iter_1[b_size];
	//	//uint8_t iter_2[b_size];
	//	//memcpy(iter_1, key, b_size);
	//	//memcpy(iter_2, key + 16, b_size);
	//
	//	uint8_t iter_1[] = { 0xdb, 0x31, 0x48, 0x53, 0x15, 0x69, 0x43, 0x43, 0x22, 0x8d, 0x6a, 0xef, 0x8c, 0xc7, 0x8c, 0x44 };
	//	uint8_t iter_2[] = { 0x3d, 0x45, 0x53, 0xd8, 0xe9, 0xcf, 0xec, 0x68, 0x15, 0xeb, 0xad, 0xc4, 0x0a, 0x9f, 0xfd, 0x04 };
	//	// текущая пара ключей
	//	uint8_t iter_3[b_size];
	//	uint8_t iter_4[b_size];
	//
	//	// Первые два итерационных ключа равны паре мастер-ключа
	//	memcpy(K[0], key, b_size);
	//	memcpy(K[1], key + 16, b_size);
	//
	//
	//
	//	for (int i = 0; i < 4; ++i) {
	//
	//		gen_F(iter_1, iter_2, iter_3, iter_4, C[8]);
	//		gen_F(iter_3, iter_4, iter_1, iter_2, C[9]);
	//		gen_F(iter_1, iter_2, iter_3, iter_4, C[10]);
	//		gen_F(iter_3, iter_4, iter_1, iter_2, C[11]);
	//		gen_F(iter_1, iter_2, iter_3, iter_4, C[12]);
	//		gen_F(iter_3, iter_4, iter_1, iter_2, C[13]);
	//		gen_F(iter_1, iter_2, iter_3, iter_4, C[14]);
	//		gen_F(iter_3, iter_4, iter_1, iter_2, C[15]);
	//		memcpy(K[2 * i + 2], iter_1, b_size);
	//		memcpy(K[2 * i + 3], iter_2, b_size);
	//	}
	//
	//
	//}

	/*struct deleter {
		deleter() : m_file(f) {};
		~deleter() {


		}


	private:
		std::string m_file;
	};
	*/
	inline void readKeyFile(ATL::CAtlFile f) {
		f.Seek(0);
		ULONG x = static_cast<ULONG>(32);
		auto hres = f.Read(key, static_cast<ULONG>(32));
		if (hres != S_OK) {
			TRACE_NORMAL(L"Ключ не удалось прочитать");
			throw(hres);
		}
		TRACE_NORMAL(L"Ключ успешно считан\r\n");
	}

	// Открываем файл с ключом, проверяем размер = 32 байт
	inline bool openReadFile(ATL::CAtlFile f, const LPCWSTR& path) {
		auto res = f.Create(path,
			GENERIC_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			static_cast<LPSECURITY_ATTRIBUTES>(NULL),
			NULL);
		if (res != S_OK) {
			//auto e = GetLastError();
			// TRACE_ERROR();
			//throw(e);
			return false;
		}
		// Проверяем размер файла
		ULONGLONG fLen;
		res = f.GetSize(fLen);
		if (res != S_OK) {
			auto e = GetLastError();
			// TRACE_ERROR();
			//throw(e);
			return false;
		}
		if (fLen != static_cast<ULONGLONG>(32)) {
			//TRACE_ERROR();
			std::cout << "Size of keyFile is not 256 B" << std::endl;
			std::cout << "Size of keyFile is: " << fLen << std::endl;
			return false;
		}
		TRACE_NORMAL(L"keyFile is open and it's size = 256 Bit \r\n");
		readKeyFile(f);
		f.Close();
		return true;
	}


	void read_key() {
		ATL::CAtlFile f;
		while (1) {
			std::cout << std::endl << "Key file: ";
			// Считываем название файла с ключом
			std::wstring path;
			std::wcin >> path;
			// Отрываем файл и проверяем размер = 256 бит
			auto res = openReadFile(f, path.c_str());
			if (!res) {
				std::cout << "Try once more." << std::endl;
				std::wcin.sync();
			}
			else
				break;
		}
		//deleter f;

		//readKeyFile(f);
		//reverse_key();
	}

	void reverse_block() {
		for (int i = 0; i < 8; i++) {
			unsigned char tmp = a[i];
			a[i] = a[15 - i];
			a[15 - i] = tmp;
		}
	}
	std::string s;

	//
	// Читаем из консоли название файла для шифрования
	//
	void readFileName(std::wstring &name) {
		std::cout << std::endl << "The file to be encrypted: ";
		// Считываем название файла 
		std::wcin >> name;
	}

	//
	// Открываем файл для шифрования
	//
	bool openFile(ATL::CAtlFile &f, std::wstring &path) {
		auto res = f.Create(path.c_str(),
			GENERIC_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			static_cast<LPSECURITY_ATTRIBUTES>(NULL),
			NULL);
		if (res != S_OK) {
			auto e = GetLastError();
			TRACE_ERROR(L"Open File for encrypt is Failed with error");
			return false;
		}
		return true;
	}
	//
	// Проверяем, не равен ли размер файла нулю, иначе нет смысла шифровать        // Уточнить этот момент!
	//
	bool checNullSizeFile(ATL::CAtlFile& f) {
		ULONGLONG len;
		f.GetSize(len);
		if (!len) {
			std::cout << "The size of file is NULL! \r\n";
			return false;
		}
		return true;
	}
	//
	// Обнуляем память a[] для чтения блока
	//
	void clearbBlock() {
		for (int i = 0; i < 16; ++i) 
			a[i] = static_cast<UCHAR>(NULL);
	}
	//
	// Читаем блок текста из файла
	//
	void readBlock(ATL::CAtlFile& f, UCHAR offset, UCHAR sizeBlock = 16) {
		auto hres = f.Seek(offset, NULL);
		if (hres != S_OK) {
			TRACE_ERROR(L"Ошибка в функции readBlock");
			throw(hres);
		}
		// Зануляем блок, на случай если последний блок текста будет неполным
		clearbBlock();
		f.Read(a, sizeBlock);
	}


	//void read_text_block() {
	//	std::string s1;
	//
	//	if (s.length() < 32)
	//		while (s.length() < 32)
	//			s.push_back(' ');
	//	char* first, * second;
	//	first = &s[0];
	//	int j = 1;
	//	for (int i = 0; i < 16; i++) {
	//		first = &s[j - 1];
	//		second = &s[j];
	//		j += 2;
	//		s1 = *first;
	//		s1 += *second;
	//		sscanf_s(s1.c_str(), "%hhX", &a[i]);
	//	}
	//	reverse_block();
	//
	//}

	//
	// ЗАШИФРОВАНИЕ блока
	//
	void encrypt_block() { 
		for (int i = 0; i < 9; i++) {
			X(a, K[i], a);
			S(a, a);
			L(a, a);
		}
		X(a, K[9], b);

	}

	//
	// Ксорим блок ОТ с предыдущим ШТ
	//
	void xorAB() {
		for (int i = 0; i < 16; ++i)
			a[i] ^= b[i];
	}
	//
	// Ксорим блок ОТ с предыдущим ШТ и вспомогателным ключом
	//
	void xorLastBlockK1() {
		for (int i = 0; i < 16; ++i)
			a[i] ^= b[i];
		for (int i = 0; i < 16; ++i)
			a[i] ^= K_1[i];
	}

	void xorLastBlockK2() {
		for (int i = 0; i < 16; ++i)
			a[i] ^= b[i];
		for (int i = 0; i < 16; ++i)
			a[i] ^= K_2[i];
	}

	void decrypt_block() { // РАСШИФРОВАНИЕ блока
		X(b, K[9], b);
		for (int i = 8; i >= 0; i--) {
			Reverse_L(b, b);
			Reverse_S(b, b);
			X(b, K[i], b);
		}
		memcpy(a, b, 16);
	}

	//
	// Выработка вспомогательных ключей
	//

	// Инициализирующая последовательность нулей для получение R
	UCHAR null[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	UCHAR R_support[16];
	
	constexpr UCHAR B[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0b10000111 };


	//
	// Генерируем первый вспомогательный ключ
	//
	void supportKey_1() {
		// Получаем R
		for (int i = 0; i < 9; i++) {
			X(null, K[i], null);
			S(null, null);
			L(null, null);
		}
		X(null, K[9], R_support);
		// Если старший бит (MSB1(R)) = 0
		if (!(R_support[0] & 0b10000000)) {
			for (int i = 0; i < 16; ++i) {
				// Если старший разряд равен 1, то прибавляем его к предыдущему разряду, чтобы 1 не потерялась. Если нет, то просто сдвигаем
				if ((i != 0) && (R_support[i] & 0b10000000))
					R_support[i - 1] += 0b0000001;
				R_support[i] <<= 1;
			}
		}
		// Если старший бит(MSB1(R)) = 1
		else {
			// Так же выполняем логический сдвиг, как и на предыдущем шаге и ксорим с B[]
			for (int i = 0; i < 16; ++i) {
				// Если старший разряд равен 1, то прибавляем его к предыдущему разряду, чтобы 1 не потерялась. Если нет, то просто сдвигаем
				if ((i != 0) && (R_support[i] & 0b10000000))
					R_support[i - 1] += 0b0000001;
				R_support[i] <<= 1;
			}
			R_support[15] ^= B[15];
		}
		//
		// Копируем значения из R в K_1
		//
		for (int i = 0; i < 16; ++i) {
			K_1[i] = R_support[i];
		}
	}


	//
	//Генерируем второй вспомогательный ключ
	//
	void supportKey_2() {
		// Генерируем первый вспомогательный ключ, чтобы из него получить второй
		supportKey_1();
		// Скопируем значения из K_1 в K_2, чтобы дальше производить вычисления наж K_2
		for (int i = 0; i < 16; ++i) {
			K_2[i] = K_1[i];
		}

		// Если старший бит (MSB1(K1)) = 0
		if (!(K_2[0] & 0b10000000)) {
			for (int i = 0; i < 16; ++i) {
				// Если старший разряд равен 1, то прибавляем его к предыдущему разряду, чтобы 1 не потерялась. Если нет, то просто сдвигаем
				if ((i != 0) && (K_2[i] & 0b10000000))
					K_2[i - 1] += 0b0000001;
				K_2[i] <<= 1;
			}
		}
		// Если старший бит(MSB1(K_1)) = 1
		else {
			// Так же выполняем логический сдвиг, как и на предыдущем шаге и ксорим с B[]
			for (int i = 0; i < 16; ++i) {
				// Если старший разряд равен 1, то прибавляем его к предыдущему разряду, чтобы 1 не потерялась. Если нет, то просто сдвигаем
				if ((i != 0) && (K_2[i] & 0b10000000))
					K_2[i - 1] += 0b0000001;
				K_2[i] <<= 1;
			}
			K_2[15] ^= B[15];
		}
	}
	
	 



