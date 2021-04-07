/*
Fichier contenant les classes du projet finale et leurs fonctions.
\file   
\author Benoit - Paraschivoiu et St - Arnaud
date    4 avril 2021
Créé le 1 avril 2021
*/
#pragma once

#include <string>
#include <utility>
#include <cmath>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
#define GAUCHE 0
#define DROITE 1
#define BLANC 0
#define NOIR 1
#define NBR_LIGNES 8
#define NBR_COLONNES 8


class Piece {
public:
	Piece(bool couleur) { couleur_ = couleur; }
	bool setPosition(int positionLigne, int positionColonne) { 
		if (this->mouvementValide(positionLigne, positionColonne)) {
			positionLigne_ = positionLigne;
			positionColonne_ = positionColonne;
			return true;
		}
		else {
			cout << "Position invalide" << endl;
			return false;
		}
	}
	
	pair<int, int> getPosition() const { return { positionLigne_, positionColonne_ }; } 
	bool getCouleur() const { return couleur_; }

protected:
	int positionLigne_=0;
	int positionColonne_=0;
	bool couleur_; //0 = blanc, 1 = noir
	virtual bool mouvementValide(int positionLigneVoulue, int positionColonneVoulue) {
		if ((positionLigneVoulue < 0) | (positionLigneVoulue >= NBR_LIGNES)) return false;
		else if ((positionColonneVoulue < 0) | (positionColonneVoulue >= NBR_COLONNES)) return false;
		else if ((positionColonneVoulue == positionColonne_ && positionLigneVoulue == positionLigne_)) return false;
		return true;
	}
};

class Roi : public Piece {
public:
	Roi(bool couleur) : Piece(couleur) {
		couleur ? positionLigne_ = 7, positionColonne_ = 4 : positionLigne_ = 0, positionColonne_ = 4;
		//        roi noir                                   roi blanc
	}

	bool mouvementValide(int positionLigneVoulue, int positionColonneVoulue) override {
		if (Piece::mouvementValide(positionLigneVoulue, positionColonneVoulue)) {

			bool validationLigne = abs(positionLigne_ - positionLigneVoulue) <= 1;
			bool validationColonne = abs(positionColonne_ - positionColonneVoulue) <= 1;

			if ( validationLigne && validationColonne) {
				return true;
			}
		}
		return false;
	}
};

class Cavalier : public Piece {
public:
	Cavalier(bool couleur, bool cote) : Piece(couleur) { //cote a 1 est a droite, 0 est a gauche
		if (couleur) { //donc le cheval noir
			//cout << "COTE: " << cote << endl;
			cote ? (positionLigne_ = 7, positionColonne_ = 6) : (positionLigne_ = 7, positionColonne_ = 1);
			//     a droite                                   a gauche
		}
		else { //cheval blanc
			//cout << "COTE: " << cote << endl;
			cote ? (positionLigne_ = 0, positionColonne_ = 6) : (positionLigne_ = 0, positionColonne_ = 1);
			//     a droite                                   a gauche
		}
	}

	bool mouvementValide(int positionLigneVoulue, int positionColonneVoulue) override {
		if (Piece::mouvementValide(positionLigneVoulue, positionColonneVoulue)) {
			int variationLigne = abs(positionLigne_ - positionLigneVoulue);
			int variationColonne = abs(positionColonne_ - positionColonneVoulue);

			bool validationLigne = (variationLigne == 2) | (variationLigne == 1);
			bool validationColonne = (variationColonne == 2) | (variationColonne == 1);
			bool validationMouvement = variationColonne != variationLigne;
			
			if (validationColonne && validationLigne && validationMouvement) {
				return true;
			}
		}
		return false;
	}
};

class Tour : public Piece {
public:
	Tour(bool couleur, bool cote) : Piece(couleur) { //cote a 1 est a droite, 0 est a gauche
		if (couleur) { //donc la tour noire
			cote ? (positionLigne_ = 7, positionColonne_ = 7) : (positionLigne_ = 7, positionColonne_ = 0);
			//     a droite                                   a gauche
		}
		else { //tour blanche
			cote ? (positionLigne_ = 0, positionColonne_ = 7) : (positionLigne_ = 0, positionColonne_ = 0);
			//     a droite                                   a gauche
		}
	}

	bool mouvementValide(int positionLigneVoulue, int positionColonneVoulue) {
		if (Piece::mouvementValide(positionLigneVoulue, positionColonneVoulue)) {
			int variationLigne = abs(positionLigne_ - positionLigneVoulue);
			int variationColonne = abs(positionColonne_ - positionColonneVoulue);

			if ((variationColonne == 0 && variationLigne > 0) | (variationLigne == 0 && variationColonne > 0)) {
				return true;
			}
		}
		return false;
	}
};

//Le Pion est implementer ci dessous, mais puisquil faut trois pieces, il est en commentaire. Si jamais un jeu complet veut etre fait, on pourra decommenter cette section.
/*
class Pion : public Piece {
public:
	Pion(bool couleur, int positionColonne) : Piece(couleur) {
		positionColonne_ = positionColonne;
		couleur ? positionLigne_ = 6 : positionLigne_ = 1;
	}

	bool mouvementValide(int positionLigneVoulue, int positionColonneVoulue) {
		if (Piece::mouvementValide(positionLigneVoulue, positionColonneVoulue)) {
			if (couleur_ && (positionLigneVoulue >= positionLigne_)) return false;   // ces deux conditions sassurent qu une piece avance
			else if (!couleur_ && positionLigneVoulue <= positionLigne_) return false;

			int variationLigne = abs(positionLigne_ - positionLigneVoulue);
			int variationColonne = abs(positionColonne_ - positionColonneVoulue);

			if (variationColonne == 0) { //et quil ny a pas de piece la, a ajouter
				if (variationLigne == 1) return true;
				else if ((variationLigne == 2) && couleur_ && (positionLigne_ == 6)) return true;  // double saut au debut pour les noirs
				else if ((variationLigne == 2) && !couleur_ && (positionLigne_ == 1)) return true; //double saut a lavant pour les blancs
			}
			if (variationColonne == 1 && variationLigne == 1) //et quil y a une piece la
				return true;
		}
		return false;
	}
	
	bool setPosition(int positionLigne, int positionColonne) override {
		if (mouvementValide(positionLigne, positionColonne)) {
			return Piece::setPosition(positionLigne, positionColonne);
		}
		else {
			cout << "Position invalide" << endl;
			return false;
		}
	}
};*/

class Echiquier {
public:
	Echiquier() {
		for (int ligne = 0; ligne < NBR_LIGNES; ligne++) {
			for (int colonne = 0; colonne < NBR_COLONNES; colonne++) {
				echiquier_[ligne][colonne] = nullptr;
				if (ligne == 0) {

					if (colonne == 0) echiquier_[ligne][colonne] = new Tour(BLANC, GAUCHE);
					if (colonne == 1) echiquier_[ligne][colonne] = new Cavalier(BLANC, GAUCHE);
					else if (colonne == 4) echiquier_[ligne][colonne] = new Roi(BLANC);
					else if (colonne == 6) echiquier_[ligne][colonne] = new Cavalier(BLANC, DROITE);
					else if (colonne == 7) echiquier_[ligne][colonne] = new Tour(BLANC, DROITE);
				}
				//else if (ligne == 1) echiquier_[ligne][colonne] = new Pion(BLANC, colonne); // pions blancs

				//else if (ligne == 6) echiquier_[ligne][colonne] = new Pion(NOIR, colonne); // pions noirs

				else if (ligne == 7) {

					if (colonne == 0) echiquier_[ligne][colonne] = new Tour(NOIR, GAUCHE);
					else if (colonne == 1) echiquier_[ligne][colonne] = new Cavalier(NOIR, GAUCHE);
					else if (colonne == 4) echiquier_[ligne][colonne] = new Roi(NOIR);
					else if (colonne == 6) echiquier_[ligne][colonne] = new Cavalier(NOIR, DROITE);
					else if (colonne == 7) echiquier_[ligne][colonne] = new Tour(NOIR, DROITE);
				}
			}
		}		
	}
	
	~Echiquier() {
		for (int ligne = 0; ligne < NBR_LIGNES; ligne++) {
			for (int colonne = 0; colonne < NBR_COLONNES; colonne++) {
				delete echiquier_[ligne][colonne];
			}
		}
	}

	Piece* getPiece(int positionLigne, int positionColonne) {
		return echiquier_[positionLigne][positionColonne];
	}
	
	bool effectuerMouvement(int positionActuelleX, int positionActuelleY, int positionVoulueX, int positionVoulueY) {
		if (echiquier_[positionActuelleX][positionActuelleY] == nullptr) return false; //peut pas bouger une piece qui existe pas
		else if (pieceEnChemin(positionActuelleX, positionActuelleY, positionVoulueX, positionVoulueY)) return false;
		else if (echiquier_[positionVoulueX][positionVoulueY] != nullptr) { //donc il y a une piece
			bool memeCouleur = echiquier_[positionVoulueX][positionVoulueY]->getCouleur() == echiquier_[positionActuelleX][positionActuelleY]->getCouleur();
			if (memeCouleur) return false; //peut pas bouger sur une piece de ta couleur
			else { //donc il y a une piece adverse
				return echangerPiece(positionActuelleX, positionActuelleY, positionVoulueX, positionVoulueY, true);
			}
		}
		else { //donc il ny a pas de piece
			return echangerPiece(positionActuelleX, positionActuelleY, positionVoulueX, positionVoulueY, false);
		}
	}

private:
	Piece* echiquier_[NBR_LIGNES][NBR_COLONNES]; // un jeu d'échecs a 64 cases
	bool echangerPiece(int positionActuelleX, int positionActuelleY, int positionVoulueX, int positionVoulueY, bool pieceAdverse) {
		if (echiquier_[positionActuelleX][positionActuelleY]->setPosition(positionVoulueX, positionVoulueY)) { //on change les attributs de la piece quon bouge si le mouvement est valide
			//on rentre ici si le mouvement est valide
			if (pieceAdverse) delete echiquier_[positionVoulueX][positionVoulueY];
			echiquier_[positionVoulueX][positionVoulueY] = echiquier_[positionActuelleX][positionActuelleY]; //on change sa position dans la matrice
			echiquier_[positionActuelleX][positionActuelleY] = nullptr; //il y a maintenant rien a la position actuelle
			return true;
		}
		return false;
	}
	//puisque la seule piece dans notre cas qui peut rencontrer une piece dans son chemin est la tour, le code suitant sera implementer en consequent. 
	//Si jamais une version complete du jeu voudra etre faites, le code suivant devra etre changer pour considerer que le fou et la reine (le pion aussi lorsquil avance de deux) pouraient avoir se probleme.
	bool pieceEnChemin(int positionActuelleX, int positionActuelleY, int positionVoulueX, int positionVoulueY) { 
		int variationLigne = abs(positionActuelleX - positionVoulueX);
		int variationColonne = abs(positionActuelleY - positionVoulueY);

		if (variationLigne > 0) {
			for (int i = positionActuelleX; i < positionVoulueX; i++) { //on ne regarde pas sil y a une piece a la positon voulu, ceci est deja considerer dans la fonction effectuerMouvement
				if (echiquier_[i][positionActuelleY] != nullptr) return true;
			}
		}
		else {
			for (int i = positionActuelleY; i < positionVoulueY; i++) { //on ne regarde pas sil y a une piece a la positon voulu, ceci est deja considerer dans la fonction effectuerMouvement
				if (echiquier_[positionActuelleX][i] != nullptr) return true;
			}
		}
		return false;
	}
};