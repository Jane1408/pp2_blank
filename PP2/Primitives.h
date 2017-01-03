#pragma once
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <Windows.h>

enum class PrimitiveType
{
	CRITICAL_SECTION,
	MUTEX,
	SEMAPHORE,
	EVENT,
	NO
};


struct Primitives
{
	PrimitiveType type;
	HANDLE hMutex;
	HANDLE hSemaphore;
	HANDLE hEvent;
	CRITICAL_SECTION critical_section;


	Primitives()
		: hMutex(CreateMutex(NULL, false, NULL))
		, hSemaphore(CreateSemaphore(NULL, 1, 1, NULL))
		, hEvent(CreateEvent(NULL, false, true, NULL))
	{
		InitializeCriticalSection(&critical_section);
	}
};