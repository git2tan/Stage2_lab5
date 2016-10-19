#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
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
	int gIndx;
	MyList * next;
};
struct MyListMain
{
	MyListMain * next;
	MyListMain * prev;
	MyList * headOfMylist;
	int indx;
};

char * getInput();
void addToTailOfMyList(MyList * const, MyList *const);
void showMyList(MyList*const);

/*������� fillMyList() ��������� �������� ������ ������� ������ (MyList), �� ����
�������� ������������ ������� ������ � ������ ������. ���������� 1 ���� ��������� ������������*/
int fillMyList(MyList&, const int);
/*������� ��������� �� ���������� �� ������. ���������� false ���� ����� ����������� ������� � true - ���� ������ ������.
� �������� ���������� ��������� ��������� �� ��������� ������ � ������ ������*/
bool isFull(MyList*, const int);
/*������� �������������� ������*/
MyListMain *initMyListMain();

/*������� ������ ��� ��������� ������ �������*/
void firstFillTheList(MyListMain*,const int);
/*������� ��������� ������� �������� ������*/
void addMainList(MyListMain*);
/*������� ������� ������� ���������� ������ � ���������� ��������� �� ����*/
MyList * createElemMyList(const int);
/*������� ������� �� ����� ������ �������*/
void ShowMyListMain(MyListMain *);

///////////////////////////////////////////////////MAIN//////////////////////////////////////////////////////////////////
void main()
{
	
	MyListMain *headMain = initMyListMain();
	int MaxSize = 4;

	//fillMyList(*(headMain->headOfMylist), SizeOfMyList);
	//showMyList(headMain->headOfMylist);
	//printf("is full? - %s\n",isFull(headMain->headOfMylist,SizeOfMyList)?"full":"not full");

	firstFillTheList(headMain,MaxSize);
	system("cls");
	ShowMyListMain(headMain);
	printf("END OF PROGRAMM");
	system("pause");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char * getInput()
{
	char buf[255] = { 0 };
	char * returnableBuf;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	scanf("%[^\n]s", buf);
	int bufsize = (strlen(buf) + 1);
	returnableBuf = (char*)malloc(sizeof(char)*bufsize);
	strcpy(returnableBuf, buf);

	return returnableBuf;
}
void addToTailOfMyList(MyList *const head, MyList * const paste)
{
	MyList *current;
	if (head != NULL)
	{
		for (current = head; current->next != NULL; current = current->next);
	}
	else
		current = head;
	current->next = paste;
	paste->next = NULL;
}
void showMyList(MyList * const head)
{
	for (MyList * current = head; current != NULL; current = current->next)
	{
		printf("%dst element of MyList is: %s\n",current->gIndx,current->content);
	}
}
int fillMyList(MyList &head, const int SizeOfMyList)
{
	int i = 0;
	while (true)
	{
		if (i == 0)
		{
			//head = (MyList*)malloc(sizeof(MyList));
			head.next = NULL;
			head.gIndx = i;
			printf("Please, input the %dst element of MyList\n>>>", i);
			head.content = getInput();
		}
		else
		{
			printf("Please, input the %dst element of MyList\n>>>", i);
			MyList *tmp;
			tmp = (MyList*)malloc(sizeof(MyList));
			tmp->content = getInput();
			tmp->gIndx = i;
			addToTailOfMyList(&head, tmp);
		}
		
		i++;
		if (i == SizeOfMyList)
		{
			printf("List is full\n");
			system("pause");
			return 1;
		}
		
		int isExit = 0;
		printf("Continue?Y(1)/N(0)\n>>>");
		scanf("%d", &isExit);

		if (isExit != 1)
			break;
		
	}
	
	return 0;

}
bool isFull(MyList* head, const int size)
{
	int count=0;
	for (MyList * current = head; current != NULL; current = current->next)
	{
		count++;
	}
	if (count >= size)
		return true;
	else
		return	false;
}

MyListMain *initMyListMain()
{
	MyListMain *headMain;
	headMain = (MyListMain*)malloc(sizeof(MyListMain));
	headMain->next = headMain->prev = NULL;
	headMain->indx = 0;
	//headMain->headOfMylist = (MyList*)malloc(sizeof(MyList));
	//headMain->headOfMylist->content = NULL;
	//headMain->headOfMylist->next = NULL;
	return headMain;
}
void firstFillTheList(MyListMain* headMain, const int maxSize)
{
	MyListMain * start;							//������� ���������
	start = headMain;							//� ��������� ��� ���� �� ���� ��������� ��������� ������
	printf("Begin to fill the list of list...\n");
	int i = 0;									//������� ���������� ��� �������� ����������� �������
	
	while (true)								/*	�������������� ���� �� ���������� ������ �������
													��������� ������ ����� ������� ������������ ���������� ����*/
	{
		int indxOfSecList = 0;					//�������������� �������, ���������� ������ ������� �������� �� ��������� ������
		while (true)
		{
			if (indxOfSecList == 0)				//�������� �� ������ ������� �� ��������� ������ (�������� �� ���������)
			{
				start->headOfMylist = createElemMyList(i);				//������� ������������ ������� ���������� ������
				start->headOfMylist->next = NULL;						//��������� � ��� ��� ���������� ���
								
				indxOfSecList++;										//����������� ������� �������� �������� � ������
				i++;													//����������� ���������� ������
				
				int isExit1 = 0;											//
				printf("Continue fill the Secondary List?Y(1)/N(0)\n>>>");	//�������� ������� ������ �� ����� ����� ��������� ���������� �����
				scanf("%d", &isExit1);										//

				if (isExit1 != 1)
				{
					printf("List%d fill is break.\n", start->indx);			
					system("pause");
					system("cls");
					addMainList(start);										/*���� ������ ����� �� ���������� ����� �� ������� ����� ������� ���������� �����*/
					start = start->next;
					break;
				}
				continue;	
			}
			if (isFull(start->headOfMylist, maxSize))
			{
				printf("List%d is full\n",start->indx);
				system("pause");
				addMainList(start);
				start = start->next;
				break;
			}
			else
			{
				addToTailOfMyList(headMain->headOfMylist,createElemMyList(i));
			}
			indxOfSecList++;
			i++;
			int isExit1 = 0;
			printf("Continue fill the Secondary List?Y(1)/N(0)\n>>>");
			scanf("%d", &isExit1);

			if (isExit1 != 1)
			{
				printf("List%d fill is break.\n", start->indx);
				system("pause");
				addMainList(start);
				start = start->next;
				break;
			}

		}

		int isExit0 = 0;											//
		printf("Continue fill the List of List?Y(1)/N(0)\n>>>");	//��� ��� ������� ������ � �������� � ����������� ������
		scanf("%d", &isExit0);										//
		if (isExit0 == 0)											//
			break;													//

	}
	
}
void addMainList(MyListMain* headMain)
{
	MyListMain *tail = (MyListMain*)malloc(sizeof(MyListMain));
	tail->headOfMylist = (MyList*)malloc(sizeof(MyList));
	tail->headOfMylist = NULL;
	//tail->headOfMylist->next = NULL;
	tail->next = NULL;
	if (headMain->next == NULL)
	{
		headMain->next = tail;
		
		tail->prev = headMain;
		tail->indx = headMain->indx + 1;
	}
	else
	{
		MyListMain * tmpList;
		for (tmpList = headMain; tmpList->next != NULL; tmpList = tmpList->next);
		tmpList->next = tail;
		tail->prev = tmpList;
		tail->indx = tmpList->indx + 1;
	}
}
MyList * createElemMyList(const int inpIndx)
{
	MyList *tmp = (MyList*)malloc(sizeof(MyList));
	printf("Please, input the %dst element of MyList\n>>>",inpIndx);
	tmp->content = getInput();
	tmp->next = NULL;
	tmp->gIndx = inpIndx;
	return tmp;
}
void ShowMyListMain(MyListMain * headMain)
{
	int i = 0;
	for (MyListMain * current0 = headMain; current0 != NULL; current0 = current0->next, i++)
	{
		printf("Print %dst MainList:\n",i);
		showMyList(current0->headOfMylist);
		printf("\n");
	}
}