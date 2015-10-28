#ifndef __RPG_DIALOG_H__
#define __RPG_DIALOG_H__

#include <string>
#include "types.h"
#include "sprite.h"

class Message {
public:
	Message(std::string speaker = "", std::string message = "", Sprite* lsprite = nullptr, Sprite* rsprite = nullptr) :
        _speaker(FormatString(speaker)), _message(FormatString(message)), _sprites{ lsprite, rsprite } {}
    Message(FormatString speaker = ""_format, FormatString message = ""_format, Sprite* lsprite = nullptr, Sprite* rsprite = nullptr) :
        _speaker(speaker), _message(message), _sprites{ lsprite, rsprite } {}
	~Message() {}

    Message operator+(const Message&) const;
    std::string to_string() const { return _speaker.to_string() + ": " + _message.to_string(); }
    FormatString next();
private:
	const FormatString _speaker;
	const FormatString _message;
	Sprite* _sprites[2];
    unsigned int _current_pos;
};

class Dialog {
public:
	Dialog(int messageCount = 0) : _messageCount(messageCount) {}
	~Dialog() {}
    static Dialog import(std::string) { return Dialog(); }

    Message next() { return _messages[++_currentMessage]; }
private:
	Message* _messages;
	unsigned int _currentMessage;
    unsigned const int _messageCount;
};


Message operator""_speaker(const char*, size_t);
Message operator""_message(const char*, size_t);
Message operator""_lsprite(const char*, size_t);
Message operator""_rsprite(const char*, size_t);

#endif