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
//	keySize cK_1; //��������������� ���� 1
//	keySize cK_2; //��������������� ���� 2
//	//keySize cK;    // ��������� �����(10)
//};

constexpr auto b_size = 16;
typedef uint8_t vect[b_size];
// ��������������� ����, ��� ������� ��� ��������� ���� ������ ������
//static UCHAR K_1[16];
// ��������������� ����, ���� ��������� ���� �������� �����
//static UCHAR K_2[16];
//
// ������ ���� �� � ���������� �� � �������������� ������
//
void xorLastBlockK1(); 
void xorLastBlockK2();
//
// ������ ���� �� � ���������� ��
//
void xorAB();
//
// ������ ���� ������ �� �����
//
void readBlock(ATL::CAtlFile&, UCHAR, UCHAR);
//
// �������� ������ a[] ��� ������ �����
//
void clearbBlock();
//
// ���������, �� ����� �� ������ ����� ����, ����� ��� ������ ���������        // �������� ���� ������!
//
bool checNullSizeFile(ATL::CAtlFile&);
//
// ��������� ���� ��� ����������
//
bool openFile(ATL::CAtlFile&, std::wstring&);
//
// ������ �� ������� �������� ����� ��� ����������
//
void readFileName(std::wstring&);
//
//���������� ������ ��������������� ����
//
void supportKey_1();
//
//���������� ������ ��������������� ����
//
void supportKey_2();

static void X(const uint8_t*, const uint8_t*, uint8_t);

// S - ��������������
void S(const uint8_t*, uint8_t*);

// �������� �������������� S
void Reverse_S(const uint8_t*, uint8_t*);

// ��������� � ���� GF(2^)
unsigned char mult(unsigned char, unsigned char);

// R ��������������
void R(unsigned char* data);

// �������� �������������� R
void Reverse_R(unsigned char* data);

// L ��������������
void L(const unsigned char* in_data, unsigned char* out_data);

// �������� �������������� L
void Reverse_L(const unsigned char* in_data, unsigned char* out_data);

constexpr void gen_C();

void reverse_key();

void gen_K();

void read_key();

void reverse_block();

//void read_text_block();

void encrypt_block();

void decrypt_block();

	
			
	



