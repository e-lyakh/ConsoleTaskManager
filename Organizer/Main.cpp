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
			UI::MenuInput("������� ���������� ����� �� ����");
		else if (Input1 == "�" || Input1 == "�")
			Q = false;
		else
		{			
			switch (Input1[0])
			{
			case '�':
			case '�':
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "�" || Input2 == "�")
					goto glmenu;
				else
				{
					CatCount++;
					CurrentCat = CatCount - 1;
					Category Temp(Input2, CatCount);
					CatSet.push_back(Temp);										
				}				
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}								
				else if ( Input2 == "�" || Input2 == "�")
					goto glmenu;
				reinputC:
				UI::MenuInput2(Input1, Input2);
				if (Input2.size() > 2)
				{
					UI::MenuInput("������� ���������� ����� ���������");
					goto reinputC;
				}
				Input2i = stoi(Input2);
				if (Input2i >= 0 && Input2i <= CatCount)
					CurrentCat = Input2i - 1;
				else
				{
					UI::MenuInput("������� ���������� ����� ���������");
					goto reinputC;
				}													
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				reinputN:
				UI::MenuInput2(Input1, Input2);
				if (Input2.size() > 2)
				{
					UI::MenuInput("������� ���������� ����� ������� �������");
					goto reinputN;
				}					
				else if (Input2 == "�" || Input2 == "�")
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
					UI::MenuInput("������� ���������� ����� ������� �������");
					goto reinputN;
				}					
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "�" || Input2 == "�")
					goto glmenu;
				else
					CatSet[CurrentCat].SetCatName(Input2);					
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				reinputU:
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "�" || Input2 == "�" || Input2 == "�" || Input2 == "�")
					goto glmenu;
				if (Input2 == "�" || Input2 == "�")
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
					UI::MenuInput("������� ���������� �����");
					goto reinputU;
				}					
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "�" || Input2 == "�")
					goto glmenu;				
				else
				{
					CatSet[CurrentCat].AddTask(Input2);
					UI::Table(CatSet, CatCount, CurrentCat);				
					reinputS:
					UI::MenuInput2("4", Input2);
					if (Input2 == "�" || Input2 == "�")
						goto glmenu;
					else if (Input2 == "-")
						UI::Table(CatSet, CatCount, CurrentCat);
					else if (Input2.size() != 10 || stoiDateConv(Input2) < 20161210 || stoiDateConv(Input2) > 20300000)
					{
						UI::MenuInput("������� ���������� ����");
						goto reinputS;
					}						
					else
					{
						CatSet[CurrentCat].TasksSet[CatSet[CurrentCat].GetCurrentTask()].SetTaskDate(Input2);
						UI::Table(CatSet, CatCount, CurrentCat);						
					}						
					reinputP:					
					UI::MenuInput2("5", Input2);					
					if (Input2 == "�" || Input2 == "�")
						goto glmenu;
					else if (Input2 != "1" && Input2 != "2" && Input2 != "3")
					{
						UI::MenuInput("������� ���������� ���������");
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
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("� ��������� ��� �������� �����");
					goto glmenu;
				}
				reinputT:
				UI::MenuInput2(Input1, Input2);
				if (stoi(Input2) - 1 < 0 || stoi(Input2) > CatSet[CurrentCat].GetTaskCounter())
				{
					UI::MenuInput("������� ���������� ����� ������");
					goto reinputT;
				}
				else if ( Input2 == "�" || Input2 == "�")
					goto glmenu;				
				if (CatSet[CurrentCat].GetCurrentTask() >= 0 && CatSet[CurrentCat].GetCurrentTask() <= CatSet[CurrentCat].GetTaskCounter())
				{
					int CurTask = stoi(Input2) - 1;
					CatSet[CurrentCat].SetCurrentTask(CurTask);
				}					
				else
				{
					UI::MenuInput("������� ���������� ����� ������");
					goto reinputT;
				}					
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("� ��������� ��� �������� �����");
					goto glmenu;
				}
				reinputR:
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "�" || Input2 == "�")
					goto glmenu;
				else if (Input2 != "1" && Input2 != "2" && Input2 != "3")
				{
					UI::MenuInput("������� ���������� �����");
					goto reinputR;
				}					
				else
				{
					if (Input2 == "1")
					{
						UI::MenuInput2("1", Input2); // �� ���������: ��������� ������ ������ �� �������
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
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("� ��������� ��� �������� �����");
					goto glmenu;
				}
				reinputO:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "�" || Input2 == "�" || Input2[0] == '�' || Input2[0] == '�')
					goto glmenu;
				else if ((Input2) != "�" && (Input2) != "�")
				{
					UI::MenuInput("������� ���������� �����");
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
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("� ��������� ��� �������� �����");
					goto glmenu;
				}
				reinputM:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "�" || Input2 == "�")
					goto glmenu;
				else if (stoi(Input2) < 1 || stoi(Input2) > CatCount)
				{
					UI::MenuInput("������� ���������� �����");
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
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("� ��������� ��� �������� �����");
					goto glmenu;
				}
				reinputC2:
				UI::MenuInput2(Input1, Input2);
				if ( Input2 == "�" || Input2 == "�" || Input2 == "�" || Input2 == "�")
					goto glmenu;
				else if (Input2 != "�" && Input2 != "�")
				{
					UI::MenuInput("������� ���������� �����");
					goto reinputC2;
				}					
				else				
					CatSet[CurrentCat].SortByDate();				
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("� ��������� ��� �������� �����");
					goto glmenu;
				}
				reinputP2:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "�" || Input2 == "�" || Input2 == "�" || Input2 == "�")
					goto glmenu;
				else if (Input2 != "�" && Input2 != "�")
				{
					UI::MenuInput("������� ���������� �����");
					goto reinputP2;
				}					
				else
					CatSet[CurrentCat].SortByPrior();					
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("� ��������� ��� �������� �����");
					goto glmenu;
				}
				reinputX:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "�" || Input2 == "�" || Input2 == "�" || Input2 == "�")
					goto glmenu;
				else if (Input2 != "�" && Input2 != "�")
				{
					UI::MenuInput("������� ���������� �����");
					goto reinputX;
				}					
				else
				{
					CatSet[CurrentCat].SortByDefault();
					CatSet[CurrentCat].SetDateFilter(0);
					CatSet[CurrentCat].SetPriorFilter(0);
				}					
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksCompleted.size() == 0)
				{
					UI::MenuInput("� ��������� ��� ����������� �����");
					goto glmenu;
				}
				reinputC3:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "�" || Input2 == "�")
					goto glmenu;
				else if (Input2 != "�" && Input2 != "�" && Input2 != "�" && Input2 != "�")
				{
					UI::MenuInput("������� ���������� �����");
					goto reinputC3;
				}					
				else if (Input2 == "�" || Input2 == "�")				
					CatSet[CurrentCat].SetShowCompleted(true);
				else if (Input2 == "�" || Input2 == "�")
					CatSet[CurrentCat].SetShowCompleted(false);
				break;
			case '�':
			case '�':
				if (CatSet.size() == 0)
				{
					UI::MenuInput("������� �������� ���������");
					goto glmenu;
				}
				if (CatSet[CurrentCat].TasksSet.size() == 0)
				{
					UI::MenuInput("� ��������� ��� �������� �����");
					goto glmenu;
				}
				reinputF:
				UI::MenuInput2(Input1, Input2);
				if (Input2 == "�" || Input2 == "�")
					goto glmenu;
				else if (Input2.size() == 1 && Input2 != "�" && Input2 != "�" && Input2 != "�" && Input2 != "�")
				{
					UI::MenuInput("������� ���������� �����");
					goto reinputF;
				}					
				else if (Input2 == "�" || Input2 == "�" )
				{
					reinputD:
					UI::MenuInput2("6", Input2);
					if (Input2.size() == 1 && Input2 != "�" && Input2 != "�" && Input2 != "�" && Input2 != "�")
					{
						UI::MenuInput("������� ���������� ����");
						goto reinputD;
					}
					else if (Input2.size() > 1 && stoiDateConv(Input2) < 20161220 && stoiDateConv(Input2) > 20300000)
					{
						UI::MenuInput("������� ���������� ����");
						goto reinputD;
					}
					else
					{
						int today = today_y * 10000 + today_m * 100 + today_d;
						if (Input2 == "�" || Input2 == "�")
							CatSet[CurrentCat].SetDateFilter(today);
						else if (Input2 == "�" || Input2 == "�")
							CatSet[CurrentCat].SetDateFilter(today + 1);
						else
							CatSet[CurrentCat].SetDateFilter(stoiDateConv(Input2));
						CatSet[CurrentCat].SetCurrentTask(0);
						CatSet[CurrentCat].SetPriorFilter(0);
					}					
				}
				else if (Input2 == "�" || Input2 == "�")
				{
					reinputP3:
					UI::MenuInput2("7", Input2);
					if (Input2 != "1" && Input2 != "2" && Input2 != "3")
					{
						UI::MenuInput("������� ���������� ���������");
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
				UI::MenuInput("������� ���������� ��������...");
				goto glmenu;
				break;
			}						
			UI::Table(CatSet, CatCount, CurrentCat);
			UI::MenuInput();
		}
	}	
	SetConsoleCursorPosition(hConsole, position_down);
	}
	
	catch (int i) // �������������
	{
		switch (i)
		{
		case 1:
			UI::MenuInput("������� ����� � ������������ � ����");
			break;
		case 2:
			UI::MenuInput("������������ ���� ������ ������� ���������");
			break;
		case 3:
			UI::MenuInput("������������ ���� ����������");
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

/* ���������� ���������:
- ��� �������������� ����� � ����� "-" ������
- ���������� 1�� ������� ��� �������������� ������ ��� ����� ��������
- ��������� ������
- �������� �� 1 ������ ��� ������� Input2
- ���� try-catch
*/