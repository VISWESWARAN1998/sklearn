// SWAMI KARUPPASWAMI THUNNAI

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>
#include "json.h"

using json = nlohmann::json;

template <typename D, typename T>
class noob_pandas
{
private:
	std::vector<std::vector<D>> X;
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
			if (typeid(D).name() == typeid(std::string).name())
			{
				D x_val = j[std::to_string(i)]["X"];
				std::vector<D> independent;
				independent.push_back(x_val);
				X.push_back(independent);
			}
			else
			{
				std::vector<D> independent = j[std::to_string(i)]["X"];
				X.push_back(independent);
			}
			T dependent = j[std::to_string(i)]["y"];
			y.push_back(dependent);
		}
	}

	std::vector<std::vector<D>> get_X()
	{
		return X;
	}

	std::vector<T> get_y()
	{
		return y;
	}
};
