#include "classes_projet.hpp"
#include "gtest/gtest.h"

#define GAUCHE 0
#define DROITE 1
#define BLANC 0
#define NOIR 1

TEST(TestRoi, TestInitilisation) {
	Roi roi = Roi(BLANC);
	EXPECT_EQ(BLANC, roi.getCouleur());
	EXPECT_EQ(0, roi.getPosition().first);
	EXPECT_EQ(4, roi.getPosition().second);

	Roi roiN = Roi(NOIR);
	EXPECT_EQ(NOIR, roiN.getCouleur());
	EXPECT_EQ(7, roiN.getPosition().first);
	EXPECT_EQ(4, roiN.getPosition().second);
}

TEST(TestRoi, TestMouvement) {
	Roi roi = Roi(BLANC);
	EXPECT_TRUE(roi.setPosition(0, 5));
	EXPECT_TRUE(roi.setPosition(1, 5));
	EXPECT_TRUE(roi.setPosition(1, 6));
	EXPECT_FALSE(roi.setPosition(1, 6));
	EXPECT_FALSE(roi.setPosition(12, 5));
	EXPECT_FALSE(roi.setPosition(3, 6));
	EXPECT_FALSE(roi.setPosition(1, 8));
}

TEST(TestCavalier, TestInitilisation) {
	Cavalier cav = Cavalier(BLANC, GAUCHE);
	EXPECT_EQ(BLANC, cav.getCouleur());
	EXPECT_EQ(0, cav.getPosition().first);
	EXPECT_EQ(1, cav.getPosition().second);

	Cavalier cavN = Cavalier(NOIR, DROITE);
	EXPECT_EQ(NOIR, cavN.getCouleur());
	EXPECT_EQ(7, cavN.getPosition().first);
	EXPECT_EQ(6, cavN.getPosition().second);
}

TEST(TestCavalier, TestMouvement) {
	Cavalier cav = Cavalier(BLANC, GAUCHE);
	EXPECT_TRUE(cav.setPosition(2, 2));
	EXPECT_TRUE(cav.setPosition(1, 4));
	EXPECT_TRUE(cav.setPosition(3, 3));
	EXPECT_FALSE(cav.setPosition(3, 3));
	EXPECT_FALSE(cav.setPosition(-1, 5));
	EXPECT_FALSE(cav.setPosition(3, 6));
	EXPECT_FALSE(cav.setPosition(5, 5));
}

TEST(TestTour, TestInitilisation) {
	Tour tour = Tour(BLANC, GAUCHE);
	EXPECT_EQ(BLANC, tour.getCouleur());
	EXPECT_EQ(0, tour.getPosition().first);
	EXPECT_EQ(0, tour.getPosition().second);

	Tour tourN = Tour(NOIR, DROITE);
	EXPECT_EQ(NOIR, tourN.getCouleur());
	EXPECT_EQ(7, tourN.getPosition().first);
	EXPECT_EQ(7, tourN.getPosition().second);
}

TEST(TestTour, TestMouvement) {
	Tour tour = Tour(BLANC, GAUCHE);
	EXPECT_TRUE(tour.setPosition(0, 2));
	EXPECT_TRUE(tour.setPosition(0, 7));
	EXPECT_TRUE(tour.setPosition(7, 7));
	EXPECT_FALSE(tour.setPosition(7, 7));
	EXPECT_FALSE(tour.setPosition(8, 7));
	EXPECT_FALSE(tour.setPosition(6, 6));
	EXPECT_FALSE(tour.setPosition(5, 4));
}

TEST(TestEchiquier, TestMouvementValide) {
	Echiquier echiquier = Echiquier();
	EXPECT_TRUE(echiquier.effectuerMouvement(0, 0, 5, 0));
	EXPECT_TRUE(echiquier.effectuerMouvement(7, 1, 5, 2));
	EXPECT_TRUE(echiquier.effectuerMouvement(0, 4, 1, 5));
}

TEST(TestEchiquier, TestPieceEnChemin) {
	Echiquier echiquier = Echiquier();
	echiquier.effectuerMouvement(7, 0, 4, 0);
	EXPECT_FALSE(echiquier.effectuerMouvement(0, 0, 7, 0));
	EXPECT_FALSE(echiquier.effectuerMouvement(0, 0, 0, 3));
	echiquier.effectuerMouvement(0, 6, 2, 7);
	EXPECT_FALSE(echiquier.effectuerMouvement(7, 7, 1, 7));

}

TEST(TestEchiquier, TestManger) {
	Tour tourNoire = Tour(NOIR, GAUCHE);
	Tour tourBlanche = Tour(BLANC, GAUCHE);
	Echiquier echiquier = Echiquier();
	EXPECT_EQ(tourNoire, echiquier.getPiece(7,0));
	EXPECT_TRUE(echiquier.effectuerMouvement(0, 0, 7, 0));
	//EXPECT_EQ()


}

//TEST(TestEchiquier, TestPieceEnChemin) {
//	Echiquier echiquier = Echiquier();
//
//}

