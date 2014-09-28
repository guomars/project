#include "PackTool.h"
#include <stdio.h>
#include<iostream>

using namespace std;

void help()
{
	printf("please use as ./PackTool source_dir dest_dir md5file\n");
}

int main(int argc,char *argv[])
{
	if (!PackTool::GetInstance().Init(argc,argv))
	{
		printf("PackTool init failed.\n");
		help();
		return -1;
	}

	printf("Begin Pack.\n");

	int ret = PackTool::GetInstance().Pack();

	if (ret != 0)
	{
		printf("Pack failed. ret=%d\n",ret);
		return -1;
	}

	printf("Pack Succed.\n");

	while(true)
	{
		Sleep(1);
	}

	return 0;
}