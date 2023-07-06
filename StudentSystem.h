#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//ѧ����Ϣ
typedef struct _Student
{
	int stuNum;
	char name[20];
	int score;
}Student;

//�����Ϣ
typedef struct _Node
{
	Student student;
	struct _Node* next; //��һ�����ĵ�ַλ��
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