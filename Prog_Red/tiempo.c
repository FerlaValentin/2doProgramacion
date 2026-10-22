#include "stdio.h"
#include "windows.h"

int main(){
	LARGE_INTEGER freq, antes, despues;

	QueryPerformanceCounter(&antes);
	printf("\nContador: %lld", antes.QuadPart);
	
	

	QueryPerformanceCounter(&despues);
	printf("\nContador: %lld", despues.QuadPart);
	printf("\nHan pasado: %lld", (despues.QuadPart - antes.QuadPart));
	QueryPerformanceFrequency(&freq);
	printf("\nHan pasado: %lld segundos", (despues.QuadPart - antes.QuadPart) / freq.QuadPart);

	return 0;
}