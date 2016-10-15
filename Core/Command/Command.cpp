#include "Command.h"
#include <iostream>
namespace AnimeFight
{

Command::Command(): command_length_(0)
{
}
CommandType Command::type()
{
	return TextType;
}
char* Command::Raw()
{
	return data_;
}
const char* Command::Raw()const
{
	return data_;
}
char* Command::Content()
{
	return data_ + header_length;
}
const char* Command::Content()const
{
	return data_ + header_length;
}
void Command::Contentlength(std::size_t length)
{
	command_length_ = max_command_length < length ? max_command_length : length;
}
std::size_t Command::Contentlength() const
{
	return command_length_;
}
std::size_t Command::Rawlength() const
{
	return command_length_ + header_length;
}
void Command::encode()
{
	char header[header_length + 1] = "";
	std::sprintf(header, "%2d", static_cast<uint16_t>(command_length_));
	std::memcpy(data_, header, header_length);
}
bool Command::decode()
{
	char header[header_length + 1] = "";
	std::strncat(header, data_, header_length);
	command_length_ = std::atoi(header);
	if (command_length_ > max_command_length) {
		command_length_ = 0;
		return false;
	}
	return true;
}
}
