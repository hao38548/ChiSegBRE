#include "ChiSegSystem.h"

int main(int argc, char* argv[])
{
	
/*
	if (5 != argc)
	{
		cout << "Usage: BreakEntropy.exe <Seg File> <Punc File> <n-gram> <result File> " << endl;
		return 1;
	}
D:\\
	int n =atoi(argv[3]);
	if ((2 != n) && (3 != n)&&(1 != n))
	{
		cout << "Parameter error: n-gram = 2 or 3" << endl;
		return 1;
	}

	new CCalculator(argv[1], argv[2], n, argv[4]);

	return 0;*/
	ChiSeg *chiseg=new ChiSeg();
	const char* pun_file_path="E:\\coding\\ChineseSegment\\�����ļ�\\punc.txt";
	const char* one_gram_filepath="E:\\coding\\ChineseSegment\\�����ļ�\\1gram.txt";
	string dictionary_filepaths[3]={"E:\\coding\\ChineseSegment\\ChiSeg-GitHub\\ChiSeg-GitHub\\Normlize\\Normlize\\Result-Way1-1Gram.txt","E:\\coding\\ChineseSegment\\ChiSeg-GitHub\\ChiSeg-GitHub\\Normlize\\Normlize\\Result-Way1-2Gram.txt","E:\\coding\\ChineseSegment\\ChiSeg-GitHub\\ChiSeg-GitHub\\Normlize\\Normlize\\Result-Way1-3Gram.txt"};
	//string source_file="E:\\coding\\ChineseSegment\\�����ļ�\\agr_seg.txt";
	string source_file = "E:\\coding\\ChineseSegment\\���������Ϣ\\5000���\\ũҵ\\���\\ICTCLAS�з��ı�.txt";
	string result_file="E:\\coding\\ChineseSegment\\�����ļ�\\way1-marked-seg-result.txt";
	chiseg->MainProcess(pun_file_path,one_gram_filepath,dictionary_filepaths,source_file,result_file);
	
}