#include "dialog.h"

Message operator""_speaker(const char* speaker, size_t) {
    return Message(speaker);
}

Message operator""_message(const char* message, size_t) {
    return Message("", message);
}

Message Message::operator+(const Message& o) const {
    return Message(_speaker + o._speaker, _message + o._message);
}

void Message::draw(const Point& pos) {
    _speaker.draw(pos - Point(0, _speaker.height()));
    increment();
    _message.upto(_current_pos).draw(pos);
}

Dialog* Dialog::_on_display = nullptr;
std::map<std::string, Dialog*> Dialog::all_dialogs = std::map<std::string, Dialog*>();

Dialog* Dialog::get(const std::string& name) {
    auto old = all_dialogs.find(name);
    if (old != all_dialogs.end()) {
        return old->second;
    }
    return nullptr;
}

void Dialog::set(Dialog* which) {
    which->start();
}

void Dialog::import(const std::string& path) {
    std::ifstream file(path);
    std::string name;
    getline(file, name);
    while (!file.eof()) {
        int n = 0;
        Message* msg_list;
        name = name.substr(1, name.length() - 2);
        Dialog* dia = new Dialog(name);
        all_dialogs[name] = dia;
        {
            std::function<void(void)> next;
            (next = [&]() {
                std::string line = "[";
                if (!file.eof()) {
                    getline(file, line);
                }
                if (line[0] == '[') {
                    name = line;
                    msg_list = new Message[n];
                    dia->_message_count = n;
                } else {
                    Message msg = Message(line.substr(0, line.find(':')), line.substr(line.find(':') + 1));
                    n++;
                    next();
                    msg_list[--n] = msg;
                }
            })();
        }
        dia->_messages = msg_list;
    }
}

void Dialog::next() {
    if (_on_display != nullptr) {
        if (_on_display->current().current_pos() < _on_display->current().message().length()) {
            _on_display->current().current_pos(_on_display->current().message().length());
        } else {
            if (_on_display->_current_message + 1 < _on_display->_message_count) {
                _on_display->_current_message++;
                _on_display->current().current_pos(0);
            } else {
                _on_display = nullptr;
            }
        }
    }
}

void Dialog::_draw() {
    Rect box = Rect(0, WINDOW_HEIGHT - current().message().height() - current().speaker().height(), WINDOW_WIDTH, current().message().height() + current().speaker().height());
    draw::set_color(Color(0, 0, 0, 0x33));
    //draw::rect(box);
    current().draw(Point(0, WINDOW_HEIGHT - current().message().height()));
}

void Dialog::draw() {
    if (_on_display != nullptr) {
        _on_display->_draw();
    }
}