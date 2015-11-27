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

std::function<void(Message*, const Point&)> Message::draw_fn = [] (Message* msg, const Point& pos) {
    msg->speaker().draw(pos - Point(0, msg->speaker().height()), GUI_LAYER);
    msg->increment();
    msg->message().draw_upto(msg->current_pos(), pos, GUI_LAYER);
};

void Message::draw(const Point& pos) {
    draw_fn(this, pos);
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
                    dia->_messages = new Message*[n];
                    dia->_message_count = n;
                } else {
                    Message* msg = new Message(line.substr(0, line.find(':')), line.substr(line.find(':') + 1));
                    n++;
                    next();
                    dia->_messages[--n] = msg;
                }
            })();
        }
    }
}

void Dialog::next() {
    if (_on_display != nullptr) {
        if (_on_display->current()->current_pos() < _on_display->current()->message().length()) {
            // Skip to end
            _on_display->current()->current_pos(_on_display->current()->message().length());
        } else if (_on_display->_current_message + 1 < _on_display->_message_count) {
            // Go to next message
            _on_display->_current_message++;
            _on_display->current()->current_pos(0);
        } else {
            // Quit
            _on_display = nullptr;
        }
    }
}

std::function<void(Dialog*)> Dialog::draw_fn = [] (Dialog* dialog) {
    Rect box = Rect(0, WINDOW_HEIGHT - 150, WINDOW_WIDTH, 150);
    draw::set_color(Color(0xEE, 0xEE, 0xEE, 0x33));
    draw::rect(box, GUI_LAYER - 1);
    dialog->current()->draw(Point(0, WINDOW_HEIGHT - 150));
};

void Dialog::draw() {
    if (_on_display != nullptr) {
        draw_fn(_on_display);
    }
}

Dialog::~Dialog() {
    for (unsigned int i = 0; i < _message_count; i++) { delete _messages[i]; }
    delete[] _messages;
}