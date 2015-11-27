#include <stdio.h>
#include <stdlib.h> 
#include "calc.h"

void calc_sample() {
	printf("‚±‚ÌŠÖ”‚ÍCalc‚Ìƒƒ“ƒoŠÖ”‚Ì‚æ‚¤‚Éˆµ‚¦‚Ü‚·\n");
}

void calc_show(Calc_t* self)
{
	printf("Rslt...%d\n", self->now_p);
}

void calc_clear(Calc_t *self)
{
	printf("Clear...\n");
	self->now_p = 0;
}

void calc_add(Calc_t *self, int in)
{
	self->now_p = self->now_p + in;
}

void calc_dif(Calc_t *self, int in)
{
	self->now_p = self->now_p - in;
}

void calc_mul(Calc_t *self, int in)
{
	self->now_p = self->now_p * in;
}

void calc_div(Calc_t *self, int in)
{
	self->now_p = self->now_p / in;
}

void calc_done(Calc_t *self)
{
	free(self);
}

Calc_t* newCalc(void)
{
	Calc_t	 *Calc;
	Calc = NULL;
	Calc = malloc(sizeof(Calc_t));
	if (Calc == NULL) {
		printf("Cant't make new Calc!\n");
		return NULL;
	}
	Calc->now_p = 0;
	Calc->show = (void*)&calc_show;
	Calc->clear = (void*)&calc_clear;
	Calc->add = (void*)&calc_add;
	Calc->dif = (void*)&calc_dif;
	Calc->mul = (void*)&calc_mul;
	Calc->div = (void*)&calc_div;
	Calc->done = (void*)&calc_done;
	Calc->sample = (void*)&calc_sample;
	return Calc;

}
