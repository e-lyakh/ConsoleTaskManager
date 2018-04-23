#pragma once

#include "Header.h"
#include "Task.h"

class Category : public Task
{
	string CatName;
	int CatNum;
	int CurrentTask;
	bool ShowCompleted = false;
	bool SortedByDate = false;
	bool SortedByPrior = false;
	int DateFilter = 0;
	int PriorFilter = 0;
	int TaskCounter = 0;
	int TaskComCounter = 0;
public:
	vector <Task> TasksSet;
	vector <Task> TasksCompleted;	
	Category();
	Category(string CName, int CNum);	
	void SetCatName(string CName);
	void SetCatNum(int CNum);	
	void SetCurrentTask(int CTask);
	void SetShowCompleted(bool SC);
	void SetDateFilter(int DF);
	void SetPriorFilter(int PF);
	void SetTaskCounter(int TCounter);	
	void SetTaskComCounter(int TCCounter);
	void ChangeTaskCounter(int i);
	void ChangeTaskComCounter(int i);
	string GetCatName() const;
	int GetCatNum() const;
	int GetCurrentTask() const;
	int GetDateFilter() const;
	int GetPriorFilter() const;
	int GetTaskCounter() const;
	int GetTaskComCounter() const;
	bool GetShowCompleted() const;
	bool GetSortedByDate() const;
	bool GetSortedByPrior() const;
	void AddTask(string TName);
	void SortByDate();
	void SortByPrior();
	void SortByDefault();
};