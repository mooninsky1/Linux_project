//lihf 2012/08/08 人人网签名算法
#include <set>
class cSortString
{
public:
	bool operator()(const std::string& str1,const std::string& str2)
	{
		return strcmp(str1.c_str(),str2.c_str()) < 0;
	}
};

void renren_Sig(const std::string & strInput ,std::string& strOutput,
				const std::string& strBegin, const std::string &strEnd,int offset);
void Test()
{
	std::string strInput ="xn_sig_in_iframe=1&xn_sig_method=get&xn_sig_time=1329468895803&xn_sig_user=177705358&xn_sig_expires=1329472800&xn_sig_session_key=2.136769bd2e563baaff9ddeea18c3af9d.3600.1329472800-177705358&xn_sig_added=1&xn_sig_api_key=a18bb71e557941d29b517a2c2f070f3d&xn_sig_app_id=126453&xn_sig_domain=renren.com&xn_sig_user_src=rr&xn_sig=b92d95d45dcfad6195cbe8ab6591d464";
	std::string strOutput;
	std::string strBegin="xn_sig_";
	std::string strEnd = "&";
	
	int offset = strBegin.length();
	renren_Sig(strInput,strOutput,strBegin,strEnd,offset);
}

void renren_Sig(const std::string & strInput ,std::string& strOutput,
		  const std::string& strBegin, const std::string &strEnd,int offset)
{
	strOutput.clear();
	int nOffset = 0;
	int nStrlen = strInput.length();

	int nLooplen =0;
	std::set<std::string,cSortString> set_str;
	while(true&&nLooplen<100)
	{
		nLooplen++;
		
		int nPosBegin =  strInput.find(strBegin.c_str(),nOffset);
		int nPosEnd = 0;
		if (nPosBegin != std::string::npos)
		{
			nPosEnd = strInput.find(strEnd.c_str(),nPosBegin);
			if (nPosEnd == std::string::npos)
			{
				nPosEnd = nStrlen;
			}
			std::string str = strInput.substr(nPosBegin+offset,nPosEnd-nPosBegin-offset);
			set_str.insert(str);
			nOffset = nPosEnd;
		}
	}
	typedef std::set<std::string,cSortString>::iterator SetIt;
	for (SetIt it = set_str.begin(); it != set_str.end(); it++)
	{
		strOutput+=(*it);
	}
}