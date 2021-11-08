#pragma once

#define BEGIN_TRACE() \
		try {

#define END_TRACE_AND_RETURN_1() \
	} \
	catch(...) \
	{ \
		std::cout<< "Unknown exception" << std::endl; \
		TRACE_ERROR(L"Unknown exception");\
		return 1; \
	}

//static void GetModulePath(LPWSTR& moduleName);
void printError(const std::wstring& str);
void printNormal(const std::wstring& str);
#define TRACE_ERROR(string) printError(string)
#define TRACE_NORMAL(string) printNormal(string)