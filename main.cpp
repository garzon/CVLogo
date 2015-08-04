#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cds.h"
using namespace std;
CDS cds;
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Mat inputImage = imread("/Users/SpaceQ/Pictures/Adidas_Logo.svg.png",CV_LOAD_IMAGE_GRAYSCALE);
//	Mat inputImage = imread("/Users/SpaceQ/Pictures/AudiLogo.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	Mat testImage = imread("/Users/SpaceQ/Pictures/Adidas_4.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//	Mat testImage = imread("/Users/SpaceQ/Pictures/NewAudiQ7_1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//	Mat inputImage = imread("/Users/SpaceQ/Pictures/HeinekenLogo_1.png",CV_LOAD_IMAGE_GRAYSCALE);
//	Mat testImage = imread("/Users/SpaceQ/Pictures/Heineken_1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	cds.setInputImage(inputImage);
	cds.setTestImage(testImage);
	cout << cds.process() << endl;
	cds.visualize();
	return a.exec();
}
