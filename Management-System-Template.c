#include "StudentSystem.h"

//��������һ��ָ���·����ڴ��ָ�� �����·�������ָ��

//ͨ�õĹ���ϵͳͷ���ģʽ(������ṹ��ָ��)

//2023/4/23   ���

int main()
{
	//����ͷ���
	Node* head = malloc(sizeof(Node)); //�ṹ�����͵�ָ��
	head->next = NULL;
	loadStudent(head);

	while (1)
	{
		welcome();
		char c = _getch(); //��getchar��Ȳ��ûس�, �س���������

		switch (c)
		{
		case '1':
			inputStudent(head);//¼��ѧ����Ϣ
			break;
		case '2':
			printStudent(head);//��ӡѧ����Ϣ
			break;
		case '3': 
			countStudent(head);//ͳ��ѧ������
			break;
		case '4': 
		    findStudend(head);//����ѧ����Ϣ
			break;
		case '5': 
			modifyStudent(head);//�޸�ѧ����Ϣ
			break;
		case '6': 
			deleteStudent(head);//ɾ��ѧ����Ϣ
			break;
		case '7':  
			sortStudent(head);//���ɼ�����, �����㷨����ð������
			break;
		case '8': 
			system("cls");
			printf("��лʹ��\n");
			exit(0);//�˳�ϵͳ
			break;
		default:
			printf("����������\n");
			//��ͣ����
			system("pause");
			//��տ���̨
			system("cls");
			break;
		}
	}

	return 0;
	}

void welcome()
{
	printf("*********************************\n");
	printf("*\tѧ����Ϣ����ϵͳ\t*\n");
	printf("*********************************\n");
	printf("*\t��ѡ�����б�\t\t*\n");
	printf("*********************************\n");
	printf("*\t1.¼��ѧ����Ϣ\t\t*\n");
	printf("*\t2.��ӡѧ����Ϣ\t\t*\n");
	printf("*\t3.ͳ��ѧ������\t\t*\n");
	printf("*\t4.����ѧ����Ϣ\t\t*\n");
	printf("*\t5.�޸�ѧ����Ϣ\t\t*\n");
	printf("*\t6.ɾ��ѧ����Ϣ\t\t*\n");
	printf("*\t7.���ɼ�����\t\t*\n");
	printf("*\t8.�˳�ϵͳ\t\t*\n");
	printf("*********************************\n");


}

void inputStudent(Node* head)  //void* ���͵�ָ��������������������
{
	Node* fresh = malloc(sizeof(Node));
	fresh->next = NULL;
	printf("������ѧ����ѧ�ţ��������ɼ�\n");
	scanf("%d%s%d", &fresh->student.stuNum, fresh->student.name, &fresh->student.score);

	Node* move = head;
	while (move->next != NULL)
	{
		move = move->next;  //��ͣ��ת�������ַ
	}
	//��ѧ�����뵽β��
	move->next = fresh;  //���ʱmove->next��Ϊ��

	saveStudent(head);
	//��ͣ����
	system("pause");
	//��տ���̨
	system("cls");
}  //����

void printStudent(Node* head)
{
	Node* move = head->next;
	while (move != NULL)
	{
		printf("ѧ��: %d ����: %s �ɼ�: %d\n", move->student.stuNum, move->student.name, move->student.score);
		move = move->next;
	}

	system("pause");
	system("cls");
}

void countStudent(Node* head)
{
	int count = 0;

	Node* move = head->next;
	while (move != NULL)
	{
		count++;
		move = move->next;
	}

	printf("ѧ����������Ϊ:%d\n", count);

	system("pause");
	system("cls");
}

void findStudend(Node* head)
{
	printf("���������ѧ��: ");
	int stuNum;
	scanf("%d", &stuNum);
	Node* move = head->next;
	while (move != NULL)
	{
		if (stuNum == move->student.stuNum)
		{
			printf("ѧ��: %d ����:%s �ɼ�:%d\n", move->student.stuNum, move->student.name, move->student.score);
			//��ͣ����
			system("pause");
			//��տ���̨
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("δ�ҵ�ѧ����Ϣ\n");

	//��ͣ����
	system("pause");
	//��տ���̨
	system("cls");
}

void saveStudent(Node* head)  //��ʱ��洢
{
	//���ļ�
	FILE* file = fopen("./stu.info", "w");
	if (file == NULL)
	{
		printf("���ļ���\n");
		return;
	}

	Node* move = head->next;
	while (move != NULL)
	{
		//���ṹ��д���ļ�
		if (fwrite(&move->student, sizeof(Student), 1, file) != 1)  //fwrite��������д��ĸ���
		{
			printf("����%s���ִ���\n", move->student.name);
		}
		move = move->next;

	}

	fclose(file);
}

void loadStudent(Node* head)
{
	//���ļ�
	FILE* file = fopen("./stu.info", "r");
	if (file == NULL)
	{
		printf("δ�ҵ���ȡ�ļ�, ��ȡʧ��\n");
		return;
	}
	//����һ�����
	Node* fresh = malloc(sizeof(Node));
	fresh->next = NULL;
	Node* move = head;
	while (fread(&fresh->student, sizeof(Student), 1, file) == 1)
	{
		move->next = fresh;
		move = fresh;
		fresh = malloc(sizeof(Node));
		fresh->next = NULL;
	}
	free(fresh);
	fclose(file);
	printf("��ȡ�ɹ�\n");
}

void modifyStudent(Node* head)
{
	printf("������Ҫ�޸�ѧ����ѧ��: ");
	int stuNum;
	scanf("%d", &stuNum);
	Node* move = head->next;
	while (move != NULL)
	{
		if (move->student.stuNum == stuNum)
		{
			printf("������ѧ������, �ɼ�\n");
			scanf("%s%d", move->student.name, &move->student.score);
			printf("�޸ĳɹ�\n");
			saveStudent(head);
			//��ͣ����
			system("pause");
			//��տ���̨
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("�޸�ʧ��\n");
	//��ͣ����
	system("pause");
	//��տ���̨
	system("cls");
}

void deleteStudent(Node* head)
{
	printf("������Ҫɾ��ѧ����ѧ��:\n");
	int stuNum = 0;
	scanf("%d", &stuNum);

	Node* move = head;
	while (move->next != NULL)
	{
		if (move->next->student.stuNum == stuNum)
		{
			Node* tmp = move->next;
			move->next = move->next->next;
			free(tmp);
			tmp = NULL;
			saveStudent(head);
			printf("ɾ���ɹ�\n");
			//��ͣ����
			system("pause");
			//��տ���̨
			system("cls");
			return;
		}
	}
	printf("ɾ��ʧ��\n");
	//��ͣ����
	system("pause");
	//��տ���̨
	system("cls");
}

void sortStudent(Node* head)
{
	Node* save = NULL;
	Node* move = NULL; //�����Ż���

	for (Node* turn = head->next; turn->next != NULL; turn = turn->next)
	{
		for (move = head->next; move->next != save; move = move->next)
		{
			if (move->student.score > move->next->student.score)
			{
				Student tmp = move->student;
				move->student = move->next->student;
				move->next->student = tmp;
			}
		}
		save = move;
	}

	printStudent(head);
}