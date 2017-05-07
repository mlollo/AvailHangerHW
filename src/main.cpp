#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <vector>
#include "../boost/network.hpp"
#include "../boost/network/protocol/http/client.hpp"

#define FILENAME "/dev/i2c-1"
#define NB_HANGER 128

using namespace boost::network;
using namespace boost::network::http;

char token = "";

int connect(int *desc_file){
	//Ouverture du bus I2C
	if((*desc_file = open(FILENAME, O_RDWR)) < 0)
	{
		std::cout << "Echec de l'ouverture du bus I2C\n";
		return -1;
	}
	std::cout << "Bus ouvert\n";
	return 0;
}

int scan(int *desc_file, char *content){
	int n = 0;
	int state = 0;
	unsigned char buffer[1];
	buffer[0] = 0x01;
	for(int addr = 0; addr < NB_HANGER; addr++)
	{
		if(state = ioctl(*desc_file, I2C_SLAVE, addr) < 0)
		{
			std::cout << "Echec de l'acces au bus et de la communication avec l'esclave\n";
		}
		else if(read(*desc_file, buffer, 1) < 0)
		{
			content[addr] = 0;
			//std::cout << "ESCLAVE ABSENT\n";
		}
		else
		{
			content[addr] = 1;
			n++;
			//std::cout << "ESCLAVE" << addr << "PRESENT\n";
		}
	}
	return n;
}

int diff(char* content_old, char* content_new)
{
	int nb = 0;
	for(int i = 0; i < NB_HANGER; i++)
	{
		if(content_old[i] != content_new[i])
		{
			nb++;
			std::cout << "Cintre #" << i << ((content_old[i])? " Retiré" : " Ajouté") << std::endl;
			if(content_old[i] == 1){
				// Hanger just being removed
				client::request request_("http://2bb05442.ngrok.io/api/hanger/:i?token="+token);
				client client_;
				// request << header("Content-Type", "application/x-www-form-urlencoded");
				request << body("f_onRail=false");
				client::response response_ = client_.put(request_,body);
				std::string body_ = body(response_);
				std::cout << "[REQUEST] put hanger : " + body_;
			}else{
				// Hanger just being deposit
				client::request request_("http://2bb05442.ngrok.io/api/hanger/:i?token="+token);
				client client_;
				// request << header("Content-Type", "application/x-www-form-urlencoded");
				request << body("f_onRail=true");
				client::response response_ = client_.put(request_,body);
				std::string body_ = body(response_);
				std::cout << "[REQUEST] put hanger : " + body_;
			}
			content_old[i] = content_new[i];
		}
	}
}

int main()
{
	int file_i2c;
	connect(&file_i2c);

	char content_act[NB_HANGER] = "";
	char content_new[NB_HANGER] = "Lul";

	client::request request_("http://2bb05442.ngrok.io/api/getToken/");
	request_ << header("Authorization", "8D0dZXMIBeiWSj7:YzDVJPRyIUp7DS0");
	client client_;
	client::response response_ = client_.get(request_);
	std::string body_ = body(response_);
	std::cout << "[REQUEST] Token : " + body_;
	// token = body_.token;
	// std::cout << token;

	diff(content_act, content_new);
	while(1)
	{
		scan(&file_i2c, content_new);
		diff(content_act, content_new);
	}
	return 0;
}
