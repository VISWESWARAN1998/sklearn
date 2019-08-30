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
