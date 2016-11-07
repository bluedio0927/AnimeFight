#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
namespace AnimeFight
{

typedef enum {
	TextType
} CommandType;

class Command
{
public:
	enum { header_length = sizeof(uint16_t)};
	enum { max_command_length = 64};
	Command();
	virtual CommandType type();
	virtual char* Content();
	virtual const char* Content() const;
	virtual char* Raw();
	virtual const char* Raw() const;
	virtual void Contentlength(std::size_t length);
	virtual std::size_t Contentlength() const;
	virtual std::size_t Rawlength() const;
	virtual void encode();
	virtual bool decode();
protected:
	char data_[header_length + max_command_length];
	std::size_t command_length_;
};
}
