# sklearn
Trying to implement Scikit Learn for Python in C++

#### Least Squares Regression

**HEADERS NEEDED:** lsr.h and lsr.cpp

Creating new model and saving it

```c++
// SWAMI KARUPPASWAMI THUNNAI

#include "lsr.h"

int main()
{
	// X, y, print_debug messages
	simple_linear_regression slr({2, 3, 5, 7, 9}, {4, 5, 7, 10, 15}, DEBUG);
	slr.fit();
	std::cout << slr.predict(8);
	slr.save_model("model.txt");
}
```


Loading existing model

```c++
// SWAMI KARUPPASWAMI THUNNAI

#include "lsr.h"

int main()
{
	// X, y, print_debug messages
	simple_linear_regression slr("model.txt");
	std::cout << slr.predict(8);
}

```

**OUTPUT:**
![](static/slr.png)


#### STANDARDIZATION

**HEADERS NEEDED:** preprocessing.h, proecessing.cpp and statx.h

```c++
// SWAMI KARUPPASWAMI THUNNAI

#include <iostream>
#include "preprocessing.h"

int main()
{
	StandardScaler scaler({0, 0, 1, 1});
	std::vector<double> scaled = scaler.scale();
	// Scaled value and inverse scaling
	for (double i : scaled)
	{
		std::cout << i << " " << scaler.inverse_scale(i) << "\n";
	}
}
```


#### Classification - Gaussian Naive Bayes

Classification male - female using height, weight, foot size and saving the model.

**HEADERS / SOURCE NEEDED:** naive_bayes.h, naive_bayes.cpp, json.h

```c++
// SWAMI KARUPPASWAMI THUNNAI

#include "naive_bayes.h"

int main()
{
	gaussian_naive_bayes nb({ {6, 180, 12}, {5.92, 190, 11}, {5.58, 170, 12}, {5.92, 165, 10}, {5, 100, 6}, {5.5, 150, 8}, {5.42, 130, 7}, {5.75, 150, 9} }, { 0, 0, 0, 0, 1, 1, 1, 1 }, DEBUG);
	nb.fit();
	nb.save_model("model.json");
	std::map<unsigned long int, double> probabilities = nb.predict({ 6, 130, 8 });
	double male = probabilities[0];
	double female = probabilities[1];
	if (male > female) std::cout << "MALE";
	else std::cout << "FEMALE";
}
```

Loading a saved model,

```c++
// SWAMI KARUPPASWAMI THUNNAI

#include "naive_bayes.h"

int main()
{
	gaussian_naive_bayes nb(NODEBUG);
	nb.load_model("model.json");
	std::map<unsigned long int, double> probabilities = nb.predict({ 6, 130, 8 });
	double male = probabilities[0];
	double female = probabilities[1];
	if (male > female) std::cout << "MALE";
	else std::cout << "FEMALE";
}
```
