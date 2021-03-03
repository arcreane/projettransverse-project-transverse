#include <opencv2/imgcodecs.hpp>		//Librairies utiles au développement
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;



int main() {


	VideoCapture cap(0);
	Mat img;
	while (true) {

		cap.read(img);
		imshow("Rendu", img);
		waitKey(1);
	}
}