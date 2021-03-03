#include <opencv2/imgcodecs.hpp>		//Librairies utiles au développement
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {


	VideoCapture cap(0);		   //Choix de la source de la vidéo (ici cap(0) signifie que la vidéo vient de la caméra)
	Mat img;					   //Création d'une matrice pour afficher et traiter la vidéo
	
	while (true) {				   //Affichage de l'image obtenue

		cap.read(img);			   //Indique l'image de sortie
		imshow("Rendu", img);	   //Affiche une fenêtre contenant img et de nom "Rendu"
		waitKey(1);				   //Délai d'affichage, ici l'image est mise à jour dans la fenêtre toute les 1 millisecondes
	}
}