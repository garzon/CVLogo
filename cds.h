#ifndef CDS_H
#define CDS_H

//#define DEBUG
#include<iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <set>
using namespace std;
using namespace cv;
class CDS
{
public:
	CDS();
	void setAlpha(float Alpha) { alpha = Alpha; }
	void setBeta(float Beta) { beta = Beta; }
	void setTau(float Tau) { tau = Tau; }
	void setNa(float Na) { this->Na = Na; }
	void setNr(float Nr) { this->Nr = Nr; }
	void setEps(float Eps) { eps = Eps; }
	void setMaxTheta(float theta) { maxtheta = theta; }
	void setMaxRho(float rho) { maxrho = rho; }
	void setParameters(float Alpha, float Beta, float Tau, float Na, float Nr, float eps);
	float getAlpha() { return alpha; }
	float getBeta() { return beta; }
	float getTau() { return tau; }
	float getNa() { return Na; }
	float getNr() { return Nr; }
	float getEps() { return eps; }
	float getMaxTheta() { return maxtheta; }
	float getMaxRho() { return maxrho; }

	void setInputImage(Mat inputimage)
	{
		//resize(inputimage,Ix,Size(200,200));
		Ix = inputimage;
	}
	void setTestImage(Mat testimage)
	{
		resize(testimage,Iy,Size(500,500));
	}
	Mat getInputImage() { return Ix; }
	Mat getTestImage() { return Iy; }

	void extractSIFTKeyPoint();
	void computeContext();
	void computeCDSMatrix();
	bool match();
	void visualize();
	bool process();
private:
	float alpha, beta, tau, Nr, eps;
	int maxtheta, maxrho, maxt;
	float threshold, Na, responseThresholdx,responseThresholdy;
	std::vector<KeyPoint> Sx, Sy;
	Mat Ix,Iy;
	vector< vector<Mat> > P, Q; // I think SparseMat is better, but I don't know how to use it.
	Mat K,D;
	Mat Kp;
	std::set<int> matchY;
	vector<DMatch> matchVec;
	Mat showImg;

	Mat G(const Mat &K) const;
	float dist(const KeyPoint &p1, const KeyPoint &p2) const;
	void unpackSIFTOctave(const KeyPoint& kpt, int& octave, int& layer, float& scale);
	int unpackSIFTOctave(const KeyPoint& kpt);
	static void callBackFuncForROI(int event, int x, int y, int flags, void* userdata);
	static Point2f ROIpt1, ROIpt2;
};

#endif // CDS_H
