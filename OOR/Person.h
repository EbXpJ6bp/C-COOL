
#ifndef _PERSON_H_
#define _PERSON_H_

#define newPerson() {Person_Bark}

typedef struct Person {
	int age;
}Person;

//�p�u���b�N�֐��̃v���g�^�C�v�錾
void Person_Test(void);

void Person_Bark(void);

void Person_SayAge(Person person);

#endif //_PERSON_H_
