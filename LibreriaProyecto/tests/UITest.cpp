/*
 * UITest.cpp
 *
 *  Created on: Aug 8, 2015
 *      Author: Daniel
 */

#include "UITest.h"
#include "../ui/InterfazGrafica.h"
#include "../models/compras/Local.h"

UITest::UITest() {};

UITest::~UITest() {};

void UITest::testUI() {
	Local* local = new Local();
	InterfazGrafica* ui = new InterfazGrafica(*local);
	ui->inicializar();

	delete ui;
	delete local;
}
