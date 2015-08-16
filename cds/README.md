对Logo

- 首次要执行
	- void setInputImage(cv::Mat inputimage);
	- extractSIFTKeyPointX();
	- computeContextX();
- 修改参数后需执行
	- computeContextX();
	
对TestImage

- 首次要执行
	- void setTestImage(cv::Mat testimage);
	- extractSIFTKeyPointY();
	- computeContextY();
- 修改参数后要执行
	- computeContextY();

之后执行 

- computeCDSMatrix();
- bool match();

match()会返回是否匹配到

之后通过

- void getSiftKeyPoint(std::vector<cv::KeyPoint> &Sx, std::vector<cv::KeyPoint> &Sy);
- std::vector<cv::DMatch> getMatchVec()；

来得到特征点和匹配点对

