#include "../common/iStream.h"
#include <vector>
struct PlayerDog
{
	// 狗的等级
	int uDogLevel;
	// 狗的ID
	int uDogID;
	// 狗的索引
	int uDogIndex;
	// 狗的经验
	int uDogExperience;
	// 狗的星级
	int uDogStar;
	// 狗的成长
	int uDogGrowup;
	// 狗的心情
	int uDogMood;
	// 狗的体力
	int uDogForce;
	// 狗的敏捷
	int uDogCel;
	// 狗的美观
	int uDogSurface;
	// 狗的名称
	char szDogName[17];

	//
	PlayerDog()
	{
		Clear();
	}
	//
	void Clear()
	{
		// 狗的等级
		uDogLevel = 0;
		// 狗的ID
		uDogID = 0;
		uDogIndex = 0;
		// 狗的经验
		uDogExperience = 0;
		uDogStar = 0;
		uDogGrowup = 0;
		uDogMood=0;
		uDogForce = 0;
		uDogCel = 0;
		uDogSurface = 0;
		// 狗的名称
		memset(szDogName, 0, sizeof(szDogName));
	}
	bool To_Stream(nsCommon::cOStream &Ostream)
	{
		//int version = 1;
		int version = 2;

		Ostream  << version << uDogLevel<<uDogID <<uDogIndex<<uDogExperience<< uDogStar << uDogGrowup <<uDogMood << uDogSurface
			<< uDogCel << uDogSurface;
		return true;
	}
	bool From_Stream(nsCommon::cIStream &Istream)
	{
		int version;
		int uDogLevel = 0;
		int uDogID = 0;
		Istream >> version;
		if (version == 1)
		{
			int uDogLevel =2;
			Istream >> uDogLevel;
		}
// 		Istream >>uDogID >>uDogIndex>>uDogExperience>> uDogStar >> uDogGrowup >>uDogMood >> uDogSurface
// 			>> uDogCel >> uDogSurface;
		else if (version == 2)
		{
			Istream >> uDogID >>uDogIndex>>uDogExperience>> uDogStar >> uDogGrowup >>uDogMood >> uDogSurface
				>> uDogCel >> uDogSurface;
		}

		return true;
	}
};

void Test()
{
	std::vector<PlayerDog> vecDog;
	int n = 10; 
	for (int i=0; i<n; i++)
	{
		PlayerDog  tempDog;
		tempDog.uDogID = i;
		vecDog.push_back(tempDog);
	}
	nsCommon::cIStream Istream;
	nsCommon::cOStream Ostream;

	
	for (int i=0; i < n; i++)
	{
		PlayerDog tempdog = vecDog[i];
		Ostream << n;
		tempdog.To_Stream(Ostream);
	}
	std::vector<PlayerDog> vecDog1;
	nsCommon::cStreamBinaryBufferReader binareader(0,0);
	int size = Ostream.GetDataSize();
	binareader.SetData(Ostream.GetData(),Ostream.GetDataSize());
	Istream.SetReader(&binareader);
	int cout;
	Istream>>cout;
	for (int i = 0 ; i <cout; i++)
	{
		PlayerDog tempdog;
		tempdog.From_Stream(Istream);
		vecDog1.push_back(tempdog);
	}
	
	
}