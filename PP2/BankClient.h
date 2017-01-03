#pragma once
#include <Windows.h>
#include "Bank.h"

class CBank;

class CBankClient
{
public:
	unsigned int GetId();
	~CBankClient() = default;
private:
	CBankClient(CBank *bank, unsigned int id, Primitives *syncPrimitives);
	static unsigned int GetSleepDuration(CBankClient *client);
	static unsigned int GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

	CBank *m_bank;
	unsigned m_id;

	static std::function<void(CBankClient*)> GetSyncMethodFunc(PrimitiveType type);

	friend CBank;
	
	HANDLE m_handle;
	Primitives *m_syncPrimitives = nullptr;
};