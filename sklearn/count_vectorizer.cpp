// SWAMI KARUPPASWAMI THUNNAI

#include "count_vectorizer.h"


template<typename T>
void count_vectorizer<T>::generate_encodings()
{
	for (unsigned long int i = 0; i < header_values.size(); i++)
	{
		encoded_values[header_values[i]] = i;
	}
}

template<typename T>
count_vectorizer<T>::count_vectorizer(std::vector<T> &sentences, unsigned long int max_features)
{
	this->sentences = sentences;
	this->max_features = max_features;
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
void count_vectorizer<T>::generate_headers()
{
	if (max_features >= tokens.size())
	{
		for (auto token : tokens)
		{
			header_values.push_back(token.first);
		}
		std::sort(header_values.begin(), header_values.end());
		return;
	}
	while (tokens.size() > max_features)
	{
		for (unsigned long int min : max_values)
		{
			std::vector<T> matched_values;
			for (auto itr : tokens)
			{
				if (itr.second == min)
				{
					matched_values.push_back(itr.first);
				}
			}
			std::sort(matched_values.begin(), matched_values.end());
			if (matched_values.size() > 0)
			{
				// delete the last matched values
				tokens.erase(matched_values[matched_values.size() - 1]);
				break;
			}
		}
	}

	for (auto token : tokens)
	{
		header_values.push_back(token.first);
	}
	std::sort(header_values.begin(), header_values.end());
}

template<typename T>
void count_vectorizer<T>::get_array()
{
	generate_tokens_array();
	generate_headers();
	generate_encodings();
}

template<typename T>
std::vector<T> count_vectorizer<T>::get_headers()
{
	return header_values;
}

template<typename T>
std::map<T, unsigned long int> count_vectorizer<T>::encodings()
{
	return encoded_values;
}


template class count_vectorizer<std::string>;
