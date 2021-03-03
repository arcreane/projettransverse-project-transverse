#include <opencv2/imgcodecs.hpp>		//Librairies utiles au développement
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale);
string cascadeName, nestedCascadeName;

int main(int argc, const char** argv) {


	VideoCapture GetVideo;
	Mat frame, img;				//Création de matrices pouvant contenir la vidéo
	CascadeClassifier cascade, nestedCascade;	//Charge des fichiers .xml entraînés pour la reconnaissance faciale
	double scale = 1;			//Echelle
	nestedCascade.load("res/cas/haarcascade_frontalface_default.xml");	//Chargement du fichier cascade
	cascade.load("res/cas/haarcascade_frontalface_default.xml");
	
		GetVideo.open(0);
		if (GetVideo.isOpened()) {
			cout << "Détection en cours" << endl;

			while (1) {
				GetVideo >> frame;
				if (frame.empty()) {
					break;
				}
				Mat frameclone = frame.clone();
				detectAndDraw(frameclone, cascade, nestedCascade, scale);
				char c = (char)waitKey(10);
				if (c == 27 || c == 'f' || c == 'F') {
					break;
				}
			}
		}
		else
			cout << "Impossible d'utiliser la caméra";
		return 0;
			
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale)
{
 vector<Rect> faces, faces2; 
    Mat gray, smallImg; 
  
    cvtColor( img, gray, COLOR_BGR2GRAY ); //Conversion couleur -> nuances de gris 
    double fx = 1 / scale; 
  
    //Réglage des dimensions de l'image obtenue  
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );  
    equalizeHist( smallImg, smallImg ); 
  
    // Gestion des images de différentes tailles  
    cascade.detectMultiScale( smallImg, faces, 1.1,  
                            2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) ); 
  
    //Entourer les visages détectés 
    for ( size_t i = 0; i < faces.size(); i++ ) 
    { 
        Rect r = faces[i]; 
        Mat smallImgROI; 
        vector<Rect> nestedObjects; 
        Point center; 
        Scalar color = Scalar(255, 0, 0);
        Scalar color2 = Scalar(255, 0, 255);
        int radius; 
  
        double aspect_ratio = (double)r.width/r.height; 
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 ) 
        { 
            center.x = cvRound((r.x + r.width*0.5)*scale); 
            center.y = cvRound((r.y + r.height*0.5)*scale); 
            radius = cvRound((r.width + r.height)*0.25*scale); 
            circle( img, center, radius, color, 3, 8, 0 ); 
        } 
        else
            rectangle( img, Point(cvRound(r.x*scale), cvRound(r.y*scale)), 
                    Point(cvRound((r.x + r.width-1)*scale),  
                    cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0); 
        if( nestedCascade.empty() ) 
            continue; 
        smallImgROI = smallImg( r ); 
          
        //Détection des yeux dans l'image 
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2, 
                                        0|CASCADE_SCALE_IMAGE, Size(30, 30) );  
          
        // Encercler les yeux 
        for ( size_t j = 0; j < nestedObjects.size(); j++ )  
        { 
            Rect nr = nestedObjects[j]; 
            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale); 
            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale); 
            radius = cvRound((nr.width + nr.height)*0.25*scale); 
            circle( img, center, radius, color2, 3, 8, 0 ); 
        } 
    } 
  
    //Ouverture du résultat 
    imshow( "Face Detection", img );
    waitKey(1);
}
