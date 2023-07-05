#include "StudentSystem.h"

//函数返回一个指向新分配内存的指针 返回新分配类型指针

//通用的管理系统头结点模式(深度理解结构体指针)

//2023/4/23   完结

int main()
{
	//创建头结点
	Node* head = malloc(sizeof(Node)); //结构体类型的指针
	head->next = NULL;
	loadStudent(head);

	while (1)
	{
		welcome();
		char c = _getch(); //与getchar相比不用回车, 回车被吸收了

		switch (c)
		{
		case '1':
			inputStudent(head);//录入学生信息
			break;
		case '2':
			printStudent(head);//打印学生信息
			break;
		case '3': 
			countStudent(head);//统计学生人数
			break;
		case '4': 
		    findStudend(head);//查找学生信息
			break;
		case '5': 
			modifyStudent(head);//修改学生信息
			break;
		case '6': 
			deleteStudent(head);//删除学生信息
			break;
		case '7':  
			sortStudent(head);//按成绩排序, 排序算法采用冒泡排序
			break;
		case '8': 
			system("cls");
			printf("感谢使用\n");
			exit(0);//退出系统
			break;
		default:
			printf("请重新输入\n");
			//暂停程序
			system("pause");
			//清空控制台
			system("cls");
			break;
		}
	}

	return 0;
	}

void welcome()
{
	printf("*********************************\n");
	printf("*\t学生信息管理系统\t*\n");
	printf("*********************************\n");
	printf("*\t请选择功能列表\t\t*\n");
	printf("*********************************\n");
	printf("*\t1.录入学生信息\t\t*\n");
	printf("*\t2.打印学生信息\t\t*\n");
	printf("*\t3.统计学生人数\t\t*\n");
	printf("*\t4.查找学生信息\t\t*\n");
	printf("*\t5.修改学生信息\t\t*\n");
	printf("*\t6.删除学生信息\t\t*\n");
	printf("*\t7.按成绩排序\t\t*\n");
	printf("*\t8.退出系统\t\t*\n");
	printf("*********************************\n");


}

void inputStudent(Node* head)  //void* 类型的指针可以针对任意数据类型
{
	Node* fresh = malloc(sizeof(Node));
	fresh->next = NULL;
	printf("请输入学生的学号，姓名，成绩\n");
	scanf("%d%s%d", &fresh->student.stuNum, fresh->student.name, &fresh->student.score);

	Node* move = head;
	while (move->next != NULL)
	{
		move = move->next;  //不停的转移链表地址
	}
	//将学生插入到尾部
	move->next = fresh;  //则此时move->next不为空

	saveStudent(head);
	//暂停程序
	system("pause");
	//清空控制台
	system("cls");
}  //核心

void printStudent(Node* head)
{
	Node* move = head->next;
	while (move != NULL)
	{
		printf("学号: %d 姓名: %s 成绩: %d\n", move->student.stuNum, move->student.name, move->student.score);
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

	printf("学生的总人数为:%d\n", count);

	system("pause");
	system("cls");
}

void findStudend(Node* head)
{
	printf("请输入查找学号: ");
	int stuNum;
	scanf("%d", &stuNum);
	Node* move = head->next;
	while (move != NULL)
	{
		if (stuNum == move->student.stuNum)
		{
			printf("学号: %d 姓名:%s 成绩:%d\n", move->student.stuNum, move->student.name, move->student.score);
			//暂停程序
			system("pause");
			//清空控制台
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("未找到学生信息\n");

	//暂停程序
	system("pause");
	//清空控制台
	system("cls");
}

void saveStudent(Node* head)  //长时间存储
{
	//打开文件
	FILE* file = fopen("./stu.info", "w");
	if (file == NULL)
	{
		printf("打开文件夹\n");
		return;
	}

	Node* move = head->next;
	while (move != NULL)
	{
		//将结构体写入文件
		if (fwrite(&move->student, sizeof(Student), 1, file) != 1)  //fwrite函数返回写入的个数
		{
			printf("保存%s出现错误\n", move->student.name);
		}
		move = move->next;

	}

	fclose(file);
}

void loadStudent(Node* head)
{
	//打开文件
	FILE* file = fopen("./stu.info", "r");
	if (file == NULL)
	{
		printf("未找到读取文件, 读取失败\n");
		return;
	}
	//创建一个结点
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
	printf("读取成功\n");
}

void modifyStudent(Node* head)
{
	printf("请输入要修改学生的学号: ");
	int stuNum;
	scanf("%d", &stuNum);
	Node* move = head->next;
	while (move != NULL)
	{
		if (move->student.stuNum == stuNum)
		{
			printf("请输入学生姓名, 成绩\n");
			scanf("%s%d", move->student.name, &move->student.score);
			printf("修改成功\n");
			saveStudent(head);
			//暂停程序
			system("pause");
			//清空控制台
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("修改失败\n");
	//暂停程序
	system("pause");
	//清空控制台
	system("cls");
}

void deleteStudent(Node* head)
{
	printf("请输入要删除学生的学号:\n");
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
			printf("删除成功\n");
			//暂停程序
			system("pause");
			//清空控制台
			system("cls");
			return;
		}
	}
	printf("删除失败\n");
	//暂停程序
	system("pause");
	//清空控制台
	system("cls");
}

void sortStudent(Node* head)
{
	Node* save = NULL;
	Node* move = NULL; //排序优化后

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