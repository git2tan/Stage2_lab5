#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <iostream>
/*�� ���������� ������ ��������������� ��������� ������ ������������ ����� ������� �������� ������������������ ���������
(��������, �����) �� ����������� ������� �������� (���������� � �����, ������� � �������� �� ����������� ������, ����������, 
�������� �����, ������� � ����������� �������, ���������� � �������� �� ���������� �����, ������������ 
(������������ - ������������ ������������ �������� ������ ������� ������). 

���������� ��������� ������ ����� ��� ������. �� ������ ������ �������������� ����������� ����������� ��������� ������: 
��� ������������ ��� ����������� �������, ��������������� ��������� �������� � ������� �������. 
��� ���������� ������ ���������� ��������� ����������� ��������� ������� ������ ��������� � �� ������������ 
(���������� ������� ��������). ������� ��� ���������� ����������� (�������-���������������, ������������).

������ - ������ ������� �������� ���������� ������������ ������. ������� ������ ������� ������ �������� ��������� �� ������. 
(��������� �������� ��������� � ������ ����������� � ������ ������������ ����� �������� � ���������� �������).*/

struct MyList
{
	char *content;
	MyList * next;
};

char * getInput();
void addToTailOfMyList(MyList *,MyList *);
void showMyList(MyList*);


void main()
{
	MyList * head;
	head = (MyList*)malloc(sizeof(MyList));
	head = NULL;
	int i = 1;
	while (true)
	{
		if (i == 1)
		{
			head = (MyList*)malloc(sizeof(MyList));
			head->next = NULL;
			printf("Please, input the %dst element of MyList\n>>>", i);
			head->content = getInput();
		}
		else
		{
			printf("Please, input the %dst element of MyList\n>>>", i);
			MyList *tmp;
			tmp = (MyList*)malloc(sizeof(MyList));
			tmp->content = getInput();
			addToTailOfMyList(head, tmp);
		}
			
		int isExit = 0;
		printf("Continue?Y(1)/N(0)\n>>>");
		scanf("%d", &isExit);
		
		if (isExit != 1)
			break;
		i++;
	}
	showMyList(head);
	system("pause");
}


char * getInput()
{
	char buf[255];
	char * returnableBuf;
	//printf("Input data?\n");
	scanf("%s", buf);
	int bufsize = (strlen(buf) + 1);
	 returnableBuf = (char*)malloc(sizeof(char)*bufsize);
	strcpy(returnableBuf, buf);

	return returnableBuf;
}
void addToTailOfMyList(MyList *head, MyList * paste)
{
	MyList *current;
	if (head != NULL)
		for (current = head; current->next != NULL; current = current->next);
	else
		current = head;
	current->next = paste;
	paste->next = NULL;
}
void showMyList(MyList * head)
{
	int i = 1;
	for (MyList * current = head; current != NULL; current = current->next)
	{
		printf("%dst element of MyList is: %s\n",i,current->content);
		i++;
	}
}