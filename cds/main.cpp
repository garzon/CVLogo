//#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cds.h"
using namespace std;
using namespace cv;
CDS cds;
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
//	Mat inputImage = imread("/Users/SpaceQ/Pictures/Adidas_Logo.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//	Mat inputImage = imread("/Users/SpaceQ/Pictures/AudiLogo.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//	Mat testImage = imread("/Users/SpaceQ/Pictures/Adidas_4.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//	Mat testImage = imread("/Users/SpaceQ/Pictures/NewAudiQ7_1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//	Mat inputImage = imread("/Users/SpaceQ/Pictures/Heineken/HeinekenLogo_2.JPG",CV_LOAD_IMAGE_GRAYSCALE);
//	Mat testImage = imread("/Users/SpaceQ/Pictures/Heineken/TB2Zo.KcpXXXXb_XXXXXXXXXXXX_\!\!530257868.jpg_400x400.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	Mat inputImage = imread("/Users/SpaceQ/Pictures/Intel/Intel_logo_3.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	Mat testImage = imread("/Users/SpaceQ/Pictures/Intel/TB21ACabFXXXXXgXXXXXXXXXXXX_\!\!642864513.jpg_430x430q90.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	cds.setInputImage(inputImage);
	cds.setTestImage(testImage);
	cout << cds.process() << endl;
	cds.visualize();
	cds.drawRectanglePlanA();
	ofstream outfile("para.txt");
	cds.writeParameters(outfile);
	outfile.close();
	return a.exec();
}
