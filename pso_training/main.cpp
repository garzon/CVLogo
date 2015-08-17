#include "CostFunc/SiftCost.h"
#include "CostFunc/SiftCost_1.h"
#include "pso/pso.h"

using namespace std;

int main() {
	vector<string> trainingSet = { "d:/CVLogo/1.jpg", "d:/CVLogo/2.jpg", "d:/CVLogo/3.jpg", "d:/CVLogo/4.jpg" };
	SiftCost func1(trainingSet, "d:/CVLogo/logo.jpg");
	Pso<SiftCost> pso(func1);
	SiftParams best_params = pso.solve();
	cout << "cost: " << func1.costFunction(best_params) << endl;
	cout << best_params.toMat() << endl;
	return 0;
}