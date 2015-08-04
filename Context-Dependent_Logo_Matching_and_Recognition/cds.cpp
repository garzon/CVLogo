#include "cds.h"
#include <algorithm>
CDS::CDS():alpha(20),beta(20),tau(0.4),Nr(10),eps(1e-2),
	maxtheta(16),maxrho(16),maxt(30),threshold(0.90),responseThresholdx(0.09),responseThresholdy(0.03)
{
	for(int i = 0; i < maxtheta; i++)
	{
		P.push_back(vector<Mat>(maxrho));
		Q.push_back(vector<Mat>(maxrho));
	}
	Na = maxtheta;
}

void CDS::extractSIFTKeyPoint() {
	SiftFeatureDetector sift; //此处先用默认参数
	std::vector<KeyPoint> Sx_tmp, Sy_tmp;
	sift.detect(Ix, Sx_tmp);
	sift.detect(Iy, Sy_tmp);
	for(int i = 0; i < (int)Sx_tmp.size(); i++)
	{
		KeyPoint & key = Sx_tmp[i];
		if(key.response > responseThresholdx)Sx.push_back(key);
	}
	for(int i = 0; i < (int)Sy_tmp.size(); i++)
	{
		KeyPoint & key = Sy_tmp[i];
		if(key.response > responseThresholdy)Sy.push_back(key);
	}

#ifdef DEBUG
	Mat Show1,Show2;

	// 去除一些size比较大的特征点，因为商标没有那么大，参数什么还在调试中：…
	//for(int i = 0; i < (int) Sx.size(); i++) if(Sx[i].size > 18.0) Sx.erase(Sx.begin() + i), i--; //删除之后指针不移动
	//for(int i = 0; i < (int) Sy.size(); i++) if(Sy[i].size > 18.0) Sy.erase(Sy.begin() + i), i--;

	drawKeypoints(Ix,Sx,Show1,Scalar(255,255,255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);//在内存中画出特征点
	drawKeypoints(Iy,Sy,Show2,Scalar(255,255,255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("keypointInput",Show1);//显示特征点
	imshow("keypointTest",Show2);
	cout << Sx.size() << endl;
	cout << Sy.size() << endl;
#endif

	SiftDescriptorExtractor siftDesc;//定义描述子对象
	Mat Dx,Dy;//存放特征向量的矩阵
	siftDesc.compute(Ix,Sx,Dx);//计算特征向量
	siftDesc.compute(Iy,Sy,Dy);

#ifdef DEBUG
	/*for(int i = 0; i < Dx.rows; i++)
	{
		for(int j = 0; j < Dx.cols; j++)
			cout << Dx.at<float>(i,j) << ' ';
		cout << endl;
	}
	imshow("Dx",Dx);
	imshow("Dy",Dy);*/
#endif

	D = Mat::zeros(Sx.size(),Sy.size(),CV_32FC1);
	for(int i = 0; i < Dx.rows; i++)
		for(int j = 0; j < Dy.rows; j++)
		{
			const float* px = Dx.ptr<float>(i);
			const float* py = Dy.ptr<float>(j);
			for(int k = 0; k < Dx.cols; k++)
			{
				float tmp = *px - *py;
				D.at<float>(i,j) += tmp * tmp;
				px++;
				py++;
			}
			D.at<float>(i,j) = sqrt(D.at<float>(i,j));
		}
}

void CDS::computeContext() {
	//maybe P and Q need to set their elements to zero here
	for(int i = 0; i < maxtheta; i++)
		for(int j = 0; j < maxrho; j++)
		{
			P[i][j] = Mat::zeros(Sx.size(),Sx.size(),CV_32FC1);
			Q[i][j] = Mat::zeros(Sy.size(),Sy.size(),CV_32FC1);
		}
	for(int i=0;i< (int) Sx.size();i++) //Sx.size() == n in the paper
	{
		float deltarho = (float) Sx[i].size / Nr;
		float baseangle = Sx[i].angle;
		float deltaangle = 360.0 / Na;
		for(int j = 0; j < (int) Sx.size(); j++)
			if(i !=j && unpackSIFTOctave(Sx[i]) == unpackSIFTOctave(Sx[j]) && dist(Sx[i],Sx[j]) < maxrho * deltarho)  //此处8为硬编码，因为我也不知道这里到底该咋办
			{
				float tmp = Sx[j].angle - baseangle;
				if(tmp < 0) tmp += 360 ; //keep tmp in [0, 2*PI]
				int theta = (int) (tmp / deltaangle);
				int rho = (int) ( (dist(Sx[i],Sx[j])) / deltarho );
				P[theta][rho].at<float>(i,j) = 1;
			}
	}

	for(int i=0;i< (int) Sy.size();i++) //Sy.size() == m in the paper
	{
		float deltarho = (float) Sy[i].size / Nr;
		float baseangle = Sy[i].angle;
		float deltaangle = 360.0 / Na;
		for(int j = 0; j < (int) Sy.size(); j++)
			if(i != j && unpackSIFTOctave(Sy[i]) == unpackSIFTOctave(Sy[j]) && dist(Sy[i],Sy[j]) < maxrho * deltarho)  //此处8为硬编码，因为我也不知道这里到底该咋办
			{
				float tmp = Sy[j].angle - baseangle;
				if(tmp < 0) tmp += 360 ; //keep tmp in [0, 2*PI]
				int theta = (int) (tmp / deltaangle);
				int rho = (int) ( (dist(Sy[i],Sy[j])) / deltarho );
				Q[theta][rho].at<float>(i,j) = 1;
			}
	}
}

float CDS::dist(const KeyPoint &p1, const KeyPoint &p2) const
{
	float deltax = p1.pt.x - p2.pt.x , deltay = p1.pt.y - p2.pt.y;
	return sqrt(deltax*deltax + deltay*deltay);
}

void CDS::computeCDSMatrix()
{
	Mat K_history;
	K_history = D * (-1.0 / beta);
	for(int i = 0; i < K_history.rows; i++)
	{
		float* now = K_history.ptr<float>(i);
		for(int j = 0; j < K_history.cols; j++)
		{
			(*now) = exp(*now);
			//if(isnan(*now))(*now) = 0;
			now++;
		}
	}
	normalize(K_history, K_history, 1, 0, NORM_L1);
	for(int t = 0; t < maxt; t++)
	{
		cout << "============================== iterator num = " << t << " ===========================" << endl;
		normalize(G(K_history),K, 1, 0, NORM_L1);
		cout << norm(K_history -K)<< endl;
		if( norm(K - K_history) < eps ) break;
		K_history = K.clone();
	}
}

Mat CDS::G(const Mat &K)const
{
	Mat ret(Sx.size(), Sy.size(), CV_32FC1);
	for(int theta = 0; theta < maxtheta; theta++)
		for(int rho = 0; rho < maxrho; rho++)
		{
			ret += P[theta][rho] * K * Q[theta][rho].t()
					+ P[theta][rho].t() * K * Q[theta][rho];
		}
	ret = D / (-1.0 * beta) + ret * (alpha/beta);

	//cout << ret << endl;
	//exp(ret)
	for(int i = 0; i < ret.rows; i++)
	{
		float* now = ret.ptr<float>(i);
		for(int j = 0; j < ret.cols; j++)
		{
			(*now) = exp(*now);
			//if(isnan(*now))(*now) = 0;
			now++;
		}
	}
	return ret;
}


bool CDS::match()
{
	Kp = Mat(Sx.size(),Sy.size(),CV_32FC1); //条件概率 j|i
	vector<float> sumK;  //当x=i时的和
	sumK.clear();
	for(int i = 0; i < (int)Sx.size(); i++)
	{
		sumK.push_back(0);
		for(int j = 0; j < (int)Sy.size(); j++)
		{
			sumK[i] +=  K.at<float>(i,j);
		}
	}

	for(int i = 0; i < (int)Sx.size(); i++)
		for(int j = 0; j < (int)Sy.size(); j++)
		{
			Kp.at<float>(i,j) = K.at<float>(i,j) / sumK[i];
		}
	matchY.clear();

	vector<float> sumKp;
	for(int i = 0; i < (int)Sx.size(); i++)
	{
		sumKp.push_back(0);
		for(int  j = 0; j < (int)Sy.size(); j++)
			sumKp[i] += Kp.at<float>(i,j);
	}

	for(int i = 0; i < (int)Sx.size(); i++)
		for(int j = 0; j < (int)Sy.size(); j++)
			if(Kp.at<float>(i,j) >= sumKp[i] * threshold)
			{
				matchVec.push_back(DMatch(i,j,0,0));
				if(matchY.find(j) == matchY.end()) matchY.insert(j);
			}
	cout << matchY.size() <<endl;
	cout << Sx.size() << endl;
	//cout << Sy.size() << endl;
	cout << "maxTau = " << matchY.size() << "/" << Sx.size() << " = " << (float) matchY.size() / Sx.size() << endl;
	if(matchY.size() > tau * Sx.size()) return true;
	return false;
}

void CDS::unpackSIFTOctave(const KeyPoint& kpt, int& octave, int& layer, float& scale)
{
	octave = kpt.octave & 255;
	layer = (kpt.octave >> 8) & 255;
	octave = octave < 128 ? octave : (-128 | octave);
	scale = octave >= 0 ? 1.f/(1 << octave) : (float)(1 << -octave);
}

int CDS::unpackSIFTOctave(const KeyPoint &kpt)
{
	int octave = kpt.octave & 255;
	octave = octave < 128 ? octave : (-128 | octave);
	return octave;
}

void CDS::visualize()
{
	drawMatches(Ix, Sx, Iy, Sy, matchVec, showImg);
	//cout << "#match_pair = " << matchVec.size() << endl;
	namedWindow("showImg", 1);
	//setMouseCallback("showImg", CDS::callBackFuncForROI, NULL);
	//rectangle(showImg, Point2f(396,74), Point2f(440,113), Scalar(255,255,255) );
	for(int i = 0; i < (int)matchVec.size() ; i+=1)
	{
		vector<DMatch> tmp;
		tmp.clear();
		for(int j = i; j < std::min((int)i+1,(int)matchVec.size()); j++)
		{
			tmp.push_back(matchVec[j]);
		}
		drawMatches(Ix, Sx, Iy, Sy, tmp, showImg);
		imshow("showImg", showImg);
		waitKey(3000);
	}
	//resize(showImg,showImg,Size(showImg.cols*2.5,showImg.rows*2.5));
	drawMatches(Ix, Sx, Iy, Sy, matchVec, showImg);
	imshow("showImg", showImg);
	waitKey(100000);
	/*for(int i = 0; i < (int) matchVec.size(); i++)
	{
		Point2f &pt = Sy[matchVec[i].trainIdx].pt;
		cout << pt << endl;
	}*/
	//int cnt = 0;
	/*for(int i = 0; i < (int) matchVec.size(); i++)
	{
		DMatch &D = matchVec[i];
		if(Sy[D.trainIdx].pt.y > 74 && Sy[D.trainIdx].pt.y < 113)
			cnt ++;
	}*/
	//cout << "right_num = " << cnt << endl;
	//cout << (float)cnt / matchVec.size() << endl;
	//waitKey(0);
}


void CDS::callBackFuncForROI(int event, int x, int y, int flags, void* userdata)
{
	if(flags == 0 && userdata)
	{
		//I only want to use these parameters...
	}
	if( event == EVENT_LBUTTONDOWN)
	{
		cout << "Left button of the mouse is down - position (" << x << "," << y << ")" << endl;
		//ROIpt1 = Point2f(x, y);
	}
	else if( event == EVENT_LBUTTONUP)
	{
		cout << "Left button of the mouse is up - position (" << x << "," << y << ")" << endl;
		//ROIpt2 = Point2f(x, y);
		/*rectangle(showImg, ROIpt1, ROIpt2, Scalar(255,255,255) );
		imshow("showImg", showImg);*/
	}
}
bool CDS::process()
{
	extractSIFTKeyPoint();
	computeContext();
	computeCDSMatrix();
	return match();
}
