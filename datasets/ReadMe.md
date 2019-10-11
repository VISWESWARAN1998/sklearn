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

Training with dependent variables as strings:

```c++
// SWAMI KARUPPASWAMI THUNNAI

#include "noob_pandas.h"
#include "naive_bayes.h"
#include "preprocessing.h"

int main()
{
	// For classification use unsigned long int instead of double
	noob_pandas<std::string> dataset("dataset.json");
	std::vector<std::vector<double>> X = dataset.get_X();
	std::vector<std::string> y = dataset.get_y();
	LabelEncoder<std::string> encoder(y);
	std::vector<unsigned long int> y_encoded = encoder.fit_transorm();
	gaussian_naive_bayes gnb(X, y_encoded, NODEBUG);
	gnb.fit();
	std::map<unsigned long int, double> probabilities = gnb.predict({ 2.1, 3.5, 1.4, 0.2, 2.3 });
	for (auto i : probabilities)
	{
		std::cout << i.first << " => " << i.second << "\n";
	}
	gnb.save_model("irismodel.json");
}
```

_Note: All json files are generated automatically using a script. So would no typos and other human errors._