#include "stdafx.h"
#include "round.h"
#include "Wipe.h"

void wipeK(keySize data) {
	for (UCHAR i = 0; i < data.size; ++i) {
		data.key[i] = static_cast<UCHAR>(0);
	}
}
void wipe() {
	std::random_device rd;
	std::mt19937 mersenne(rd());

}