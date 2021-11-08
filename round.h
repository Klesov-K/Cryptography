#pragma once
#include <vector>


struct keySize {
	UCHAR* key;
	UCHAR size;
	keySize(UCHAR* k, UCHAR s) : key(k), size(s) {}
};

//class clearKey {
//	clearKey() : cK_1(K_1, 16), cK_2(K_2, 16) {}
//	~clearKey() {
//		wipeK(cK_1);
//	}
//private:
//	keySize cK_1; //Вспомогательный ключ 1
//	keySize cK_2; //Вспомогательный ключ 2
//	//keySize cK;    // Раундовые ключи(10)
//};

constexpr auto b_size = 16;
typedef uint8_t vect[b_size];
// Вспомогательный ключ, при условии что последний блок полный длиный
//static UCHAR K_1[16];
// Вспомогательный ключ, если последний блок неполной длины
//static UCHAR K_2[16];
//
// Ксорим блок ОТ с предыдущим ШТ и вспомогателным ключом
//
void xorLastBlockK1(); 
void xorLastBlockK2();
//
// Ксорим блок ОТ с предыдущим ШТ
//
void xorAB();
//
// Читаем блок текста из файла
//
void readBlock(ATL::CAtlFile&, UCHAR, UCHAR);
//
// Обнуляем память a[] для чтения блока
//
void clearbBlock();
//
// Проверяем, не равен ли размер файла нулю, иначе нет смысла шифровать        // Уточнить этот момент!
//
bool checNullSizeFile(ATL::CAtlFile&);
//
// Открываем файл для шифрования
//
bool openFile(ATL::CAtlFile&, std::wstring&);
//
// Читаем из консоли название файла для шифрования
//
void readFileName(std::wstring&);
//
//Генерируем первый вспомогательный ключ
//
void supportKey_1();
//
//Генерируем второй вспомогательный ключ
//
void supportKey_2();

static void X(const uint8_t*, const uint8_t*, uint8_t);

// S - преобразование
void S(const uint8_t*, uint8_t*);

// Обратное преобразование S
void Reverse_S(const uint8_t*, uint8_t*);

// Умножение в поле GF(2^)
unsigned char mult(unsigned char, unsigned char);

// R преобразование
void R(unsigned char* data);

// Обратное преобразование R
void Reverse_R(unsigned char* data);

// L преобразование
void L(const unsigned char* in_data, unsigned char* out_data);

// Обратное преобразование L
void Reverse_L(const unsigned char* in_data, unsigned char* out_data);

constexpr void gen_C();

void reverse_key();

void gen_K();

void read_key();

void reverse_block();

//void read_text_block();

void encrypt_block();

void decrypt_block();

	
			
	



