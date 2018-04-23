#pragma once

#include "Header.h"

class Task
{
	string TaskName;
	string TaskDate = "-";
	int TaskDateD;
	int TaskPrior = 0;
	string TaskCategory;
	int TaskNum;
	bool TaskComplete = false;
public:	
	void SetTaskNum(int TNum);
	void SetTaskName(string TName);
	void SetTaskDate(string TDate);
	void SetTaskPrior(int TPrior);
	void SetTaskCategory(string TCategory);
	void SetTaskComplete(bool TComplete);
	int GetTaskNum() const;
	string GetTaskName() const;
	string GetTaskDate() const;
	int GetTaskPrior() const;
	string GetTaskCatrgory() const;
	int GetTaskDateD() const;
};