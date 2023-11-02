#include <main.hpp>
#include <Server/Server.hpp>

void    test_mode()
{
    Channel channel;
	std::cout << "Default channel:" << std::endl;
	std::cout << "Invite: " << (channel.hasMode(Channel::I_INVITE) ? "on" : "off") << std::endl;
	std::cout << "Topic: " << (channel.hasMode(Channel::T_TOPIC) ? "on" : "off") << std::endl;
	std::cout << "Password: " << (channel.hasMode(Channel::K_PASSWORD) ? "on" : "off") << std::endl;
	std::cout << "Operator: " << (channel.hasMode(Channel::O_OPERATOR) ? "on" : "off") << std::endl;
	std::cout << "Limit: " << (channel.hasMode(Channel::L_LIMIT) ? "on" : "off") << std::endl;
	std::cout << std::endl;

	std::cout << "Add mode password:" << std::endl;
	channel.addMode(Channel::K_PASSWORD);
	std::cout << "Invite: " << (channel.hasMode(Channel::I_INVITE) ? "on" : "off") << std::endl;
	std::cout << "Topic: " << (channel.hasMode(Channel::T_TOPIC) ? "on" : "off") << std::endl;
	std::cout << "Password: " << (channel.hasMode(Channel::K_PASSWORD) ? "on" : "off") << std::endl;
	std::cout << "Operator: " << (channel.hasMode(Channel::O_OPERATOR) ? "on" : "off") << std::endl;
	std::cout << "Limit: " << (channel.hasMode(Channel::L_LIMIT) ? "on" : "off") << std::endl;
	std::cout << std::endl;

	std::cout << "Remove mode invite:" << std::endl;
	channel.delMode(Channel::I_INVITE);
	std::cout << "Invite: " << (channel.hasMode(Channel::I_INVITE) ? "on" : "off") << std::endl;
	std::cout << "Topic: " << (channel.hasMode(Channel::T_TOPIC) ? "on" : "off") << std::endl;
	std::cout << "Password: " << (channel.hasMode(Channel::K_PASSWORD) ? "on" : "off") << std::endl;
	std::cout << "Operator: " << (channel.hasMode(Channel::O_OPERATOR) ? "on" : "off") << std::endl;
	std::cout << "Limit: " << (channel.hasMode(Channel::L_LIMIT) ? "on" : "off") << std::endl;
	std::cout << std::endl;

    std::cout << "Remove mode password:" << std::endl;
	channel.delMode(Channel::K_PASSWORD);
	std::cout << "Invite: " << (channel.hasMode(Channel::I_INVITE) ? "on" : "off") << std::endl;
	std::cout << "Topic: " << (channel.hasMode(Channel::T_TOPIC) ? "on" : "off") << std::endl;
	std::cout << "Password: " << (channel.hasMode(Channel::K_PASSWORD) ? "on" : "off") << std::endl;
	std::cout << "Operator: " << (channel.hasMode(Channel::O_OPERATOR) ? "on" : "off") << std::endl;
	std::cout << "Limit: " << (channel.hasMode(Channel::L_LIMIT) ? "on" : "off") << std::endl;
	std::cout << std::endl;

    std::cout << "Add mode invite and password at once:" << std::endl;
	channel.addMode(Channel::I_INVITE | Channel::K_PASSWORD);
	std::cout << "Invite: " << (channel.hasMode(Channel::I_INVITE) ? "on" : "off") << std::endl;
	std::cout << "Topic: " << (channel.hasMode(Channel::T_TOPIC) ? "on" : "off") << std::endl;
	std::cout << "Password: " << (channel.hasMode(Channel::K_PASSWORD) ? "on" : "off") << std::endl;
	std::cout << "Operator: " << (channel.hasMode(Channel::O_OPERATOR) ? "on" : "off") << std::endl;
	std::cout << "Limit: " << (channel.hasMode(Channel::L_LIMIT) ? "on" : "off") << std::endl;
	std::cout << std::endl;

    std::cout << "Add mode topic, operator and invite at once:" << std::endl;
	channel.addMode(Channel::I_INVITE | Channel::T_TOPIC | Channel::O_OPERATOR);
	std::cout << "Invite: " << (channel.hasMode(Channel::I_INVITE) ? "on" : "off") << std::endl;
	std::cout << "Topic: " << (channel.hasMode(Channel::T_TOPIC) ? "on" : "off") << std::endl;
	std::cout << "Password: " << (channel.hasMode(Channel::K_PASSWORD) ? "on" : "off") << std::endl;
	std::cout << "Operator: " << (channel.hasMode(Channel::O_OPERATOR) ? "on" : "off") << std::endl;
	std::cout << "Limit: " << (channel.hasMode(Channel::L_LIMIT) ? "on" : "off") << std::endl;
	std::cout << std::endl;

    std::cout << "Remove mode invite and password at once:" << std::endl;
	channel.delMode(Channel::I_INVITE | Channel::K_PASSWORD);
	std::cout << "Invite: " << (channel.hasMode(Channel::I_INVITE) ? "on" : "off") << std::endl;
	std::cout << "Topic: " << (channel.hasMode(Channel::T_TOPIC) ? "on" : "off") << std::endl;
	std::cout << "Password: " << (channel.hasMode(Channel::K_PASSWORD) ? "on" : "off") << std::endl;
	std::cout << "Operator: " << (channel.hasMode(Channel::O_OPERATOR) ? "on" : "off") << std::endl;
	std::cout << "Limit: " << (channel.hasMode(Channel::L_LIMIT) ? "on" : "off") << std::endl;
	std::cout << std::endl;

    std::cout << "FAIL Remove mode topic and invite at once:" << std::endl;
	channel.delMode(Channel::I_INVITE | Channel::T_TOPIC);
	std::cout << "Invite: " << (channel.hasMode(Channel::I_INVITE) ? "on" : "off") << std::endl;
	std::cout << "Topic: " << (channel.hasMode(Channel::T_TOPIC) ? "on" : "off") << std::endl;
	std::cout << "Password: " << (channel.hasMode(Channel::K_PASSWORD) ? "on" : "off") << std::endl;
	std::cout << "Operator: " << (channel.hasMode(Channel::O_OPERATOR) ? "on" : "off") << std::endl;
	std::cout << "Limit: " << (channel.hasMode(Channel::L_LIMIT) ? "on" : "off") << std::endl;
	std::cout << std::endl;
}