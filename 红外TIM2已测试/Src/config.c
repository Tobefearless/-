#include "config.h"

static App locApp;
static App *app = &locApp;
static IrCode locIr;

//App������ʼ��
App *AppInit(void) {
	app->ir = &locIr;
	app->ir->valid = 0;
	return app;
}

//��ȡ������
App *GetApp(void) {
	return app;
}



