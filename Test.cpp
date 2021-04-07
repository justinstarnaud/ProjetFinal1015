#include "classes_projet.hpp"
#include "gtest/gtest.h"



TEST(TestEchiquier, TestMouvement) {
	Echiquier echiquier = Echiquier();
	EXPECT_EQ(false, echiquier.effectuerMouvement(0, 0, 1, 4));
}