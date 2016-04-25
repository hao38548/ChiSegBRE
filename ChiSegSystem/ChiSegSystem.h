#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <map>
#include <set>
#include <vector>
#include <windows.h>

using namespace std;

//��������Ʒ�ģ�ͽṹ

typedef struct  
{
	int hidden_states_cnt;//����״̬����Ŀ���ڱ����ķִ���Ϊ2����������ʶ���У�����Ŀÿ����ξ���һ��
	int observestates_cnt;//�۲쵽�����г��ȣ����۲�״̬��Ŀ���ڷִ��в������ڹ۲����У�����˵�������Ϊ1�����迼����
	double* strat_vector;//��ʼ��������
	double** transfer_matrix;//ת�Ƹ��ʾ���
	//��Ӧ����һ���������󣬵���ϵͳ�о�Ϊһ�����Բ��迼��
}HMM;
//����HMM�����ڵ�ṹ
typedef struct 
{
	string path;
	float currentMaxValue;

}hmmNode;
//�����֧�ؽṹ
typedef struct{
	float lbe;
	float rbe;
}BE;

//��ͼ�ڵ�ṹ
struct Node{
	string node_word;
	float score;
	int n;//�����ýڵ�洢���Ǽ�Ԫ�ʻ�
	float current_maxscore;
	//vector<string> path;
	bool operator < (const Node& a) const
	{
		//��node_word�ɴ�С����
		return a.node_word < node_word;
	}

};

//��ͼ������νṹ
typedef set<Node> SingleHierachy;


typedef vector<string> Sentence;
typedef vector<Sentence> Doc;
typedef map<string,float> Dictionary;

class ChiSeg{
private:
	Dictionary dictionary[3];
	HMM hmm;
	vector<SingleHierachy> hierachy;//��ͼ�ṹ�����ղ����֯
public:
	//���������ʵ�
	bool GenerateDictionarys(string filepaths[3]);
	//��ѯĳ���ʻ�ķ�֧��
	float GetBEValues(string word,int n);
	//��������Ʒ�ģ��
	void GenerateHMM(Sentence sentence);
	//Viterbi�㷨
	//float ViterbiStyleAlgorithm(vector<string> part_sentence,stack<string> code_result);
	string ViterbiStyleAlgorithm(Sentence sentence);
	//���ɷִʴ�ͼ
	void GenerateGraph(Sentence sentence);
	//����HMMת�ƾ���
	void GenHMMTransMat(Sentence sentence, float* transferMar);
	//���㷨����

	bool MainProcess(const char* pun_file_path,const char* one_gram_filepath,string dictionary_filepaths[3],string source_file,string result_file);

};

class PreProcessing{
private:
	//�����ż���
	set<string> m_puncSet;
	//ԭʼ����ľ���
	string original_sentence;
	//һԪ�ʻ�ʵ�
	set<string> one_gram_dic;
public:
	//һ�仰�ı����ű�������
	vector<string> pun_list;
	//��ʼ�����������ļ���һԪ�ʱ��ļ�
	bool InitPrePro(const char*  pun_file_path,const char* one_gram_filepath);
	//����һ��
	void ParseLine(string& str, Doc& doc);
	//����һ���ʻ�������½ṹ��
	void SaveWord(const string& word, Doc& doc);

	//��UTF-8ת��Ϊgbk
	char* U2G(const char* utf8);

};