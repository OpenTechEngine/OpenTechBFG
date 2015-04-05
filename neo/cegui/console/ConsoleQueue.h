/*
 * ConsoleQueue.h
 *
 *  Created on: Dec 18, 2014
 *      Author: kordex
 */

#ifndef CONSOLEQUEUE_H_
#define CONSOLEQUEUE_H_

#include <list>

#include "ConsoleMsg.h"

namespace CEGUIConsole
{

class ConsoleQueue
{
public:
	ConsoleQueue();
	virtual ~ConsoleQueue();
	
	ConsoleQueue& operator=( const ConsoleQueue& rhs )
	{
		return *this;
	}
	
	void push( ConsoleMsg in )
	{
		messages.push_back( in );
	};
	ConsoleMsg pop()
	{
		ConsoleMsg out = messages.front();
		messages.pop_front();
		return out;
	};
	
	bool empty()
	{
		return messages.empty();
	};
	
private:
	std::list<ConsoleMsg> messages;
};

} /* namespace CEGUIConsole */

#endif /* CONSOLEQUEUE_H_ */
