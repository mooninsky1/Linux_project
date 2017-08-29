//Î»²Ù×÷
void Test()
{
	struct JoinCertRaceRecord
	{
		unsigned int a1:1;
		unsigned int a2:1;
		unsigned int a3:1;
		unsigned int a4:1;
		unsigned int a5:1;
		unsigned int a6:1;
		unsigned int a7:1;
		unsigned int a8:1;
		unsigned int a9:1;
		unsigned int a10:1;
		unsigned int a11:1;
		unsigned int a12:1;
		unsigned int a13:1;
		unsigned int aNULL:19;
	};
	JoinCertRaceRecord myJoinCertRaceRecord;
	memset(&myJoinCertRaceRecord, 0, sizeof(myJoinCertRaceRecord));
	JoinCertRaceRecord *pJoinCertRaceRecord = &myJoinCertRaceRecord;
	myJoinCertRaceRecord.a1 = 1;
	myJoinCertRaceRecord.a2 = 2;
	myJoinCertRaceRecord.a3 = 3;
	myJoinCertRaceRecord.a4 = 5;

	int a = sizeof(myJoinCertRaceRecord);
}