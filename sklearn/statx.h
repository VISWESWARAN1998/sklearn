// SWAMI KARUPPASWAMI THUNNAI

/*
Minimalistic statistics library (ALPHA STAGE - UNTESTED)
Taken from: https://github.com/VISWESWARAN1998/statx
*/

#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<typeinfo>
#include<cmath>

/*
SOME GOLDEN RULES:
------------------
1.	Don't let the goat(variable) to stay longer in your garden(cpu) it will eat
all the grasses(memory). => Keep the persistance of variable as low as possible.
2.	You don't give strange names to your kids so, don't give strange names to
your goats(variables). => Naming of variable should be done with care.
3.	20% of the code will consume 80% of time, optimzing the 20% of the code
will reduce 80% running time. => The Pareto principle
4.	20% of the code will do 80% of the work, optimizing the 20% of the code
will reduce 80% of running time. => The Pareto principle
5.  Math is about accuracy not robustness! and robustness is inversely
proportional to accuracy. You are needed to write a code which
gives accurate results for computation and that speaking expect exceptions
for faulty input and note that it is YOUR input which is faulty!
6.  Don't waste your time on writing clean code and don't save your time on writing
quick and drity code. Write maintainable code and ship it on time, make it
gorgeous later.
*/


//===================================================================
//                       FOR COMPUTING MEAN
//===================================================================

template<typename T>
class mean
{
public:
	T get_mean(std::vector<T> vec)
	{
		T total = 0;
		for (auto i : vec) total += i;
		auto average = total / vec.size();
		return average;
	}

};


//===================================================================
//                     FOR COMPUTING MEDIAN
//===================================================================
template<typename T>
class median
{
public:
	T get_median(std::vector<T> vec, bool sorted = false)
	{
		if (sorted == false)std::sort(vec.begin(), vec.end());
		auto vector_size = vec.size();
		if (vector_size == 1) return vec[0];
		// If the elements are odd return the middle element
		if (vector_size % 2 != 0) return vec[vector_size / 2];
		// If the elements count are even return the average of middle elements
		auto middle_element_one = vector_size / 2;
		auto middle_element_two = middle_element_one - 1;
		auto result = (vec[middle_element_one] + vec[middle_element_two]) / 2;
		return result;

	}
};


//====================================================================
//                     FOR COMPUTING THE MODE
//====================================================================

template<typename T>
class mode
{
public:
	T get_mode(std::vector<T> vec)
	{
		std::sort(vec.begin(), vec.end());
		std::map<T, unsigned long int> number_count_table;
		std::vector<T> elements_with_max_occurences;
		unsigned long int bigger_no = 1;
		for (auto i : vec)
		{
			if (number_count_table.find(i) == number_count_table.end()) number_count_table[i] = 1;
			else {
				auto current_count = number_count_table[i];
				current_count++;
				if (current_count>bigger_no) bigger_no = current_count;
				number_count_table[i] = current_count;
			}
		}
		if (bigger_no == 1) {
			return vec[0];
		}
		else
		{
			for (auto itr : number_count_table)
			{
				if (itr.second == bigger_no) elements_with_max_occurences.push_back(itr.first);
			}
			std::sort(elements_with_max_occurences.begin(), elements_with_max_occurences.end());
			return elements_with_max_occurences[0];
		}
	}
};



//========================================================================================
//                  FOR COMPUTING WEIGHTED MEAN
//========================================================================================

template <typename T>
class weighted_mean
{
private:
	unsigned long int vector_size;
public:
	T get_weighted_mean(std::vector<T> vec, std::vector<T> weights)
	{
		this->vector_size = vec.size();
		T numerator = 0;
		T total_weight = 0;
		for (unsigned long int i = 0; i<vector_size; i++)
		{
			T current_value = vec[i] * weights[i];
			numerator += current_value;
			total_weight += weights[i];
		}
		//std::cout << "NUMERATOR: " << numerator << "\n";
		//std::cout << "DENOMINATOR: " << summation_of_weights << "\n";
		return numerator / total_weight;
	}
};


//==========================================================================================
//                 FOR COMPUTING STANDARD DEVIATION
//==========================================================================================
template <typename T>
class standard_deviation : public mean<T>
{
private:
	T mean_value;
	T standard_deviation_value;
public:
	T get_standard_deviation(std::vector<T> vec)
	{
		this->mean_value = this->get_mean(vec);
		this->standard_deviation_value = 0;
		for (unsigned long int i = 0; i<vec.size(); ++i)
		{
			T powered_value = (vec[i] - this->mean_value) * (vec[i] - this->mean_value);
			this->standard_deviation_value += powered_value;
		}
		this->standard_deviation_value = sqrt(this->standard_deviation_value / vec.size());
		return this->standard_deviation_value;
	}
};


//==========================================================================================
//					FOR COMPUTING INTERQUARTILE RANGE
//==========================================================================================
/*
CALCULATING INTERQUARTILE RANGE FOR ODD NO OF ELEMENTS:
-------------------------------------------------------
Given Elements(E) = { 3,5,5,7,8,8,9,10,13,13,14,15,16,22,23}
Step 1: Sort it! Here we already have an sorted values
E = { 3, 5, 5, 7, 8, 8, 9, 10, 13, 13, 14, 15, 16, 22, 23 }
Step 2: Get the median for the values
Median (M) = 10
Step 3: The lower and the upper half
Elements which are left to the median are called left half and
to the right is right half
3 5 5 7 8 8 9   10    13 13 14 15 16 22 23
|___________|    |    |__________________|
LOWER HALF     MEDIAN   UPPER HALF
Step 4:
Q1 = median of left half
Q3 = median of right half
interquartile_range = Q3 - Q1
CALCULATING INTERQUARTILE RANGE FOR EVEN NO OF ELEMENTS:
--------------------------------------------------------
Step 1: Sort the array
Step 2: Get the median of the array
Step 3: Insert the median back to the array
Step 4: Follow odd no procedure since we have an array
of odd size.
*/
template <typename T>
class interquartile_range : public median<T>
{
private:
	bool is_odd_vector;
public:
	T get_interquartile_range(std::vector<T> vec, bool sorted = false)
	{
		if (sorted == false) std::sort(vec.begin(), vec.end());
		if (vec.size() % 2 != 0) is_odd_vector = true;
		else is_odd_vector = false;
		if (is_odd_vector)
		{
			return compute(vec);
		}
		else
		{
			unsigned long int middle_index = vec.size() / 2;
			T median_for_vector = this->get_median(vec);
			vec.insert(vec.begin() + middle_index, median_for_vector);
			return compute(vec);
		}
	}
private:
	T compute(std::vector<T> vec)
	{
		unsigned long int middle_element_index = vec.size() / 2;
		std::vector<T> lower_half;
		for (unsigned long int i = 0; i < middle_element_index; i++)
		{
			lower_half.push_back(vec[i]);
		}
		std::vector<T> upper_half;
		for (unsigned long int i = middle_element_index + 1; i<vec.size(); i++)
		{
			upper_half.push_back(vec[i]);
		}

		T q1 = this->get_median(lower_half);
		T q3 = this->get_median(upper_half);
		return q3 - q1;
	}
};


//================================================================================
//				FREQUENCY MAP TO VECTOR CONVERTER
//================================================================================

template <typename T>
class frequency_map_converter
{
public:
	void to_vector(std::map<T, unsigned long int> frequency_map, std::vector<T> &target_vector)
	{
		for (auto element : frequency_map)
		{
			for (unsigned long int i = 0; i < element.second; i++) target_vector.push_back(element.first);
		}
	}
};



//================================================================================
//				FOR CALCULATING THE RANGE
//================================================================================

/*
HOW TO CALCULATE THE RANGE
--------------------------
sorted input vector = { 1, 2, 3, 4}
greatest_value = 4
least_value = 1
range = greatest_value - least_value
i.e range = 3
*/

template <typename T>
class range
{
public:
	T get_range(std::vector<T> vec, bool sorted = false)
	{
		if (sorted == false) std::sort(vec.begin(), vec.end());
		T greatest_value = vec[vec.size() - 1];
		T least_value = vec[0];
		return greatest_value - least_value;
	}
};



//===============================================================================
//			FOR CALCULATING THE QUARTILE
//===============================================================================

template <typename T>
class quartile : public median<T>
{
public:
	std::map<std::string, T> get_quartile(std::vector<T> vec, bool sorted = false)
	{
		if (sorted == false) std::sort(vec.begin(), vec.end());
		std::map<std::string, T> result;
		result["q2"] = this->get_median(vec, sorted = true);
		unsigned long int middle_index = vec.size() / 2;
		std::vector<T> lower_half;
		for (unsigned long int i = 0; i<middle_index; i++)
		{
			lower_half.push_back(vec[i]);
		}
		result["q1"] = this->get_median(lower_half, sorted = true);
		// free the memory by clearning the lower half
		lower_half.clear();
		std::vector<T> upper_half;
		if (vec.size() % 2 != 0) middle_index++;
		for (unsigned long int i = middle_index; i<vec.size(); i++)
		{
			upper_half.push_back(vec[i]);
		}
		result["q3"] = this->get_median(upper_half, sorted = true);
		return result;
	}
};


// ============================ ACTIVATION FUNCTIONS  ============================

template <typename T>
class activation_function
{
public:
	T identity(T value)
	{
		return value;
	}

	long double sigmoid(T value)
	{
		T negative_value = -1 * value;
		long double exponential = exp(negative_value);
		long double result = 1 / (1 + exponential);
		return result;
	}

	long double tan_h(T value)
	{
		long double pos_exp = exp(value);
		long double neg_exp = exp(-1 * value);
		return (pos_exp - neg_exp) / (pos_exp + neg_exp);
	}

	int threshold(T value)
	{
		if (value < 0) return 0;
		else return 1;
	}
};


// =================== PROBABILITY ===========================

/* Exceptions in sample space */
class element_not_in_sample_space : public std::exception
{
	virtual const char* what() const throw()
	{
		return "An element is found in an Event but not found in the sample space";
	}
};

template <typename T>
class sample_space
{
private:
	std::set<std::vector<T>> *S;
public:
	// constructor to initialize the sample space
	sample_space(std::set<std::vector<T>> &S)
	{
		this->S = &S;
	}

	// Check if an element is present in the sample space
	const bool is_element_present(std::vector<T> element)
	{
		return S->find(element) != S->end();
	}

	// Returns the pointer to the sample space
	std::set<std::vector<T>>* get_sample_space() {
		return S;
	}

	// Probability for an event
	long double P(std::vector<T> e)
	{
		if (!is_element_present(e)) throw element_not_in_sample_space();
		long double result = (long double)e.size() / (long double)S->size();;
		return result;
	}

	// Probability for multiple events
	long double P(std::set<std::vector<T>> e)
	{
		for (auto i : e) if (!is_element_present(i)) throw element_not_in_sample_space();
		long double result = (long double)e.size() / (long double)S->size();;
		return result;
	}
};

/* PROBABILITY FUNCTIONS */

// Intersection
template<typename T>
void event_intersection(std::set<std::vector<T>> event1, std::set<std::vector<T>> event2, sample_space<T> S, std::set<std::vector<T>> &O)
{
	// Check if all elements are present in the sample space
	for (auto i : event1)if (!S.is_element_present(i)) throw element_not_in_sample_space();
	for (auto i : event2)if (!S.is_element_present(i)) throw element_not_in_sample_space();
	// Perform the intersection opertaion
	for (auto i : event1) if (event2.find(i) != event2.end()) O.insert(i);
}

// Union
template<typename T>
void event_union(std::set<std::vector<T>> event1, std::set<std::vector<T>> event2, sample_space<T> S, std::set<std::vector<T>> &O)
{
	// Check if all elements are present in the sample space
	for (auto i : event1)if (!S.is_element_present(i)) throw element_not_in_sample_space();
	for (auto i : event2)if (!S.is_element_present(i)) throw element_not_in_sample_space();
	// Perform the union operation
	for (auto i : event1) if (O.find(i) == O.end())O.insert(i);
	for (auto i : event2) if (O.find(i) == O.end())O.insert(i);
}

// Complement
template<typename T>
void event_complement(std::set<std::vector<T>> e, sample_space<T> S, std::set<std::vector<T>> &O)
{
	// Check if all elements are present in the sample space
	for (auto i : e)if (!S.is_element_present(i)) throw element_not_in_sample_space();
	// Perform the complement operation
	for (auto i = S.get_sample_space()->begin(); i != S.get_sample_space()->end(); ++i) if (e.find(*i) == e.end()) O.insert(*i);
}

// Check whether two events are disjoint
template<typename T>
bool is_disjoint(sample_space<T> S,std::set<std::vector<T>> event1, std::set<std::vector<T>> event2)
{
	// Check if all elements are present in the sample space
	for (auto i : event1)if (!S.is_element_present(i)) throw element_not_in_sample_space();
	for (auto i : event2)if (!S.is_element_present(i)) throw element_not_in_sample_space();
	// Check whether they are disjoint
	for (auto i : event1)
	{
		if (event2.find(i) != event2.end()) return false;
	}
	return true;
}
