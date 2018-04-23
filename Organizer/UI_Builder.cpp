#include "UI_Builder.h"

extern COORD position_up;
extern COORD position_input;
extern COORD position_tab;
extern COORD position_down;
extern COORD position;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((background << 4) | text));
}

void CatRowDrawer(int i, Category Cat, bool isCurCat = false);
void CatRowDrawerEmp();
void TaskRowDrawer(int i, Task task, bool isCurTask = false, ConsoleColor Color = LightGray);
void TaskRowDrawerEmp();

void UI::Header()
{
	 
	cout << endl;	
	cout << "=======================================================================================================================" << endl;	
	cout << "|  МЕНЮ УПРАВЛЕНИЯ                    |   Г - Вернуться в гл. меню             В - Выйти из программы                 |" << endl;
	cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
	cout << "|  Категории:                         |   Задачи:                                                                     |" << endl;
	cout << "|  К - Создать категорию              |   З - Создать задачу                   С - Сротировать по сроку               |" << endl;
	cout << "|  Д - Перейти в др. категорию        |   Т - Выбрать др. задачу               П - Сортировать по приоритету          |" << endl;
	cout << "|  И - Изменить порядок категорий     |   Р - Редактировать задачу             Ф - Установить фильтр                  |" << endl;
	cout << "|  Н - Изменить название категории    |   О - Отметить выполненной             Ч - Отобразить / скрыть выполненные    |" << endl;
	cout << "|  У - Удалить категорию              |   М - Переместить в др. категорию      Х - Отменить сортировку и фильтры      |" << endl;	
	cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
	cout << "|  Установленные опции:               | Сортировка: -          | Фильтр: -           |  Отображать выполненные: -     |" << endl;
	cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
	cout << "|  Выберите необходимое действие:                                                                                     |" << endl;	
	cout << "|                                                                                                                     |" << endl;
	cout << "|=====================================================================================================================|" << endl;
    cout << "|  Категория                | #  | Задача                                            |       Срок       |  Приоритет  |" << endl;
    cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
    cout << "=======================================================================================================================" << endl;  
}

void UI::StatusLine(Category Cat)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.Y = position_up.Y - 2;
	SetConsoleCursorPosition(hConsole, position);

	struct tm *date;
	time_t tt = time(NULL);
	date = localtime(&tt);
	int today_d = date->tm_mday;
	int today_m = date->tm_mon + 1;
	int today_y = date->tm_year + 1900;
	int today = today_y * 10000 + today_m * 100 + today_d;

	cout << "|  Установленные опции:               ";

	if ( Cat.GetSortedByDate() == true )
		cout << "| Сортировка: С          ";
	else if ( Cat.GetSortedByPrior() == true )
		cout << "| Сортировка: П          ";
	else
		cout << "| Сортировка: -          ";

	if (Cat.GetDateFilter() != 0)
	{
		char datestr[9] = "";
		sprintf(datestr, "%d", Cat.GetDateFilter());		
		cout << "| Фильтр: ";
		if (Cat.GetDateFilter() == today)
			cout << "Cегодня     ";
		else if (Cat.GetDateFilter() == today + 1)
			cout << "Завтра      ";
		else
			cout << datestr[6] << datestr[7] << "." << datestr[4] << datestr[5] << "." << datestr[0] << datestr[1] << datestr[2] << datestr[3] << "  ";
	}
	else if (Cat.GetPriorFilter() != 0)
	{
		cout << "| Фильтр: П = ";
		cout << Cat.GetPriorFilter() << "       ";
	}
	else
		cout << "| Фильтр: -           ";
		
	if (Cat.GetShowCompleted() == true)
		cout << "|  Отображать выполненные: О     |";
	else if (Cat.GetShowCompleted() == false)
		cout << "|  Отображать выполненные: С     |";
}

void UI::Options(char input)
{		
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position_up);
	switch (input)
	{	
	case 'к':
	case 'К':		
		cout << "|  Выберите необходимое действие: К - Создать категорию                                                               |" << endl;		
		cout << "|  Введите название категории:                                                                                        |" << endl;		
		position_input.X = 31;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;	
	case 'д':
	case 'Д':		
		cout << "|  Выберите необходимое действие: Д - Перейти в др. категорию                                                         |" << endl;		
		cout << "|  Введите номер категории:                                                                                           |" << endl;		
		position_input.X = 28;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'и':
	case 'И':		
		cout << "|  Выберите необходимое действие: И - Изменить порядок категорий                                                      |" << endl;		
		cout << "|  Введите номер позиции:                                                                                             |" << endl;		
		position_input.X = 26;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'н':
	case 'Н':
		cout << "|  Выберите необходимое действие: Н - Изменить название категории                                                     |" << endl;
		cout << "|  Введите новое название:                                                                                            |" << endl;
		position_input.X = 27;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'у':
	case 'У':
		cout << "|  Выберите необходимое действие: У - Удалить категорию                                                               |" << endl;
		cout << "|  Подтверждаете удаление? Да(Д) / Нет(Н):                                                                            |" << endl;
		position_input.X = 43;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'з':
	case 'З':
		cout << "|  Выберите необходимое действие: З - Создать задачу                                                                  |" << endl;
		cout << "|  Введите название задачи:                                                                                           |" << endl;
		position_input.X = 28;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case '4':
		cout << "|  Выберите необходимое действие: З - Создать задачу                                                                  |" << endl;
		cout << "|  Введите срок выполнения (дд.мм.гггг) / - :                                                                         |" << endl;
		position_input.X = 46;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case '5':
		cout << "|  Выберите необходимое действие: З - Создать задачу                                                                  |" << endl;
		cout << "|  Введите приоритет (1 / 2 / 3):                                                                                     |" << endl;
		position_input.X = 34;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'т':
	case 'Т':
		cout << "|  Выберите необходимое действие: В - Выбрать др. задачу                                                              |" << endl;
		cout << "|  Введите номер задачи:                                                                                              |" << endl;
		position_input.X = 25;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'р':
	case 'Р':
		cout << "|  Выберите необходимое действие: Р - Редактировать задачу                                                            |" << endl;
		cout << "|  Изменить Название(1) / Срок(2) / Приоритет(3):                                                                     |" << endl;
		position_input.X = 50;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;	
	case '1':
		cout << "|  Выберите необходимое действие: Р - Редактировать задачу                                                            |" << endl;
		cout << "|  Введите новое название:                                                                                            |" << endl;
		position_input.X = 27;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case '2':
		cout << "|  Выберите необходимое действие: Р - Редактировать задачу                                                            |" << endl;
		cout << "|  Введите новый срок (дд.мм.гггг) / - :                                                                              |" << endl;
		position_input.X = 41;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case '3':
		cout << "|  Выберите необходимое действие: Р - Редактировать задачу                                                            |" << endl;
		cout << "|  Введите новый приоритет (1 / 2 / 3):                                                                               |" << endl;
		position_input.X = 40;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;	
	case 'о':
	case 'О':
		cout << "|  Выберите необходимое действие: О - Отметить выполненной                                                            |" << endl;
		cout << "|  Отметить выполненной? Да(Д) / Нет(Н):                                                                              |" << endl;
		position_input.X = 41;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'м':
	case 'М':
		cout << "|  Выберите необходимое действие: М - Переместить в др. категорию                                                     |" << endl;
		cout << "|  Укажите номер категории:                                                                                           |" << endl;
		position_input.X = 28;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'с':
	case 'С':
		cout << "|  Выберите необходимое действие: С - Сротировать по сроку                                                            |" << endl;
		cout << "|  Сортировать задачи по сроку? Да(Д) / Нет(Н):                                                                       |" << endl;
		position_input.X = 48;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'п':
	case 'П':
		cout << "|  Выберите необходимое действие: П - Сортировать по приоритету                                                       |" << endl;
		cout << "|  Сортировать задачи по приоритету? Да(Д) / Нет(Н):                                                                  |" << endl;
		position_input.X = 53;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'х':
	case 'Х':
		cout << "|  Выберите необходимое действие: Х - Отменить сортировку                                                             |" << endl;
		cout << "|  Отменить сортировку задач? Да(Д) / Нет(Н):                                                                         |" << endl;
		position_input.X = 46;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'ч':
	case 'Ч':
		cout << "|  Выберите необходимое действие: Ч - Отобразить / скрыть выполненные                                                 |" << endl;
		cout << "|  Отобразить(О) / Скрыть(С) выполненные задачи:                                                                      |" << endl;
		position_input.X = 49;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case 'ф':
	case 'Ф':
		cout << "|  Выберите необходимое действие: Ф - Установить фильтр                                                               |" << endl;
		cout << "|  Выборка по Срокам(С) / по Приоритету(П):                                                                           |" << endl;
		position_input.X = 44;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case '6':
		cout << "|  Выберите необходимое действие: Ф - Установить фильтр                                                               |" << endl;
		cout << "|  Введите срок - Сегодня(С) / Завтра(З) / До (дд.мм.гггг):                                                              |" << endl;
		position_input.X = 60;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	case '7':
		cout << "|  Выберите необходимое действие: Ф - Установить фильтр                                                               |" << endl;
		cout << "|  Введите приоритет (1 / 2 / 3):                                                                                     |" << endl;
		position_input.X = 34;
		position_input.Y = position_up.Y + 1;
		SetConsoleCursorPosition(hConsole, position_input);
		break;
	}	
}

void UI::MenuInput()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position_up);	
	cout << "|  Выберите необходимое действие:                                                                                     |" << endl;
	cout << "|                                                                                                                     |" << endl;	
	position_input.X = 34;
	position_input.Y = position_up.Y;
	SetConsoleCursorPosition(hConsole, position_input);
}

void UI::MenuInput(string WarnMessage)
{	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position_up);
	string Spaces;
	Spaces.resize(115 - WarnMessage.size(), ' ');
	string Row = "|  " + WarnMessage + Spaces + "|";
	cout << "|  Выберите необходимое действие:                                                                                     |" << endl;
	cout << Row << endl;
	position_input.X = 34;
	position_input.Y = position_up.Y;
	SetConsoleCursorPosition(hConsole, position_input);

	Sleep(1500);

	SetConsoleCursorPosition(hConsole, position_up);
	cout << "|  Выберите необходимое действие:                                                                                     |" << endl;
	cout << "|                                                                                                                     |" << endl;
	
	position_input.X = 34;
	position_input.Y = position_up.Y;
	SetConsoleCursorPosition(hConsole, position_input);
}

void UI::MenuInput2(string Input1, string &Input2)
{	
	UI::Options(Input1[0]);
	if (Input1 == "1" || Input1 == "2" || Input1 == "3" || Input1 == "4" || Input1 == "5" || Input1 == "6" || Input1 == "7")
		cin >> Input2;	
	else
	{		
		cin.get();
		getline(cin, Input2);		
	}	
}

void UI::Table(vector <Category> CSet, int CCount, int CurCat)
{	
	int rows;
	int TaskRowCounter = 0;
	int TaskComRowCounter = 0;
	int Tsize = CSet[CurCat].TasksSet.size();
	int TCsize = CSet[CurCat].TasksCompleted.size();
	int TaskRowDrawedCount = 0;	
	int TaskFilteredByDateDrawed = 0;
	int TaskFilteredByPriorDrawed = 0;
	int TaskComFilteredByDateDrawed = 0;
	int TaskComFilteredByPriorDrawed = 0;
	
	StatusLine(CSet[CurCat]);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	
	position.Y = position_up.Y + 2;
	SetConsoleCursorPosition(hConsole, position);
	cout << "|=====================================================================================================================|" << endl;
	SetConsoleCursorPosition(hConsole, position_tab);
	
	if (CSet.size() == 0)
		goto empty;	
	
	if (CSet[CurCat].GetDateFilter() == 0 && CSet[CurCat].GetPriorFilter() == 0)
	{
		TaskRowCounter = Tsize;
		if (CSet[CurCat].GetShowCompleted() == true)
			TaskComRowCounter = TCsize;
	}		
	else if (CSet[CurCat].GetDateFilter() != 0)
	{
		for (int t = 0; t < Tsize; t++)
		{			
			if (CSet[CurCat].TasksSet[t].GetTaskDateD() == CSet[CurCat].GetDateFilter())
				TaskRowCounter++;			
		}
		for (int tc = 0; tc < TCsize; tc++)
		{
			if (CSet[CurCat].TasksCompleted[tc].GetTaskDateD() == CSet[CurCat].GetDateFilter() && CSet[CurCat].GetShowCompleted() == true)
				TaskComRowCounter++;
		}
	}
	else if (CSet[CurCat].GetPriorFilter() != 0)
	{
		for (int t = 0; t < Tsize; t++)
		{
			if (CSet[CurCat].TasksSet[t].GetTaskPrior() == CSet[CurCat].GetPriorFilter())
				TaskRowCounter++;
		}
		for (int tc = 0; tc < TCsize; tc++)
		{
			if (CSet[CurCat].TasksCompleted[tc].GetTaskPrior() == CSet[CurCat].GetPriorFilter() && CSet[CurCat].GetShowCompleted() == true)
				TaskComRowCounter++;
		}
	}	
	
	rows = max( CCount, (TaskRowCounter + TaskComRowCounter) );
	
	for (register int r = 0; r < rows; r++)
	{		
		// Drawing of rows for categories:
		if (r >= CCount)
			CatRowDrawerEmp();
		else
			r == CurCat ? CatRowDrawer(r, CSet[r], true) : CatRowDrawer(r, CSet[r]);	
	
		// Drawing of rows for base tasks:
		if ( r >= (TaskRowCounter + TaskComRowCounter) )
			TaskRowDrawerEmp();		
		else if (CSet[CurCat].GetDateFilter() == 0 && CSet[CurCat].GetPriorFilter() == 0 && r < TaskRowCounter)
		{
			r == CSet[CurCat].GetCurrentTask() ? TaskRowDrawer(r, CSet[CurCat].TasksSet[r], true) : TaskRowDrawer(r, CSet[CurCat].TasksSet[r]);
			TaskRowDrawedCount++;					
		}			
		else if (CSet[CurCat].GetDateFilter() != 0 && r < TaskRowCounter)
		{
			for (int t = TaskFilteredByDateDrawed; t < Tsize; t++)
			{
				if ( CSet[CurCat].TasksSet[t].GetTaskDateD() == CSet[CurCat].GetDateFilter() )
				{
					r == CSet[CurCat].GetCurrentTask() ? TaskRowDrawer(r, CSet[CurCat].TasksSet[t], true) : TaskRowDrawer(r, CSet[CurCat].TasksSet[t]);					
					TaskFilteredByDateDrawed = t + 1;
					TaskRowDrawedCount++;										
					break;
				}				
			}
		}
		else if (CSet[CurCat].GetPriorFilter() != 0 && r < TaskRowCounter)
		{
			for (int t = TaskFilteredByPriorDrawed; t < Tsize; t++)
			{
				if (CSet[CurCat].TasksSet[t].GetTaskPrior() == CSet[CurCat].GetPriorFilter())
				{
					r == CSet[CurCat].GetCurrentTask() ? TaskRowDrawer(r, CSet[CurCat].TasksSet[t], true) : TaskRowDrawer(r, CSet[CurCat].TasksSet[t]);					
					TaskFilteredByPriorDrawed = t + 1;
					TaskRowDrawedCount++;					
					break;
				}				
			}
		}

		// Drawing of rows for completed tasks::
		if ( TaskRowDrawedCount == TaskRowCounter && r > (TaskRowCounter-1) && CSet[CurCat].TasksCompleted.size() != 0 && CSet[CurCat].GetShowCompleted() == true )
		{
			if (CSet[CurCat].GetDateFilter() == 0 && CSet[CurCat].GetPriorFilter() == 0)			
				TaskRowDrawer(r, CSet[CurCat].TasksCompleted[r-TaskRowCounter], false, DarkGray);			
			else if (CSet[CurCat].GetDateFilter() != 0)
			{
				for (int t = TaskComFilteredByDateDrawed; t < TCsize; t++)
				{
					if (CSet[CurCat].TasksCompleted[t].GetTaskDateD() == CSet[CurCat].GetDateFilter())
					{
						TaskRowDrawer(r, CSet[CurCat].TasksCompleted[t], false, DarkGray);						
						TaskComFilteredByDateDrawed = t + 1;											
						break;
					}					
				}
			}
			else if (CSet[CurCat].GetPriorFilter() != 0)
			{
				for (int t = TaskComFilteredByPriorDrawed; t < TCsize; t++)
				{
					if (CSet[CurCat].TasksCompleted[t].GetTaskPrior() == CSet[CurCat].GetPriorFilter())
					{
						TaskRowDrawer(r, CSet[CurCat].TasksCompleted[t], false, DarkGray);						
						TaskComFilteredByPriorDrawed = t + 1;											
						break;
					}					
				}
			}
		}		
		cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;		
	}
	empty:
	cout << "=======================================================================================================================" << endl;
	for (int i = 0; i < max(CCount, (Tsize + TCsize))*2 + 1; i++)
		cout << "                                                                                                                       " << endl;	
	if (CSet.size() != 0)
		position_down.Y = position_tab.Y + rows*2 + 1;
}

void CatRowDrawer(int r, Category Cat, bool isCurCat)
{	
	cout << "|  ";
	if (isCurCat) SetColor(White, Black);
	else SetColor(LightGray, Black);
	cout << r + 1 << ") ";
	string CName = Cat.GetCatName();
	if (CName.size() < 17)
	{
		cout << CName;
		for (int i = 0; i <= (21 - CName.size()); i++)
			cout << ' ';
	}
	else
	{
		for (int i = 0; i < 19; i++)
			cout << CName[i];
		cout << "...";
	}
	SetColor(LightGray, Black);
	cout << "|";
}

void CatRowDrawerEmp()
{	
	cout << "|                           |";			 
}

void TaskRowDrawer(int r, Task task, bool isCurTask, ConsoleColor Color)
{	
	if (isCurTask) SetColor(White, Black);
	else SetColor(Color, Black);
	if (r < 9 && Color != DarkGray)
		cout << " " << r + 1 << "  ";
	else if (Color != DarkGray)
		cout << " " << r + 1 << " ";
	else
		cout << " v  ";
	SetColor(LightGray, Black);
	cout << "| ";
	if (isCurTask) SetColor(White, Black);
	else SetColor(Color, Black);	
	string TName = task.GetTaskName();
	if (TName.size() < 50)
	{		
		cout << TName;
		for (int i = 0; i <= (49 - TName.size()); i++)
			cout << ' ';
	}
	else
	{
		for (int i = 0; i < 46; i++)
			cout << TName[i];
		cout << "... ";
	}
	SetColor(LightGray, Black);
	cout << "|    ";
	if (isCurTask) SetColor(White, Black);
	else SetColor(Color, Black);
	if (task.GetTaskDate() == "-")
		cout << "          ";
	else
		cout << task.GetTaskDate();	
	SetColor(LightGray, Black);
	cout << "    |      ";
	if (isCurTask) SetColor(White, Black);
	else SetColor(Color, Black);
	if (task.GetTaskPrior() == 0)
		cout << " ";
	else
		cout << task.GetTaskPrior();
	SetColor(LightGray, Black);
	cout << "      |" << endl;
}

void TaskRowDrawerEmp()
{	
	cout << "    |                                                   |                  |             |" << endl;	
}
