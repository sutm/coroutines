// awaitables.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <thread>
#include <future>
#include <iostream>
#include <experimental\resumable>
#include <experimental\generator>

std::future<int> sum_async(int x, int y)
{
	using namespace std::chrono;

	return std::async([x, y]
		{
			std::this_thread::sleep_for(2s);
			return x + y;
		});
}

std::future<void> call_sum_async(int x, int y)
{
	std::cout << "** async func - before call" << std::endl;
	auto sum = await sum_async(x, y);
	std::cout << "** async func - after call" << std::endl;
}

int main()
{
	std::cout << "<< main func - before call" << std::endl;
	auto result = call_sum_async(7, 9);
	std::cout << "<< main func - after call" << std::endl;

	{
		using namespace std::chrono;
		std::cout << "<< main func - before sleep" << std::endl;
		std::this_thread::sleep_for(3s);
		std::cout << "<< main func - after sleep" << std::endl;
	}

	result.get();
	std::cout << "<< main func - after get" << std::endl;

	return 0;
}