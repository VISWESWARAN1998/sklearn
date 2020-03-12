// SWAMI KARUPPASWAMI THUNNAI

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

template <typename T>
class count_vectorizer
{
private:
	std::vector<T> sentences;
	std::set<unsigned long int> max_values;
	std::map<T, unsigned long int> tokens;

	// Split all the sentences into unique tokens
	void generate_tokens_array();
public:
	count_vectorizer(std::vector<T> &sentences);
	void get_array();
};
