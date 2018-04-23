#include "Category.h"
#include "UI_Builder.h"

COORD position_up;
COORD position_input;
COORD position_tab;
COORD position_down;
COORD position;

int CatCount = 0;
int CurrentCat;

int stoiDateConv(string SDate);

int main()
{
	try
	{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	string Input1;
	bool Q = true;	

	position_up.X = 0;
	position_up.Y = 13;

	position_tab.X = position_up.X;
	position_tab.Y = position_up.Y + 5;

	position_down.X = position_tab.X;
	position_down.Y = position_tab.Y + 1;
	
	vector <Category> CatSet;
	vector <Category>::iterator it_cat;

	vector <Task>::iterator it_tasks;

	UI::Header();
	glmenu:
	UI::MenuInput();

	while (Q)
	{
		string Input2;
		int Input2i;
		
		struct tm *date;
		time_t tt = time(NULL);
		date = localtime(&tt);
		int today_d = date->tm_mday;
		int today_m = date->tm_mon + 1;
		int today_y = date->tm_year + 1900;

		cin >> Input1;		
		SetConsoleCursorPosition(hConsole, position_input);
		if (Input1.size() > 1)
			UI::MenuInput("Введите корректную опцию из меню");
		else if (Input1 == "в" || Input1 == "В")
			Q = false;
		else
		{			
			switch (Input1[0])
			{
			case 'к':
			case 'К':
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "г" || Input2 == "Г")
					goto glmenu;
				else
				{
					CatCount++;
					CurrentCat = CatCount - 1;
					Category Temp(Input2, CatCount);
					CatSet.push_back(Temp);										
				}				
				break;
			case 'д':
			case 'Д':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}								
				else if ( Input2 == "г" || Input2 == "Г")
					goto glmenu;
				reinputC:
				UI::MenuInput2(Input1, Input2);
				if (Input2.size() > 2)
				{
					UI::MenuInput("Введите корректный номер категории");
					goto reinputC;
				}
				Input2i = stoi(Input2);
				if (Input2i >= 0 && Input2i <= CatCount)
					CurrentCat = Input2i - 1;
				else
				{
					UI::MenuInput("Введите корректный номер категории");
					goto reinputC;
				}													
				break;
			case 'и':
			case 'И':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				reinputN:
				UI::MenuInput2(Input1, Input2);
				if (Input2.size() > 2)
				{
					UI::MenuInput("Введите корректный номер целевой позиции");
					goto reinputN;
				}					
				else if (Input2 == "г" || Input2 == "Г")
					goto glmenu;
				Input2i = stoi(Input2);
				if (Input2i >= 0 && Input2i <= CatCount )
				{
					Category Temp = CatSet[CurrentCat];
					it_cat = CatSet.begin() + CurrentCat;
					CatSet.erase(it_cat);					
					if (Input2i == CatCount)
						CatSet.push_back(Temp);
					else
					{
						it_cat = CatSet.begin() + Input2i - 1;
						CatSet.insert(it_cat, Temp);
					}						
					CurrentCat = Input2i - 1;
					for (register int i = 0; i < CatCount; i++)
						CatSet[i].SetCatNum(i+1);					
				}
				else
				{
					UI::MenuInput("Введите корректный номер целевой позиции");
					goto reinputN;
				}					
				break;
			case 'н':
			case 'Н':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "г" || Input2 == "Г")
					goto glmenu;
				else
					CatSet[CurrentCat].SetCatName(Input2);					
				break;
			case 'у':
			case 'У':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				reinputU:
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "г" || Input2 == "Г" || Input2 == "н" || Input2 == "Н")
					goto glmenu;
				if (Input2 == "д" || Input2 == "Д")
				{					
					it_cat = CatSet.begin() + CurrentCat;
					CatSet.erase(it_cat);
					CatCount--;
					CurrentCat = 0;					
					for (register int i = 0; i < CatCount; i++)
						CatSet[i].SetCatNum(i + 1);															
				}
				else
				{
					UI::MenuInput("Введите корректный выбор");
					goto reinputU;
				}					
				break;
			case 'з':
			case 'З':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "г" || Input2 == "Г")
					goto glmenu;				
				else
				{
					CatSet[CurrentCat].AddTask(Input2);
					UI::Table(CatSet, CatCount, CurrentCat);				
					reinputS:
					UI::MenuInput2("4", Input2);
					if (Input2 == "г" || Input2 == "Г")
						goto glmenu;
					else if (Input2 == "-")
						UI::Table(CatSet, CatCount, CurrentCat);
					else if (Input2.size() != 10 || stoiDateConv(Input2) < 20161210 || stoiDateConv(Input2) > 20300000)
					{
						UI::MenuInput("Введите корректный срок");
						goto reinputS;
					}						
					else
					{
						CatSet[CurrentCat].TasksSet[CatSet[CurrentCat].GetCurrentTask()].SetTaskDate(Input2);
						UI::Table(CatSet, CatCount, CurrentCat);						
					}						
					reinputP:					
					UI::MenuInput2("5", Input2);					
					if (Input2 == "г" || Input2 == "Г")
						goto glmenu;
					else if (Input2 != "1" && Input2 != "2" && Input2 != "3")
					{
						UI::MenuInput("Введите корректный приоритет");
						goto reinputP;
					}				
					else
					{
						int Prior = stoi(Input2);
						CatSet[CurrentCat].TasksSet[CatSet[CurrentCat].GetCurrentTask()].SetTaskPrior(Prior);
						UI::Table(CatSet, CatCount, CurrentCat);						
					}					
				}
				break;
			case 'т':
			case 'Т':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("В категории нет активных задач");
					goto glmenu;
				}
				reinputT:
				UI::MenuInput2(Input1, Input2);
				if (stoi(Input2) - 1 < 0 || stoi(Input2) > CatSet[CurrentCat].GetTaskCounter())
				{
					UI::MenuInput("Введите корректный номер задачи");
					goto reinputT;
				}
				else if ( Input2 == "г" || Input2 == "Г")
					goto glmenu;				
				if (CatSet[CurrentCat].GetCurrentTask() >= 0 && CatSet[CurrentCat].GetCurrentTask() <= CatSet[CurrentCat].GetTaskCounter())
				{
					int CurTask = stoi(Input2) - 1;
					CatSet[CurrentCat].SetCurrentTask(CurTask);
				}					
				else
				{
					UI::MenuInput("Введите корректный номер задачи");
					goto reinputT;
				}					
				break;
			case 'р':
			case 'Р':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("В категории нет активных задач");
					goto glmenu;
				}
				reinputR:
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "г" || Input2 == "Г")
					goto glmenu;
				else if (Input2 != "1" && Input2 != "2" && Input2 != "3")
				{
					UI::MenuInput("Введите корректный выбор");
					goto reinputR;
				}					
				else
				{
					if (Input2 == "1")
					{
						UI::MenuInput2("1", Input2); // Не устранено: считывает строку только до пробела
						CatSet[CurrentCat].TasksSet[CatSet[CurrentCat].GetCurrentTask()].SetTaskName(Input2);						
					}
					else if (Input2 == "2")
					{
						UI::MenuInput2("2", Input2);
						CatSet[CurrentCat].TasksSet[CatSet[CurrentCat].GetCurrentTask()].SetTaskDate(Input2);						
					}
					else if (Input2 == "3")
					{
						UI::MenuInput2("3", Input2);
						int pr = stoi(Input2);
						CatSet[CurrentCat].TasksSet[CatSet[CurrentCat].GetCurrentTask()].SetTaskPrior(pr);						
					}					
				}
				break;
			case 'о':
			case 'О':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("В категории нет активных задач");
					goto glmenu;
				}
				reinputO:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "г" || Input2 == "Г" || Input2[0] == 'Н' || Input2[0] == 'н')
					goto glmenu;
				else if ((Input2) != "Д" && (Input2) != "д")
				{
					UI::MenuInput("Введите корректный выбор");
					goto reinputO;
				}					
				else
				{
					CatSet[CurrentCat].TasksSet[CatSet[CurrentCat].GetCurrentTask()].SetTaskComplete(true);
					Task Temp = CatSet[CurrentCat].TasksSet[CatSet[CurrentCat].GetCurrentTask()];
					CatSet[CurrentCat].TasksCompleted.push_back(Temp);
					CatSet[CurrentCat].ChangeTaskComCounter(1);
					it_tasks = CatSet[CurrentCat].TasksSet.begin() + CatSet[CurrentCat].GetCurrentTask();
					CatSet[CurrentCat].TasksSet.erase(it_tasks);
					CatSet[CurrentCat].ChangeTaskCounter(-1);
					CatSet[CurrentCat].SetCurrentTask(0);
				}
				break;
			case 'м':
			case 'М':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("В категории нет активных задач");
					goto glmenu;
				}
				reinputM:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "г" || Input2 == "Г")
					goto glmenu;
				else if (stoi(Input2) < 1 || stoi(Input2) > CatCount)
				{
					UI::MenuInput("Введите корректный выбор");
					goto reinputM;
				}					
				else
				{
					Task Temp = CatSet[CurrentCat].TasksSet[CatSet[CurrentCat].GetCurrentTask()];
					it_tasks = CatSet[CurrentCat].TasksSet.begin() + CatSet[CurrentCat].GetCurrentTask();
					CatSet[CurrentCat].TasksSet.erase(it_tasks);
					CatSet[CurrentCat].ChangeTaskCounter(-1);
					CatSet[CurrentCat].SetCurrentTask(1);
					//CurrentCat = stoi(Input2) - 1;
					CatSet[stoi(Input2) - 1].TasksSet.push_back(Temp);
					CatSet[stoi(Input2) - 1].ChangeTaskCounter(1);
					CatSet[CurrentCat].SetCurrentTask(0);					
				}
				break;
			case 'с':
			case 'С':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("В категории нет активных задач");
					goto glmenu;
				}
				reinputC2:
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "г" || Input2 == "Г" || Input2 == "н" || Input2 == "Н")
					goto glmenu;
				else if (Input2 != "д" && Input2 != "Д")
				{
					UI::MenuInput("Введите корректный выбор");
					goto reinputC2;
				}					
				else				
					CatSet[CurrentCat].SortByDate();				
				break;
			case 'п':
			case 'П':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("В категории нет активных задач");
					goto glmenu;
				}
				reinputP2:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "г" || Input2 == "Г" || Input2 == "н" || Input2 == "Н")
					goto glmenu;
				else if (Input2 != "д" && Input2 != "Д")
				{
					UI::MenuInput("Введите корректный выбор");
					goto reinputP2;
				}					
				else
					CatSet[CurrentCat].SortByPrior();					
				break;
			case 'х':
			case 'Х':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("В категории нет активных задач");
					goto glmenu;
				}
				reinputX:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "г" || Input2 == "Г" || Input2 == "н" || Input2 == "Н")
					goto glmenu;
				else if (Input2 != "д" && Input2 != "Д")
				{
					UI::MenuInput("Введите корректный выбор");
					goto reinputX;
				}					
				else
				{
					CatSet[CurrentCat].SortByDefault();
					CatSet[CurrentCat].SetDateFilter(0);
					CatSet[CurrentCat].SetPriorFilter(0);
				}					
				break;
			case 'ч':
			case 'Ч':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksCompleted.size() == 0)
				{
					UI::MenuInput("В категории нет выполненных задач");
					goto glmenu;
				}
				reinputC3:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "г" || Input2 == "Г")
					goto glmenu;
				else if (Input2 != "о" && Input2 != "О" && Input2 != "с" && Input2 != "С")
				{
					UI::MenuInput("Введите корректный выбор");
					goto reinputC3;
				}					
				else if (Input2 == "о" || Input2 == "О")				
					CatSet[CurrentCat].SetShowCompleted(true);
				else if (Input2 == "с" || Input2 == "С")
					CatSet[CurrentCat].SetShowCompleted(false);
				break;
			case 'ф':
			case 'Ф':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("Сначала создайте категорию");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("В категории нет активных задач");
					goto glmenu;
				}
				reinputF:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "г" || Input2 == "Г")
					goto glmenu;
				else if (Input2.size() == 1 && Input2 != "с" && Input2 != "С" && Input2 != "п" && Input2 != "П")
				{
					UI::MenuInput("Введите корректный выбор");
					goto reinputF;
				}					
				else if (Input2 == "с" || Input2 == "С" )
				{
					reinputD:
					UI::MenuInput2("6", Input2);
					if (Input2.size() == 1 && Input2 != "с" && Input2 != "С" && Input2 != "з" && Input2 != "З")
					{
						UI::MenuInput("Введите корректную дату");
						goto reinputD;
					}
					else if (Input2.size() > 1 && stoiDateConv(Input2) < 20161220 && stoiDateConv(Input2) > 20300000)
					{
						UI::MenuInput("Введите корректную дату");
						goto reinputD;
					}
					else
					{
						int today = today_y * 10000 + today_m * 100 + today_d;
						if (Input2 == "с" || Input2 == "С")
							CatSet[CurrentCat].SetDateFilter(today);
						else if (Input2 == "з" || Input2 == "З")
							CatSet[CurrentCat].SetDateFilter(today + 1);
						else
							CatSet[CurrentCat].SetDateFilter(stoiDateConv(Input2));
						CatSet[CurrentCat].SetCurrentTask(0);
						CatSet[CurrentCat].SetPriorFilter(0);
					}					
				}
				else if (Input2 == "п" || Input2 == "П")
				{
					reinputP3:
					UI::MenuInput2("7", Input2);
					if (Input2 != "1" && Input2 != "2" && Input2 != "3")
					{
						UI::MenuInput("Введите корректный приоритет");
						goto reinputP3;
					}						
					else
					{
						if (Input2 == "1")
							CatSet[CurrentCat].SetPriorFilter(1);
						else if (Input2 == "2")
							CatSet[CurrentCat].SetPriorFilter(2);
						else
							CatSet[CurrentCat].SetPriorFilter(3);
						CatSet[CurrentCat].SetCurrentTask(0);
						CatSet[CurrentCat].SetDateFilter(0);
					}					
				}
				break;
			default:
				UI::MenuInput("Введите корректное значение...");
				goto glmenu;
				break;
			}						
			UI::Table(CatSet, CatCount, CurrentCat);
			UI::MenuInput();
		}
	}	
	SetConsoleCursorPosition(hConsole, position_down);
	}
	
	catch (int i) // Перепроверить
	{
		switch (i)
		{
		case 1:
			UI::MenuInput("Введите опции в соответствии с меню");
			break;
		case 2:
			UI::MenuInput("Некорректный ввод номера позиции категории");
			break;
		case 3:
			UI::MenuInput("Некорректный ввод параметров");
			break;
		}
	}
	cout << endl;	
	return 0;
}

int stoiDateConv(string SDate)
{	
	int iDate;
	string temp;
	temp.assign(SDate, 6, 4);
	iDate = stoi(temp) * 10000;
	temp.assign(SDate, 3, 2);
	iDate = iDate + stoi(temp) * 100;
	temp.assign(SDate, 0, 2);
	iDate = iDate + stoi(temp);
	return iDate;
}

/* Оставшиеся замечания:
- При редактировании срока и вводе "-" ошибка
- Пропадание 1го символа при редактировании задачи при вводе названия
- Статусная строка
- Смещение на 1 символ под строкой Input2
- Блок try-catch
*/