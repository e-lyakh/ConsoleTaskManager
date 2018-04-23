#include "Task.h"

void Task::SetTaskNum(int TNum)
{
	TaskNum = TNum;
}

void Task::SetTaskName(string TName)
{
	TaskName = TName;
}

void Task::SetTaskDate(string TDate)
{
	TaskDate = TDate;
	string temp;
	temp.assign(TDate, 6, 4);
	TaskDateD = stoi(temp) * 10000;
	temp.assign(TDate, 3, 2);
	TaskDateD = TaskDateD + stoi(temp) * 100;
	temp.assign(TDate, 0, 2);
	TaskDateD = TaskDateD + stoi(temp);
}

void Task::SetTaskPrior(int TPrior)
{
	TaskPrior = TPrior;
}

void Task::SetTaskCategory(string TCategory)
{
	TaskCategory = TCategory;
}

void Task::SetTaskComplete(bool TComplete)
{
	TaskComplete = TComplete;
}

int Task::GetTaskNum() const
{
	return TaskNum;
}

string Task::GetTaskName() const
{
	return TaskName;
}

string Task::GetTaskDate() const
{
	return TaskDate;
}

int Task::GetTaskPrior() const
{
	return TaskPrior;
}

string Task::GetTaskCatrgory() const
{
	return TaskCategory;
}

int Task::GetTaskDateD() const
{
	return TaskDateD;
}