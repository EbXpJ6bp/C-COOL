#include<stdio.h>
#include"Person.h"

//�v���C�x�[�g�ϐ�
static int MAGIC_NUMBER = 7;

//�v���C�x�[�g�֐�
static void Person_ShowSecret(void);

void Person_Test(void) {
	printf("Person Class\n");
	Person_ShowSecret();
}


void Person_Bark(void) {
	printf("����ɂ���\n");
}

void Person_SayAge(Person person) {
	printf("���̔N���%d�ł��B\n", person.age);
}

//====�v���C�x�[�g�֐�====

static void Person_ShowSecret(void) {
	printf("MagicNumber is %d\n", MAGIC_NUMBER);
}
