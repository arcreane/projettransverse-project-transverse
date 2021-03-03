#include <opencv2/imgcodecs.hpp>		//Librairies utiles au d�veloppement
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {


	VideoCapture cap(0);		   //Choix de la source de la vid�o (ici cap(0) signifie que la vid�o vient de la cam�ra)
	Mat img;					   //Cr�ation d'une matrice pour afficher et traiter la vid�o
	
	while (true) {				   //Affichage de l'image obtenue

		cap.read(img);			   //Indique l'image de sortie
		imshow("Rendu", img);	   //Affiche une fen�tre contenant img et de nom "Rendu"
		waitKey(1);				   //D�lai d'affichage, ici l'image est mise � jour dans la fen�tre toute les 1 millisecondes
	}
}