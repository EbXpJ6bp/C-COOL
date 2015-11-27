/*

written by hiroumauma
URL http://blog.livedoor.jp/hiroumauma/archives/1366474.html

*/

#include <stdio.h>
#include "calc.h"

int main() {

	Calc_t *Calc;
	Calc = newCalc();							//�V�����d��I�u�W�F�N�g�̐���

	Calc->sample();								//�����o�֐��e�X�g

	Calc->add(Calc, 5); 						//�@+5
	Calc->mul(Calc, 10);						//  x10
	Calc->div(Calc, 2);							//  /2
	Calc->dif(Calc, 5);							//  -5

	Calc->show(Calc);							// 5x10/2-5 = 20;

	printf("--> %d\n", Calc->now_p);			//�����o�ϐ��ւ̃A�N�Z�X

	Calc->clear(Calc);							// clear
	Calc->show(Calc);							// 0

	Calc->done(Calc);							//free

	return 0;
}