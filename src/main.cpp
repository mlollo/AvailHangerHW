#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <vector>

#define FILENAME "/dev/i2c-1"
#define NB_HANGER 128

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
				std::cout << "removed:" << i;
			}else{
				// Hanger just being deposit
				std::cout << "deposit:" << i;
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

	std::cout << "setup";

	diff(content_act, content_new);
	while(1)
	{
		scan(&file_i2c, content_new);
		diff(content_act, content_new);
	}
	return 0;
}
