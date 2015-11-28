
#ifndef _TEACHER_H_
#define _TEACHER_H_

#define newPerson() {Person_Bark}

#include "Person.h"

typedef struct Teacher {
	Person base;
	int nStudent;
}Teacher;

//パブリック関数のプロトタイプ宣言
void Teacher_Bark(struct Teacher teacher);


#endif //_TEACHER_H_
