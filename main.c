	int a=1;
	int b=2;
	int c;
void reset_handler(void)
{

	c=pluse_fun(a,b);
	a=c;
	while (1)
		;
}

int pluse_fun(int x ,int y)
{
	return x+y;
}