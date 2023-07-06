#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//学生信息
typedef struct _Student
{
	int stuNum;
	char name[20];
	int score;
}Student;

//结点信息
typedef struct _Node
{
	Student student;
	struct _Node* next; //下一个结点的地址位置
}Node;

void sortStudent(Node* head);
void deleteStudent(Node* head);
void modifyStudent(Node* head);
void loadStudent(Node* head);
void saveStudent(Node* head);
void findStudend(Node* head);
void countStudent(Node* head);
void printStudent(Node* head);
void inputStudent(Node* head);
void welcome();