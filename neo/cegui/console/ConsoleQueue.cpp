/*
 * ConsoleQueue.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: kordex
 */

#include <cegui/console/ConsoleQueue.h>

namespace CEGUIConsole
{

ConsoleQueue::ConsoleQueue()
{
	std::list<ConsoleMsg> messages;
}

ConsoleQueue::~ConsoleQueue()
{
	messages.clear();
}

} /* namespace CEGUIConsole */
