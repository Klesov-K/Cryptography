#include "stdafx.h"
#include "Trace.h"

void GetModulePath(WCHAR *moduleName) {
	GetModuleFileNameW(NULL, moduleName, 512);	
}

//static LPWSTR logPath = GetModulePath();
std::wstring logFile(L"logFile.txt");
inline void writeLog(ATL::CAtlFile &f, std::wstring path, const std::wstring &str) {
	//WCHAR logPath[512];
	//GetModulePath(logPath);
	auto res = f.Create(path.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		static_cast<LPSECURITY_ATTRIBUTES>(NULL),
		NULL);
	if (res != S_OK) {
		auto e = GetLastError();
		throw(e);
	}
	
	ULONGLONG fLen;
	res = f.GetSize(fLen);
	if (res != S_OK) {
		auto e = GetLastError();
		throw(e);
	}
	auto result = f.Seek(fLen);
	if (result != S_OK) {
		auto e = GetLastError();
		throw(e);
	}
	// length = (wchar_t = 2 байта) * длина строки
	auto hres = f.Write(str.c_str(), sizeof(wchar_t) * static_cast<ULONG>(size(str)));
	if (hres != S_OK) {
		auto e = GetLastError();
		throw(e);
		// Постараться исправить ошибку, мб открыть новый файл. Чтобы процесс шифровани не прекратился
	}
	f.Close();
}


void printError(const std::wstring &str) {
	ATL::CAtlFile f;
	writeLog(f, logFile, str);

}
void printNormal(const std::wstring &str) {
	ATL::CAtlFile f;
	writeLog(f, logFile, str);
}

