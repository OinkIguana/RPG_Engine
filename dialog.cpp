#include "dialog.h"

Message operator""_speaker(const char* speaker, size_t) {
    return Message(speaker);
}

Message operator""_message(const char* message, size_t) {
    return Message("", message);
}

Message operator""_lsprite(const char* sprite, size_t) {
    return Message("", "", Sprite::get(sprite));
}

Message operator""_rsprite(const char* sprite, size_t) {
    return Message("", "", nullptr, Sprite::get(sprite));
}

Message Message::operator+(const Message& o) const {
    FormatString new_speaker = _speaker, new_message = _message;
    Sprite* new_lsprite = _sprites[LEFT];
    Sprite* new_rsprite = _sprites[RIGHT];

    if (_speaker == "") {
        new_speaker = o._speaker;
    }
    if (_message == "") {
        new_message = o._message;
    }
    if (_sprites[LEFT] == nullptr) {
        new_lsprite = o._sprites[LEFT];
    }
    if (_sprites[RIGHT] == nullptr) {
        new_rsprite = o._sprites[RIGHT];
    }

    return Message(new_speaker, new_message, new_lsprite, new_rsprite);
}
