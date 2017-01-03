#include "stdafx.h"
#include <iostream>
#include <string>
#include "Bank.h"
#include "BankClient.h"
#include <map>

void ShowUsage()
{
	std::cout << "::::::::A reminder to use the program with the key::::::::\n\n\n" << std::endl;
	std::cout << "when using the program with a data synchronization program \n will work properly without it - no" << std::endl;
	std::cout << "WARNINGS!!!!! Use with key !!!!! Use without a key \nfor informational purposes only !!!!! \n\n" << std::endl;
}

const std::map<std::string, PrimitiveType> PRIMITIVE_LIST =
{
	{ "mutex", PrimitiveType::MUTEX },
	{ "semaphore", PrimitiveType::SEMAPHORE },
	{ "critical section", PrimitiveType::CRITICAL_SECTION },
	{ "event", PrimitiveType::EVENT },
	{ "NAN", PrimitiveType::NO }
};

bool GetPrimitiveType(std::string const & stringType, PrimitiveType & type)
{
	if (PRIMITIVE_LIST.find(stringType) != PRIMITIVE_LIST.end())
	{
		type = PRIMITIVE_LIST.find(stringType)->second;
		return true;
	}
	return false;
}

PrimitiveType GetTypeSyncPrimitivesInConsole()
{
	std::string val;
	bool isAccepted = false;
	PrimitiveType type;
	while (!isAccepted)
	{
		std::cout << "Please enter whether you want to use synchronization primitives or not"
			<< " (critical section, mutex, semaphore, event or NAN ) : ";
		std::getline(std::cin, val);
		isAccepted = GetPrimitiveType(val, type);
		if (val == "help")
		{
			ShowUsage();
		}
		else if (!isAccepted)
		{
			std::cout << "You enter an incorrect key value. Try again" << std::endl;
		}
	}
	return type;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error! Usage program.exe <client number> " << std::endl;
		return EXIT_FAILURE;
	}
	PrimitiveType key;
	key = GetTypeSyncPrimitivesInConsole();
	size_t clientNumber = atoi(argv[1]);

	std::unique_ptr<CBank> bank = std::make_unique<CBank>(key);

	std::vector<CBankClient*> clients;

	for (size_t i = 0; i != clientNumber; ++i)
	{
		clients.push_back(bank->CreateClient());
	}

	while (true)
	{
		WaitForMultipleObjects(static_cast<DWORD>(bank->GetClientsCount()), bank->GetClientsHandles(), TRUE, INFINITE);
	}

	return 0;
}