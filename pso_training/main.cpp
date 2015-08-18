#include "CostFunc/SiftCost.h"
#include "CostFunc/SiftCost_1.h"
#include "pso/pso.h"

using namespace std;

int main() {
    vector<string> trainingSet = { "/home/garzon/1.jpg", "/home/garzon/2.jpg", "/home/garzon/3.jpg", "/home/garzon/4.jpg" };
    SiftCost_1 func1(trainingSet, "/home/garzon/logo.jpg");
	Pso<SiftCost> pso(func1);
	SiftParams best_params = pso.solve();
	cout << "cost: " << func1.costFunction(best_params) << endl;
	cout << best_params.toMat() << endl;
	cout << "ok" << endl;
	return 0;
}
