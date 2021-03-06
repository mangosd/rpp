
class char
{
	rd1 m_in;

	~char()
	{
	}

	char()
	{
	}

	char(char& a)
	{
		mov esi,this
		mov edi,a
		mov1 [esi],[edi]
	}

	char(char a)
	{
		mov esi,this
		mov1 [esi],a
	}

	int toint()
	{
		mov esi,this
		mov s_ret,0
		mov1 s_ret,[esi]
	}

	uint touint()
	{
		mov esi,this
		mov s_ret,0
		mov1 s_ret,[esi]
	}

	rstr torstr()
	{
		rstr ret(this)
		return ret
	}

	char tochar()
	{
		mov esi,this
		mov1 s_ret,[esi]
	}

	operator=(char& a)
	{
		mov esi,this
		mov edi,a
		mov1 [esi],[edi]
	}

	operator=(char a)
	{
		mov esi,this
		mov1 [esi],a
	}
	
	operator=(int a)
	{
		mov esi,this
		mov1 [esi],a
	}

	operator=(uint a)
	{
		mov esi,this
		mov1 [esi],a
	}

	operator++()
	{
		this=toint+1
	}

	friend operator<->(char& a,char& b)
	{
		c=a
		a=b
		b=c
	}

	friend bool operator==(char a,char b)
	{
		return a.toint==b.toint
	}

	friend bool operator!=(char a,char b)
	{
		return a.toint!=b.toint
	}

	friend bool operator>(char a,char b)
	{
		return a.toint>b.toint
	}

	friend bool operator>=(char a,char b)
	{
		return a.toint>=b.toint
	}

	friend bool operator<(char a,char b)
	{
		return a.toint<b.toint
	}

	friend bool operator<=(char a,char b)
	{
		return a.toint<=b.toint
	}

	set(char a)
	{
		mov esi,this
		mov1 [esi],a
	}

	set(int a)
	{
		mov esi,this
		mov1 [esi],a
	}

	clear()
	{
		set(0)
	}

	bool empty()
	{
		return this.toint==0
	}

	print()
	{
		rf.print this.torstr
	}

	printl()
	{
		rf.printl this.torstr
	}
}