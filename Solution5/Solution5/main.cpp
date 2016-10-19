#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>
/*На логическим уровне разрабатываемая структура данных представляет собой обычную линейную последовательность элементов
(например, строк) со стандартным набором операций (добавление в конец, вставка и удаление по логическому номеру, сортировка, 
бинарный поиск, вставка с сохранением порядка, сохранение и загрузка из текстового файла, выравнивание 
(балансировка - выравнивание размерностей структур данных нижнего уровня). 

Физическая структура данных имеет два уровня. На нижнем уровне поддерживается ограничение размерности структуры данных: 
при переполнении она разбивается пополам, соответствующие изменения вносятся в верхний уровень. 
При выполнении работы произвести измерение зависимости «грязного» времени работы программы и ее трудоемкости 
(количества базовых операций). Оценить вид полученной зависимости (линейно-логарифмическая, квадратичная).

Список - каждый элемент является заголовком односвязного списка. Элемент списка второго уровня содержит указатель на строку. 
(Включение элемента последним в список производить с учетом выравнивания длины текущего и следующего списков).*/

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

/*Функция fillMyList() заполняет строками список второго уровня (MyList), на вход
получает заголовочный элемент списка и размер списка. Возвращает 1 если произошло переполнение*/
int fillMyList(MyList&, const int);
/*Функция проверяет не заполнился ли список. Возвращает false если можно производить вставку и true - если список полный.
В качестве параметров принимает указатель на заголовок списка и размер списка*/
bool isFull(MyList*, const int);
/*Функция инициализирует список*/
MyListMain *initMyListMain();

/*Функция первый раз заполняет список списков*/
void firstFillTheList(MyListMain*,const int);
/*Функция добавляет элемент главного списка*/
void addMainList(MyListMain*);
/*Функция создает элемент вторичного списка и возвращает указатель на него*/
MyList * createElemMyList(const int);
/*Функция выводит на экран список списков*/
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
	MyListMain * start;							//Заводим указатель
	start = headMain;							//и указываем его туда же куда указывает заголовок списка
	printf("Begin to fill the list of list...\n");
	int i = 0;									//заводим переменную для хранения глобального индекса
	
	while (true)								/*	Инициализируем цикл по первичному списку списков
													условиями выходя будет желание пользователя прекратить ввод*/
	{
		int indxOfSecList = 0;					//Инициализируем счетчик, содержащий индекс каждого элемента во вторичном списке
		while (true)
		{
			if (indxOfSecList == 0)				//проверка не первый элемент во вторичном списке (проверка на заголовок)
			{
				start->headOfMylist = createElemMyList(i);				//создаем заголовочный элемент вторичного списка
				start->headOfMylist->next = NULL;						//указываем в нем что следующего нет
								
				indxOfSecList++;										//увеличиваем счетчик текущего элемента в списке
				i++;													//увеличиваем глобальный индекс
				
				int isExit1 = 0;											//
				printf("Continue fill the Secondary List?Y(1)/N(0)\n>>>");	//печатаем условия выхода из цикла ввода элементов вторичного цикла
				scanf("%d", &isExit1);										//

				if (isExit1 != 1)
				{
					printf("List%d fill is break.\n", start->indx);			
					system("pause");
					system("cls");
					addMainList(start);										/*если нажали выход из вторичного цикла то создаем новый элемент первичного цикла*/
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
		printf("Continue fill the List of List?Y(1)/N(0)\n>>>");	//Это все условие выхода с вопросом и считыванием ответа
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