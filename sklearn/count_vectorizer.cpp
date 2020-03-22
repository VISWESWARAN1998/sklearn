// SWAMI KARUPPASWAMI THUNNAI

#include "count_vectorizer.h"
#include "porter2_stemmer.h"



template<typename T>
count_vectorizer<T>::count_vectorizer(std::vector<T> &sentences, unsigned long int max_features, bool to_stem)
{
	this->sentences = sentences;
	this->max_features = max_features;
	this->to_stem = to_stem;
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
					if (to_stem)
					{
						Porter2Stemmer::stem(word);
					}
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
			if (to_stem)
			{
				Porter2Stemmer::stem(word);
			}
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
std::vector<T> count_vectorizer<T>::tokenize(T sentence)
{
	std::vector<T> token_vector;
	T word = "";
	for (auto character : sentence)
	{
		if (character == ' ')
		{
			if (word != "")
			{
				if (to_stem)
				{
					Porter2Stemmer::stem(word);
				}
				token_vector.push_back(word);
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
		if (to_stem)
		{
			Porter2Stemmer::stem(word);
		}
		token_vector.push_back(word);
	}
	return token_vector;
}

template<typename T>
void count_vectorizer<T>::get_array()
{
	generate_tokens_array();
	generate_headers();
}

template<typename T>
std::vector<T> count_vectorizer<T>::get_headers()
{
	return header_values;
}


template<typename T>
std::vector<std::vector<unsigned long int>> count_vectorizer<T>::encodings()
{
	std::vector<std::vector<unsigned long int>> encodings_vector;
	for (T sentence : sentences)
	{
		std::vector<T> tokens = tokenize(sentence);
		std::vector<unsigned long int> token_count;
		for (T header_value : header_values)
		{
			unsigned long int count = std::count(tokens.begin(), tokens.end(), header_value);
			token_count.push_back(count);
		}
		encodings_vector.push_back(token_count);
	}
	return encodings_vector;
}

template<typename T>
std::vector<unsigned long int> count_vectorizer<T>::transform(T sentence)
{
	std::vector<T> tokens = tokenize(sentence);
	std::vector<unsigned long int> token_count;
	for (T header_value : header_values)
	{
		unsigned long int count = std::count(tokens.begin(), tokens.end(), header_value);
		token_count.push_back(count);
	}
	return token_count;
}


template class count_vectorizer<std::string>;
