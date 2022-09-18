#pragma once

/// <summary>
/// Abstract class of the priority queue 
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class PriorityQueue
{
public:
	/// <summary>
	/// Insert element with priority
	/// </summary>
	/// <param name="data"></param>
	/// <param name="priority"></param>
	virtual void Insert(T data, int priority) = 0;
	/// <summary>
	/// Pull element with the highest priority and delete it from the queue
	/// </summary>
	/// <returns></returns>
	virtual T Pop() = 0;
	/// <summary>
	/// Pull element with the highest priority but don't delete it
	/// </summary>
	/// <returns></returns>
	virtual T Peek() = 0;

	virtual ~PriorityQueue() = 0;

private:
	virtual bool isEmpty() = 0;
};
