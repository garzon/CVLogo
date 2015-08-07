#ifndef CDS_H
#define CDS_H

//#define DEBUG
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <set>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class CDS
{
public:
	CDS();
	void setAlpha(float Alpha) { alpha = Alpha; }
	void setBeta(float Beta) { beta = Beta; }
	void setTau(float Tau) { tau = Tau; }
	void setNr(float Nr) { this->Nr = Nr; }
	void setEps(float Eps) { eps = Eps; }
	void setMaxTheta(float theta) { maxtheta = theta; }
	void setMaxRho(float rho) { maxrho = rho; }
	float getAlpha() { return alpha; }
	float getBeta() { return beta; }
	float getTau() { return tau; }
	float getNr() { return Nr; }
	float getEps() { return eps; }
	float getMaxTheta() { return maxtheta; }
	float getMaxRho() { return maxrho; }

	void setInputImage(cv::Mat inputimage)
	{
		float cols = 500;
		float rows = 500.0 / inputimage.cols * inputimage.rows;
		resize(inputimage,Ix,cv::Size(cols,rows));
	}
	void setTestImage(cv::Mat testimage)
	{
		resize(testimage,Iy,cv::Size(500,500));
	}

	void extractSIFTKeyPoint();
	void computeContext();
	void computeCDSMatrix();
	bool match();
	void visualize();
	bool process();
	void drawRectanglePlanA();
	void drawRectanglePlanB();

	//正式接口
	struct Param
	{
		float alpha, beta, tau, Nr, eps, eeps;
		int maxtheta, maxrho, maxt;
		float threshold, responseThresholdx,responseThresholdy, rectangleThreshold;
	}param;
	void setParameters(const Param& param);
	Param getParameters(){return param;}
	void writeParameters(std::ofstream &outfile);
	void readParameters(std::ifstream &infile);
	void writeLogo(std::ofstream &outfile);
	void getSiftKeyPoint(std::vector<cv::KeyPoint> &Sx, std::vector<cv::KeyPoint> &Sy);
	cv::Mat getInputImage() { return Ix; }
	cv::Mat getTestImage() { return Iy; }
	std::vector<cv::DMatch> getMatchVec() { return matchVec;}
private:
	//参数
	float alpha, beta, tau, Nr, eps, eeps;
	int maxtheta, maxrho, maxt;
	float threshold, responseThresholdx,responseThresholdy, rectangleThreshold;
	//result
	std::vector<cv::KeyPoint> Sx, Sy;
	cv::Mat Dx,Dy;//存放特征向量的矩阵
	cv::Mat Ix,Iy;
	std::vector<std::vector<cv::Mat> > P, Q; // I think SparseMat is better, but I don't know how to use it.
	cv::Mat K,D;
	cv::Mat Kp;
	std::vector<cv::DMatch> matchVec;
	//private
	std::set<int> matchY;
	cv::Mat showImg;

	cv::Mat G(const cv::Mat &K) const;
	float dist(const cv::KeyPoint &p1, const cv::KeyPoint &p2) const;
	void unpackSIFTOctave(const cv::KeyPoint& kpt, int& octave, int& layer, float& scale);
	int unpackSIFTOctave(const cv::KeyPoint& kpt);
	static void callBackFuncForROI(int event, int x, int y, int flags, void* userdata);
	static cv::Point2f ROIpt1, ROIpt2;
};

#endif // CDS_H
