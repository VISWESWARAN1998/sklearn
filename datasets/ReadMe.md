# Example for using the the _json_ datasets.

```c++
// SWAMI KARUPPASWAMI THUNNAI

#include <iostream>
#include "naive_bayes.h"
#include "noob_pandas.h"


int main()
{
	try {
		std::cout << "Loading dataset..\n";
		// For regression use double instead of unsiged long int
		noob_pandas<unsigned long int> dataset("mnist.json");
		std::cout << "Dataset loaded, model is training now!\n";
		gaussian_naive_bayes gnb(dataset.get_X(), dataset.get_y(), DEBUG);
		gnb.fit();
		gnb.save_model("model.json");
		std::cout << "Model has been trained!";
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
	}
}
```

_Note: All json files are generated automatically using a script. So would no typos and other human errors._