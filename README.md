# sklearn
Trying to implement Scikit Learn for Python in C++

#### Least Squares Regression

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
