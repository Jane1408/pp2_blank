#pragma once
#include <iostream>
#include <vector>

#include "BankClient.h"

class CBankClient;

class CBank
{
public:
	CBank(PrimitiveType type);
	~CBank();
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	size_t GetClientsCount() const;
	HANDLE* GetClientsHandles() const;
private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;
	std::shared_ptr<Primitives> m_syncPrimitives;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations(CBankClient const &client);
};