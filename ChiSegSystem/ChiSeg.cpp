#include "ChiSegSystem.h"

int main(int argc, char* argv[])
{
	
/*
	if (5 != argc)
	{
		cout << "Usage: BreakEntropy.exe <Seg File> <Punc File> <n-gram> <result File> " << endl;
		return 1;
	}

	int n =atoi(argv[3]);
	if ((2 != n) && (3 != n)&&(1 != n))
	{
		cout << "Parameter error: n-gram = 2 or 3" << endl;
		return 1;
	}

	new CCalculator(argv[1], argv[2], n, argv[4]);

	return 0;*/
	ChiSeg *chiseg=new ChiSeg();
	const char* pun_file_path="D:\\coding\\ChineseSegment\\测试文件\\punc.txt";
	const char* one_gram_filepath="D:\\coding\\ChineseSegment\\测试文件\\1gram.txt";
	string dictionary_filepaths[3]={"D:\\coding\\ChineseSegment\\测试文件\\1gram.txt","D:\\coding\\ChineseSegment\\测试文件\\2gram.txt","D:\\coding\\ChineseSegment\\测试文件\\3gram.txt"};
	string source_file="D:\\coding\\ChineseSegment\\测试文件\\agr_seg.txt";
	string result_file="D:\\coding\\ChineseSegment\\测试文件\\result.txt";
	chiseg->MainProcess(pun_file_path,one_gram_filepath,dictionary_filepaths,source_file,result_file);
	
}