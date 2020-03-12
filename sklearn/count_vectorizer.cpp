// SWAMI KARUPPASWAMI THUNNAI

#include "count_vectorizer.h"


template<typename T>
count_vectorizer<T>::count_vectorizer(std::vector<T> &sentences)
{
	this->sentences = sentences;
}

template<typename T>
void count_vectorizer<T>::generate_tokens_array()
{
	for (T sentence : sentences)
	{
		T word = "";
		for (auto character : sentence)
		{
			if (character == ' ')
			{
				if (word != "")
				{
					if (tokens.find(word) == tokens.end())
					{
						tokens[word] = 1;
						max_values.insert(tokens[word]);
					}
					else
					{
						tokens[word] += 1;
						max_values.insert(tokens[word]);
					}
					word = "";
				}
			}
			else
			{
				word += character;
			}
		}
		if (word != "")
		{
			if (tokens.find(word) == tokens.end())
			{
				tokens[word] = 1;
				max_values.insert(tokens[word]);
			}
			else
			{
				tokens[word] += 1;
				max_values.insert(tokens[word]);
			}
		}
	}
}

template<typename T>
void count_vectorizer<T>::get_array()
{
	generate_tokens_array();
	for (auto i : max_values)
	{
		std::cout << i << "\n";
	}
}


template class count_vectorizer<std::string>;
