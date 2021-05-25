#include"Kernelization.h"
#include<iostream>
#include<vector>
int main(void)
{
	Kernelization obj;
	obj.readfile("haberman.csv");
	obj.stratifydata();
	obj.sortdata();
	obj.showresults();
	
	
	return 0;
}
