namespace rcode
{
	int utf8_to_gbk_c(char* src,char* dst)
	{
		push dst
		push src
		calle "utf8_to_gbk"
		mov s_ret,eax
		add esp,8
	}

	rstr utf8_to_gbk(rstr s)
	{
		rstr ret
		ret.set_size utf8_to_gbk_c(s.cstr,null)
		utf8_to_gbk_c(s.begin,ret.begin)
		ret.pop
		return ret
	}

	rstr utf8_to_utf16(rstr s)
	{
		ushort temp;
		rstr result;
		for (int i=0;i<s.count();i++)
		{
			if (is_utf8_3(s[i]))
			{
				if (i+2>=s.count())
				{
					continue;
				}
				temp=0;
				temp=OR(temp,SHL(AND(s[i],0xef),12)).toushort
				temp=OR(temp,SHL(AND(s[i+1],0x3f),6)).toushort
				temp=OR(temp,AND(s[i+2],0x3f)).toushort
				result.push(get_first(temp));
				result.push(get_second(temp));
				i+=2;
			}
			elif (is_utf8_2(s[i]))
			{
				if (i+1>=s.count())
				{
					continue;
				}
				temp=0;
				temp=OR(temp,SHL(AND(s[i],0x1f),6)).toushort
				temp=OR(temp,AND(s[i+1],0x3f)).toushort
				result.push(get_first(temp));
				result.push(get_second(temp));
				i++;
			}
			else
			{
				result.push(s[i]);
				result.push(0.tochar);
			}
		}
		return result;
	}

	rstr utf16_to_utf8(rstr s)
	{
		rstr result;
		if (s.count()%2!=0)
		{
			return result;
		}
		ushort temp;
		for (int i=0;i<s.count();i+=2)
		{
			if (s[i]<=0x7f&&s[i+1]==0)
			{
				result+=s[i];
				continue;
			}
			temp=*(s.begin()+i).to<ushort*>;
			if(s[i]>0x7f&&s[i+1]<=0x7)
			{
				result.push(OR(SHR(temp,6),0xc0).tochar);
				result.push(OR(AND(temp,0x3f),0x80).tochar);
			}
			else
			{
				result.push(OR(SHR(temp,12),0xe0).tochar);
				result.push(OR(AND(SHR(temp,6),0x3f),0x80).tochar);
				result.push(OR(AND(temp,0x3f),0x80).tochar);
			}
		}
		return result;
	}
	
	static char get_second(ushort ch)
	{
		return *((&ch).to<char*>+1);
	}

	static char get_first(ushort ch)
	{
		return *((&ch).to<char*>);
	}

	//是否utf8 3个字节起始
	static rbool is_utf8_3(char ch)
	{
		return int(ch)>=0xe0&&int(ch)<=0xef;
	}

	static rbool is_utf8_2(char ch)
	{
		return int(ch)>=0xc0&&int(ch)<=0xdf;
	}
}