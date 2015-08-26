/*
 * UITest.cpp
 *
 *  Created on: Aug 8, 2015
 *      Author: Daniel
 */

#include "UITest.h"
#include "../ui/InterfazGrafica.h"

UITest::UITest() {};

UITest::~UITest() {};

void UITest::testUI() {

	InterfazGrafica* ui = new InterfazGrafica();
	ui->inicializar();

	delete ui;

}
