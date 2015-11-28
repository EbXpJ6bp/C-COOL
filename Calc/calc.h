typedef void(*Member)(void);
typedef void(*_Member)(void*);
typedef void(*__Member)(void*, int in);

typedef struct {
	int now_p;
	_Member 	show;
	_Member 	clear;
	_Member		done;
	__Member 	add;
	__Member 	dif;
	__Member 	mul;
	__Member 	div;
	Member		sample;
} Calc_t;


void calc_sample();
void calc_show();
void calc_clear();
void calc_add();
void calc_dif();
void calc_mul();
void calc_div();
void calc_done();
Calc_t *newCalc();
