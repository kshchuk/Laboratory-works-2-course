#pragma once

/// <summary>
/// Interface for the priority queue 
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
	/// <exception cref="std::underflow_error"> Thrown when there is no elementes </exception>
	/// <returns></returns>
	virtual T Pop() = 0;
	/// <summary>
	/// Pull element with the highest priority but don't delete it
	/// </summary>
	/// <exception cref="std::underflow_error"> Thrown when there is no elementes </exception>
	/// <returns></returns>
	virtual T Peek() const = 0;

private:
	virtual bool isEmpty() const = 0;
};
