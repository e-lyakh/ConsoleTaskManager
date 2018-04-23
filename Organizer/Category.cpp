#include "Category.h"


Category::Category()
{
	CatName = "0";
	CatNum = 0;
}

Category::Category(string CName = "0", int CNum = 0)
{
	CatName = CName;
	CatNum = CNum;
}

void Category::SetCatName(string CName)
{
	CatName = CName;
}

void Category::SetCatNum(int CNum)
{
	CatNum = CNum;
}

void Category::SetCurrentTask(int CTask)
{
	CurrentTask = CTask;
}

void Category::SetShowCompleted(bool SC)
{
	ShowCompleted = SC;
}

void Category::SetDateFilter(int DF)
{	
	DateFilter = DF;
}

void Category::SetPriorFilter(int PF)
{
	PriorFilter = PF;
}

void Category::SetTaskCounter(int TCounter)
{
	TaskCounter = TCounter;
}

void Category::SetTaskComCounter(int TCCounter)
{
	TaskComCounter = TCCounter;
}

void Category::ChangeTaskCounter(int i)
{
	TaskCounter += i;
}

void Category::ChangeTaskComCounter(int i)
{
	TaskComCounter += i;
}

string Category::GetCatName() const
{
	return CatName;
}

int Category::GetCatNum() const
{
	return CatNum;
}

int Category::GetCurrentTask() const
{
	return CurrentTask;
}

int Category::GetDateFilter() const
{
	return DateFilter;
}

int Category::GetPriorFilter() const
{
	return PriorFilter;
}

int Category::GetTaskCounter() const
{
	return TaskCounter;
}

int Category::GetTaskComCounter() const
{
	return TaskComCounter;
}

bool Category::GetShowCompleted() const
{
	return ShowCompleted;
}

bool Category::GetSortedByDate() const
{
	return SortedByDate;
}

bool Category::GetSortedByPrior() const
{
	return SortedByPrior;
}

void Category::AddTask(string TName)
{	
	Task Temp;
	Temp.SetTaskNum(TaskCounter);
	Temp.SetTaskCategory(GetCatName());
	Temp.SetTaskName(TName);
	TasksSet.push_back(Temp);
	TaskCounter = TasksSet.size();
	//TaskCounter++;
	CurrentTask = TaskCounter - 1;
}

void Category::SortByDate()
{
	register int i, j, k;
	Task temp;
	for (i = 0; i<TaskCounter; i++)
	{
		k = i;
		temp = TasksSet[i];
		for (j = i + 1; j<TaskCounter; j++)
			if (TasksSet[j].GetTaskDateD() < temp.GetTaskDateD())
			{
				k = j;
				temp = TasksSet[j];
			}
		TasksSet[k] = TasksSet[i];
		TasksSet[i] = temp;
	}
	SortedByDate = true;
}

void Category::SortByPrior()
{
	register int i, j, k;
	Task temp;
	for (i = 0; i<TaskCounter; i++)
	{
		k = i;
		temp = TasksSet[i];
		for (j = i + 1; j<TaskCounter; j++)
			if (TasksSet[j].GetTaskPrior() < temp.GetTaskPrior())
			{
				k = j;
				temp = TasksSet[j];
			}
		TasksSet[k] = TasksSet[i];
		TasksSet[i] = temp;
	}
	SortedByPrior = true;
}

void Category::SortByDefault()
{
	register int i, j, k;
	Task temp;
	for (i = 0; i<TaskCounter; i++)
	{
		k = i;
		temp = TasksSet[i];
		for (j = i + 1; j<TaskCounter; j++)
			if (TasksSet[j].GetTaskNum() < temp.GetTaskNum())
			{
				k = j;
				temp = TasksSet[j];
			}
		TasksSet[k] = TasksSet[i];
		TasksSet[i] = temp;
	}
	SortedByDate = false;
	SortedByPrior = false;
}