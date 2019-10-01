// SWAMI KARUPPASWAMI THUNNAI

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "json.h"

using json = nlohmann::json;

template <typename T>
class noob_pandas
{
private:
	std::vector<std::vector<double>> X;
	std::vector<T> y;

public:
	noob_pandas(std::string data_set)
	{
		std::ifstream file;
		file.open(data_set);
		if (!file.is_open()) throw "Dataset cannot be opened!";
		json j;
		file >> j;
		file.close();
		unsigned long int max_index = j["max_index"];
		for (unsigned long int i = 0; i < max_index; i++)
		{
			std::vector<double> independent = j[std::to_string(i)]["X"];
			X.push_back(independent);
			T dependent = j[std::to_string(i)]["y"];
			y.push_back(dependent);
		}
	}

	std::vector<std::vector<double>> get_X()
	{
		return X;
	}

	std::vector<T> get_y()
	{
		return y;
	}
};
