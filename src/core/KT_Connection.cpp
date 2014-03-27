#include "KT_Connection.hpp"

KIARA::Transport::KT_Connection::KT_Connection ( ) {
    _sessions = new std::map<std::string, KIARA::Transport::KT_Session*>;
}

KIARA::Transport::KT_Connection::~KT_Connection ( ) { }
