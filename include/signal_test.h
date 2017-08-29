#pragma once
#include <signal.h>
int sig_usr(int);
int Test()
{
	if(signal(SIGUSR1,sig_usr) == SIG_ERR)
		printf("can't catch usr1 signal");
	if(signal(SIGUSR2,sig_usr) == SIG_ERR)
		printf("can't catch usr2 signal");
	for (;;)
	{
		Sleep(5);
	}
}

int sig_usr(int signo)
{
	if (signo == SIGUSR1)
	{
		printf("get usr1 signal");
	}
	else if (signo == SIGUSR2)
	{
		printf("get usr2 signal");
	}
	else
	{
		printf("error signo catch!");
	}

}