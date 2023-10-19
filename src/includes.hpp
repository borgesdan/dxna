#include <vector>
#include <cstdint>
#include <limits>
#include <memory>

//
//Usar #define/#undef NOMINMAX para conflitos com max() e min()
//
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>