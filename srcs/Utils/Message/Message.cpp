#include "Message.hpp"

Message::Message() {
    this->setSender(-1);
    this->setContent("");
}

Message::Message(int sender, std::string content) {
    this->setSender(sender);
    this->setContent(content);
}

Message::Message(const Message &copy) {
    *this = copy;
}

Message::~Message() {}

Message &Message::operator=(const Message &copy) {
    if (this != &copy) {
        this->_sender = copy._sender;
        this->_content = copy._content;
    }
    return *this;
}

int         Message::getSender() const {
    return this->_sender;
}

std::string Message::getContent() const {
    return this->_content;
}

void        Message::setSender(int sender) {
    this->_sender = sender;
}

void        Message::setContent(std::string content) {
    this->_content = content;
}