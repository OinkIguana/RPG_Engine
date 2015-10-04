#ifndef __RPG_DIALOG_H__
#define __RPG_DIALOG_H__

#include "types.h"
#include "sprite.h"
#include <string>

class Dialog {
public:
	Dialog() {}
	~Dialog() {}
private:
	Message* messages;
	int currentMessage;
};

class Message {
public:
	Message() {}
	~Message() {}
private:
	std::string speaker;
	std::string message;
	Sprite* sprites[2];
};

#endif