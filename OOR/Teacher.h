
#ifndef _TEACHER_H_
#define _TEACHER_H_

#define newPerson() {Person_Bark}

#include "Person.h"

typedef struct Teacher {
	Person base;
	int nStudent;
}Teacher;

//�p�u���b�N�֐��̃v���g�^�C�v�錾
void Teacher_Bark(struct Teacher teacher);


#endif //_TEACHER_H_
