#pragma once

/// @brief Interface for the priority queue classes
/// @tparam T 
template<typename T>
class PriorityQueue
{
public:
	/// @brief Insert element with it's priority
	/// @param data 
	/// @param priority 
	virtual void Insert(T data, int priority) = 0;

	/// @brief Pull element with the highest priority and delete it from the queue
	/// @exception std::underflow_error Thrown when there is no elemente
	/// @return Element's value
	virtual T Pop() = 0;

	/// @brief Pull element with the highest priority but don't delete it
	/// @exception std::underflow_error Thrown when there is no elemente
	/// @return Element's value
	virtual T Peek() const = 0;

private:
	virtual bool isEmpty() const = 0;
};
