#pragma once

#include <functional>
#include <fstream>
#include <string>
#include <map>
#include "config.h"
#include "formatstring.h"

#include <iostream>

// One message in a dialog
class Message {
public:
    Message(const std::string& message) : _speaker(""_format), _message(FormatString(message)) {}
    Message(const std::string& speaker, const std::string& message) : _speaker(FormatString(speaker)), _message(FormatString(message)) {}
    Message(const FormatString& speaker = ""_format, const FormatString& message = ""_format) : _speaker(speaker), _message(message) {}

    Message operator+(const Message&) const;
    // Produce a plain string containing "Speaker: Message"
    std::string to_string() const { return _speaker.to_string() + ": " + _message.to_string(); }
    FormatString next() {};

    void draw(const Point& pos);

    inline FormatString& speaker() { return _speaker; }
    inline FormatString& message() { return _message; }
    inline unsigned int current_pos() const { return _current_pos; }
    inline void current_pos(const unsigned int& x) { _current_pos = x; }
    inline void increment(const int& x = 1) { _current_pos = (unsigned int)std::fmin(_current_pos + x, _message.length()); }

    static std::function<void(Message*, const Point&)> draw_fn;
private:
	FormatString _speaker;
	FormatString _message;
    unsigned int _current_pos = 0;
};

// An entier Dialog, holding a list of Messages
class Dialog {
public:
    // Get a dialog by its name
    static Dialog* get(const std::string& name);
    // Set the dialog that is currently on display
    static void set(Dialog* which);
    // Import dialog from a file
    static void import(const std::string& path);

    // Determines whether there is a dialog on display
    inline static bool visible() { return _on_display != nullptr; }

    // Progress to the next message in the current Dialog
    static void next();
    // Get the current message
    inline Message& current() { return _messages[_current_message]; }
    // Get the message count
    inline unsigned int length() const { return _message_count; }

    // Run through this dialog
    inline void start() { _current_message = 0; _messages[_current_message].current_pos(0); _on_display = this; }

    static void draw();
    static std::function<void(Dialog*)> draw_fn;

    ~Dialog() { delete _messages; }
private:
    // Dialog must be imported
    Dialog(const std::string& name) : _name(name) {}
	Message* _messages;
	unsigned int _current_message;
    unsigned int _message_count;
    const std::string _name;

    static Dialog* _on_display;
    static std::map<std::string, Dialog*> all_dialogs;
};


Message operator""_speaker(const char*, size_t);
Message operator""_message(const char*, size_t);