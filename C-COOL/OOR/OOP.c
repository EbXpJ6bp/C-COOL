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

	//===カプセル化のサンプル===
	//Person.cのMAGIC_NUMBERやPerson_Secretは
	//Person.cからしか参照しない
	printf("===カプセル化のサンプル===\n");
	Person_Test();

	//===ポリモーフィズムのサンプル===
	printf("===ポリモーフィズムのサンプル===\n");
	Animal person = newPerson();//人間のオブジェクトを作成
	Animal dog = newDog();   //犬のオブジェクトを作成

	person.Bark();
	dog.Bark();

	//===継承のサンプル===
	printf("===継承のサンプル===\n");
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
