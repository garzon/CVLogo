#ifndef IPARAMS_h
#define IPARAMS_h

#include <vector>

#include <opencv2/opencv.hpp>

class IParams {
public:
    std::vector<double> params;

	// paramRange and the constructors is needed to be overrided(re-declared) in the children classes.
	static std::vector<std::pair<double, double> > paramRange;

	IParams() = default;
	IParams(const std::vector<double> &v) : params(v) {};
	IParams(cv::Mat m) {
		double *p = m.ptr<double>();
		int n = m.rows * m.cols;
		for (int i = 0; i < n; i++, p++)
			params.push_back(*p);
	};

	cv::Mat toMat() const {
		cv::Mat res(0, 0, CV_64F);
        for (auto i : params) res.push_back(i);
		res = res.reshape(1, params.size());
		return res;
	}
};


#endif // IPARAMS_h
