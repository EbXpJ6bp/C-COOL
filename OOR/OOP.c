/**
* @file: OOP.c
*
* @brief: Object Oriented Programing sample with C
*
* @author: Atsushi Sakai
*
* @copyright (c): 2014 Atsushi Sakai
*
* @license : GPL Software License Agreement
**/

#include <stdio.h>
#include "Person.h"
#include "Dog.h"
#include "Teacher.h"

typedef struct Animal {
	void(*Bark)(void);
}Animal;

int main(void) {
	printf("Object Oriented C Sample!!\n");

	//===�J�v�Z�����̃T���v��===
	//Person.c��MAGIC_NUMBER��Person_Secret��
	//Person.c���炵���Q�Ƃ��Ȃ�
	printf("===�J�v�Z�����̃T���v��===\n");
	Person_Test();

	//===�|�����[�t�B�Y���̃T���v��===
	printf("===�|�����[�t�B�Y���̃T���v��===\n");
	Animal person = newPerson();//�l�Ԃ̃I�u�W�F�N�g���쐬
	Animal dog = newDog();   //���̃I�u�W�F�N�g���쐬

	person.Bark();
	dog.Bark();

	//===�p���̃T���v��===
	printf("===�p���̃T���v��===\n");
	Person student;
	student.age = 15;
	Person_SayAge(student);

	Teacher teacher;
	teacher.base.age = 30;
	Person_SayAge(teacher.base);
	teacher.nStudent = 10;
	Teacher_Bark(teacher);

	return 0;
}
