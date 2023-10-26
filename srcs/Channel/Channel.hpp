#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <main.hpp>
# include "../Client/Client.hpp"
# include "../Utils/Message/Message.hpp"
# include <bitset>
#include "../Server/Instance/ServerInstance.hpp"

typedef std::bitset<5> t_mode;

class Server;

class Client;

class Channel {
private:
    std::string _name;
    std::vector<int> _clients;
    std::vector<int> _invited;
    std::vector<int> _operators;
    std::vector<Message *> _messages;
    t_mode _mode;
    Server *_server;

public:
    Channel();

    ~Channel();

    Channel(const Channel &copy);

    enum Mode {
        BASE_MASK = 0b11111,
        I_INVITE = 0b10000,
        T_TOPIC = 0b01000,
        K_PASSWORD = 0b00100,
        O_OPERATOR = 0b00010,
        L_LIMIT = 0b00001
    };

    Channel &operator=(const Channel &copy);

    std::string getName();

    void setName(std::string name);

    void addClient(int fd);

    std::vector<int> getClients();

    bool hasClient(int fd);

    bool hasClient(Client client);

    void showClients();

    bool removeClient(int fd);

    void broadcastPrivMsg(Client *sender, const std::string &message);

    void broadcastMessage(Client *sender, const std::string &message);

    bool hasMode(t_mode mode);

    void addMode(t_mode mode);

    void delMode(t_mode mode);

    static Channel *create(std::string name);

    bool hasOperator(Client client);

    void invite(Client client);

    bool hasInvited(Client client);

    std::string getNicknames();

    void broadcastChanMsg(Client *sender, const std::string &message);
};

std::iostream &operator<<(std::iostream &stream, Channel &client);

#endif