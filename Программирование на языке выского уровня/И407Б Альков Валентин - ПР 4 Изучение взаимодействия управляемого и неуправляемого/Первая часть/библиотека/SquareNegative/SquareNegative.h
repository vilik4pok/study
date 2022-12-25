#pragma once

#ifdef SQUARENEGATIVE_EXPORTS
#define SQUARENEGATIVE_API __declspec(dllexport)
#else
#define SQUARENEGATIVE_API __declspec(dllimport)
#endif

extern "C" SQUARENEGATIVE_API void SquareNegative(double* arr,  int size);
extern "C" SQUARENEGATIVE_API void ReadArray(double* arr,  int size);
extern "C" SQUARENEGATIVE_API void PrintArray(double* arr,  int size);
extern "C" SQUARENEGATIVE_API double getValue();

