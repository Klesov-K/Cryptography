#pragma once
#include "stdafx.h"
#include <random>
extern struct keySize;

//bool wipeK(keySize &data) {
//	for (UCHAR i = 0; i < data.size; ++i ) {
//		data.key[i] = static_cast<UCHAR>(0);
//	}
//}

void wipeK(keySize data);
//	for (UCHAR i = 0; i < data.size; ++i) {
//		data.key[i] = static_cast<UCHAR>(0);
//	}
//}
//void wipe() {
//	std::random_device rd;
//	std::mt19937 mersenne(rd());
//
//}
