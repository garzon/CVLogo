#include "CostFunc/SiftCost.h"
#include "CostFunc/SiftCost_1.h"
#include "pso/pso.h"

using namespace std;

int main() {
	vector<string> trainingSet = { "1.jpeg", "2.jpeg", "3.jpeg", "4.jpeg" };
	SiftCost func1(trainingSet, "logo.jpeg");
	Pso<SiftCost> pso(func1);
	SiftParams best_params = pso.solve();
	cout << "cost: " << func1.costFunction(best_params) << endl;
	cout << best_params.toMat() << endl;
	cout << "ok" << endl;
	return 0;
}
