#include "stdafx.h"
#include "round.h"
#include <atlfile.h>
#include "Test.h"

// INIT PROCESS (генерируем сеансовые ключи)
void Init() {
	gen_C();
	read_key();
	gen_K();
}
/* // Создание файла по заданному адресу
static void CreateFileTest(const std::wstring& path) {
	const auto& fname = strings::build_wstring(path.c_str(), L"filename.txt");
	ATL::CAtlFile file;
	auto res = file.Create(fname.c_str(),
		GENERIC_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		static_cast<LPSECURITY_ATTRIBUTES>(NULL),
		NULL);
	if (res != S_OK) {
		auto e = GetLastError();
		THROW_ERROR(e);
	}

	return;
}
*/

//void TEST_S() {
//	//uint8_t in[] = { 0xff , 0xee , 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00 };
//	uint8_t in[] = { 0xb6, 0x6c, 0xd8, 0x88, 0x7d, 0x38, 0xe8, 0xd7, 0x77, 0x65, 0xae, 0xea, 0x0c, 0x9a, 0x7e, 0xfc };
//	uint8_t out[16];
//	
//	S(in, out);
//}
//
//void TEST_R() {
//	//uint8_t var[] = { 0x00 , 0x00 , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
//	//uint8_t var[] = { 0x94 , 0x00 , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
//	uint8_t var[] = { 0xa5 , 0x94 , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//	R(var);
//}
//
//void REVERSE_TEST_R() {
//	uint8_t var[] = { 0x00 , 0x00 , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
//	//uint8_t var[] = { 0x94 , 0x00 , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
//	Reverse_R(var);
//	
//}
// 
//void TEST_L() {
//	//uint8_t in[] = { 0x64 , 0xa5 , 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//	//uint8_t in[] = { 0xd4, 0x56, 0x58, 0x4d, 0xd0, 0xe3, 0xe8, 0x4c, 0xc3, 0x16, 0x6e, 0x4b, 0x7f, 0xa2, 0x89, 0x0d };
//
//	uint8_t in[] = { 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1 };
//
//	uint8_t out[16];
//
//	L(in, out);
//
//	
//}
//void TEST_REVERSE_L() {
//	uint8_t in[] = {0xd4, 0x56, 0x58, 0x4d, 0xd0, 0xe3, 0xe8, 0x4c, 0xc3, 0x16, 0x6e, 0x4b, 0x7f, 0xa2, 0x89, 0x0d};
//	uint8_t out[16];
//	
//	Reverse_L(in, out);
//}
//
//void TEST_gen_k() {
//	gen_K();
//}
//void TEST_gen_C() {
//
//	gen_C();
//}

//extern class clearKey;

int main() {
	BEGIN_TRACE();
	if (Test())
		std::cout << "Test is good" << std::endl;
	else throw(1);
	Init();

	clearKey k();
	

	// Файл, который будем шифровать
	std::wstring fileName;
	readFileName(fileName);
	ATL::CAtlFile f;
	auto res = f.Create(fileName.c_str(),
		GENERIC_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		static_cast<LPSECURITY_ATTRIBUTES>(NULL),
		NULL);
	if (res != S_OK) {
		auto e = GetLastError();
		TRACE_ERROR(L"Open File for encrypt is Failed with error");
		std::cout << "File opening error" << std::endl;
		return 1;
	}

	if (!checNullSizeFile(f)) {
		TRACE_ERROR(L"Размер файла для шифрования равен нулю");
		return 1;
	}
	// Размер файла
	ULONGLONG fileLength;
	f.GetSize(fileLength);
	UCHAR lenLastBlock = 16;
	if (fileLength % b_size != 0) {
		lenLastBlock = fileLength % b_size;
	}

	// Шифруем все блоки ОТ кроме последнего
	for (ULONGLONG offset = 0; offset < (fileLength - lenLastBlock); offset += b_size) {

		readBlock(f, static_cast<UCHAR>(offset), b_size);
		// Ксорим с предыдущим зашифрованным блоком
		xorAB();
		encrypt_block();
	}
	// Шифруем последний блок ОТ
	if (lenLastBlock == b_size) {
		readBlock(f, static_cast<UCHAR>(fileLength - b_size), b_size);
		supportKey_1();
		xorLastBlockK1();
		encrypt_block();
	}
	else {
		readBlock(f, static_cast<UCHAR>(fileLength - lenLastBlock), b_size);
		supportKey_2();
		xorLastBlockK2();
		encrypt_block();
	}
	f.Close();
	std::wcout << L"\r\nEncryption was successful" << std::endl;
	TRACE_NORMAL(L"Ширование прошло успешно\r\n");
	END_TRACE_AND_RETURN_1();
	return 0;
}