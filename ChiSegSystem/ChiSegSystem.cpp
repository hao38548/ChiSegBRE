// ChiSegSystem.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "ChiSegSystem.h"

/*ʵ��Ԥ������*/

bool PreProcessing::InitPrePro(const char*  pun_file_path,const char* one_gram_filepath)
{
	/*���ر������ļ�*/

	if (NULL == pun_file_path)
	{
		cout << "Parameter is NULL ";
		return false;
	}
	ifstream in;
	in.open(pun_file_path, ios::in);
	if (! in.good())
	{
		cout << "Open file failed ";
		return false;
	}
	// ��ȡ�ļ�
	m_puncSet.clear();
	string word;
	float value;
	while (getline(in, word))
	{
		m_puncSet.insert(word);

	}
	in.close();

	/*����һԪ�ʱ��ļ�*/

	if (NULL == one_gram_filepath)
	{
		cout << "Parameter is NULL ";
		return false;
	}
	in.open(one_gram_filepath, ios::in);
	if (! in.good())
	{
		cout << "Open file failed ";
		return false;
	}
	while (!in.eof())
	{
		//ѭ����ȡ�ļ���������ʵ�
		in>>word>>value>>value;
		one_gram_dic.insert(set<string>::value_type(word));
	}
	in.close();
	return true;
}

//����һ��
void PreProcessing::ParseLine(const string& str, Doc& doc)
{
	//���ǰһ�б���ı��
	pun_list.clear();
	doc.clear();
	int sen_cnt = 0;
	size_t s = 0;
	size_t t = string::npos;
	string word;
	while ((t = str.find_first_of(' ', s)) != string::npos)
	{
		if (t > s)
		{
			//�س�һ������
			word = str.substr(s, t-s);
			//�ôʴ���������
			SaveWord(word, doc);
		}
		//����ɨ��ָ��λ��
		s = t+1;
	}
	word = str.substr(s);//substrδָ���ڶ�������������ȡ���ַ�����ĩβ����Ϊ���һ���ʺ�����û�пո��
	if (! word.empty())
		SaveWord(word, doc);
}

//************************************     
// ��������: SaveWord     
// ����˵����     
// ��  �ߣ�Mr.SUN     
// �������ڣ�2015/07/23     
// �� �� ֵ: void     
// ��    ��: const string & word     
// ��    ��: Doc & doc     
//************************************
void PreProcessing::SaveWord(const string& word, Doc& doc)
{
	set<string>::iterator iter=m_puncSet.find(word);
	if (iter == m_puncSet.end())
	{
		// �Ǳ�㣺����
		if (0 == doc.size())
		{
			doc.push_back(Sentence());
		}
		set<string>::iterator iter = one_gram_dic.find(word);
		if (iter == one_gram_dic.end())
			cout << "Unrecognized word: [" << word << "]" << endl;
		else
			//���ôʵ���������洢
			doc[doc.size()-1].push_back(*iter);
	}
	else
	{
		// ��㣺���������������һ���վ䣩
		size_t sen_cnt = doc.size();
		if ((sen_cnt > 0) && (doc[sen_cnt-1].size() == 0))//doc[sen_cnt-1].size()��ʾ�Ǹ��վ�
		{
			doc.erase(doc.begin()+sen_cnt-1);
		}
		pun_list.push_back(*iter);//Ϊ�˱���һ�������еı�����
		//���Ļ�����һ���µľ���
		doc.push_back(Sentence());
	}
}

//************************************     
// ��������: U2G     
// ����˵����     
// ��  �ߣ�Mr.SUN     
// �������ڣ�2015/07/23     
// �� �� ֵ: char*     
// ��    ��: const char * utf8     
//************************************
char* PreProcessing::U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}



//************************************     
// ��������: GenerateDictionarys     
// ����˵����  ���ɲ�ѯNԪ��֧�ص��ֵ�ṹ   
// ��  �ߣ�Mr.SUN     
// �������ڣ�2015/07/22     
// �� �� ֵ: bool  ���ֵ����� �ɹ����   
// ��    ��: string filepaths[3]   �����ֵ��ļ�·��  
//************************************
bool ChiSeg::GenerateDictionarys(string filepaths[3])
{
	string word,temp_word;
	BE be;
	unsigned long long word_cnt=0;//�����ȡ�˶��ٴʻ�ļ�����
	cout<<"Generating Dictionaries";
	//ѭ����ȡ�����ļ���������ʵ���
	for (int i=0;i< 3;i++)
	{
		word_cnt = 0;
		ifstream in;
		in.open(filepaths[i].c_str(), ios::in);
		if (! in.good())
		{
			cout << "Open file failed ";
			return false;
		}
		// ��ȡ�ļ�
		while(!in.eof())
		{
			word="";//������ַ���������
			//��ȡ�ַ�����Ϣ
			for (int j=0;j<=i;j++)
			{
				in>>temp_word;
				word+=temp_word;
			}
			in  >> be.lbe >> be.rbe;
			//�������ؽ�����Ӧ���ֵ���
			dictionary[i].insert(map<string ,BE>::value_type(word,be));
			//��ʾ������ȵı�ʾ
			if (word_cnt++%20000 == 0)
			{
				cout<<".";
			}
		}
		in.close();
	}
	return true;
}


//************************************     
// ��������: GenerateHMM     
// ����˵����     
// ��  �ߣ�Mr.SUN     
// �������ڣ�2015/07/22     
// �� �� ֵ: bool     
// ��    ��: Sentence sentence     
//************************************
void ChiSeg::GenerateHMM(Sentence sentence)
{
	//��ʼ��ģ�͵ĸ�������

	//�۲������ǲ�յĿո���Ŀ
	hmm.observestates_cnt=sentence.size()-1;
	//��������ÿ������
	hmm.hidden_states_cnt=hmm.observestates_cnt*2;
	//��ת�ƾ�����и�ֵ


}

void ChiSeg::GenerateGraph(Sentence sentence)
{
	Node newNode;//
	hierachy.clear();
	SingleHierachy single;
	//Ӧ�������γɵ�ԭʼ�з־����γɷִʴ�ͼ
	int sentenceLength=sentence.size();
	//����ض����Ĳ��
	for (int j=0;j<sentenceLength;j++)
	{
		hierachy.push_back(single);
	}
	//NԪɨ����Ʊ���
	for (int i=0;i<sentenceLength;i++)
	{
		//�γ����п��ܵ��з�״̬��������Ӧ�Ĳ����
		for (int j=i;j<sentenceLength&&(j-i)<3;j++)
		{
			//(j-i)=1ʱ��ʾ�Ƕ�Ԫ�ʣ�id=sentence[j-1]*maxID+sentence[j]
			//(j-i)=2ʱ��ʾ����Ԫ�ʣ�id=sentence[j-2]*maxID+sentence[j-1]8maxid+sentence[j]
			if(j-i == 0)
			{
				newNode.node_word = sentence[j];
				newNode.n=1;
			}
			if (j-i == 1)
			{
				newNode.node_word = sentence[j-1]+sentence[j];
				newNode.n=2;
			}
			if (j-i == 2)
			{
				newNode.node_word = sentence[j-2]+sentence[j-1]+sentence[j];
				newNode.n=3;
			}	
			//�ֵ��ȡ�ýڵ��Ȩֵ
			newNode.score=GetBEValues(newNode.node_word,j-i+1);
			//�ڵ����ֵĬ��Ϊ�ýڵ��Ȩֵ
			newNode.current_maxscore=newNode.score;
			//�ڵ����ò�
			hierachy[j].insert(newNode);
		}
	}

}


//************************************     
// ��������: ViterbiStyleAlgorithm     
// ����˵����  ά�ر��㷨Ѱ������·��   
// ��  �ߣ�Mr.SUN     
// �������ڣ�2015/07/23     
// �� �� ֵ: std::string     
// ��    ��: Sentence sentence     
//************************************
string ChiSeg::ViterbiStyleAlgorithm(Sentence sentence)
{
	Node temp;
	int senLength=sentence.size();
	vector<Node> optimalCandidates(senLength);
	for (int i=0;i<senLength;i++)
	{
		//��ʼ����ǰ��ε�����ֵ
		optimalCandidates[i].current_maxscore=0;
		//����һ���еĽڵ�ֵ
		SingleHierachy single=hierachy[i];
		SingleHierachy::iterator iter;
		for (iter=single.begin();iter!=single.end();iter++)
		{
			int keyLength=iter->n;
			int flag=i-keyLength;
			if (flag<0)//��������ͼ��ͷ
			{
				temp=*iter;
				//temp.path.push_back(iter->key.key);		
				temp.current_maxscore=iter->score;
				hierachy[i].erase(*iter);
				hierachy[i].insert(temp);
			}
			else//δ��������ͼ��ͷ
			{
				temp=*iter;
				Node backOptimum = optimalCandidates[flag];
				float backOptimumScore=backOptimum.current_maxscore;
				temp.current_maxscore+=backOptimumScore;				
				hierachy[i].erase(*iter);
				hierachy[i].insert(temp);
			}
			if (temp.current_maxscore>=optimalCandidates[i].current_maxscore)
			{
				optimalCandidates[i]=temp;
				/*optimalCandidates[i].current_maxscore=temp.current_maxscore;
				optimalCandidates[i].n=temp.n;*/
			}
		}
	}

	//������յ��зֽ��
	//ջ�ṹ��ʱ������
	stack<string> results_stack;
	string result="";
	int sen_cnt=senLength-1;
	while (sen_cnt >=0)
	{
		results_stack.push(optimalCandidates[sen_cnt].node_word);
		sen_cnt-=optimalCandidates[sen_cnt].n;
		if (results_stack.size()>50)
		{
			cout<<"����������ѭ��------"<<endl;
			break;
		}
	}
	while (!results_stack.empty())
	{
		result+=results_stack.top()+" ";
		results_stack.pop();
	}
	//Ϊ��ȥ��ĩβ�Ŀո�
	return result.substr(0,result.length()-1);

}
	
float ChiSeg::GetBEValues(string word,int n)
{
	//���Ƿ�֧������һ��ֵΪ0���򷵻�0
	if (n == 1)
	{
		float value=dictionary[0][word].lbe*dictionary[0][word].rbe;
		//��ֹlog����һ������ĸ���
		return value > 1?(log(value)/log((double)2)):value;
	}
	if (n == 2)
	{
		float value=dictionary[1][word].lbe*dictionary[1][word].rbe;
		return value*0.819;
/*		return dictionary[1][word].lbe*dictionary[1][word].rbe*log(3.0)/log((double)2);*/
	}
	if (n == 3)
	{
		float value=dictionary[2][word].lbe*dictionary[2][word].rbe;
		return value*log(3.0)/log((double)2);
/*		return dictionary[2][word].lbe*dictionary[2][word].rbe* log(3.90)/log((double)2);*/
	}
}





//************************************     
// ��������: ViterbiStyleAlgorithm     
// ����˵����     
// ��  �ߣ�Mr.SUN     
// �������ڣ�2015/07/23     
// �� �� ֵ: float     
// ��    ��: vector<string> part_sentence     ������Ѿ��Ϻõľ���
// ��    ��: stack<string> code_result     �ݴ�ݹ�����ջ
//************************************
/*
float ChiSeg::ViterbiStyleAlgorithm(vector<string> part_sentence,vector<string> code_result[3])
{
	int sen_len=part_sentence.size();
	//����0���ʣ�����1
	if (sen_len == 0)
	{
		return 1;
	}
	//���ǵ����ʣ������䱾��ķ�֧��
	else if (sen_len == 1)
	{
		return GetBEValues(part_sentence[0],1);
	}
	//����˫�ʣ�ֻ��Ƚ����ֵĴ�С����
	else if (sen_len == 2)
	{
		//ƴ�Ӷ�Ԫ�ʻ�
		string find_word=part_sentence[0]+" "+part_sentence[1];
		float value1=GetBEValues(find_word,2);
		//�Ƴ�part_sentence��һ��Ԫ�أ���Ϊ�ݹ�Ĳ���
		part_sentence.erase(part_sentence.begin());
		float value2=GetBEValues(part_sentence[0],1)*ViterbiStyleAlgorithm(part_sentence);
	}
	//�ʻ������Ԫ
	else
	{
		float value[3];
		string find_word="";
		for (int i=0;i<3;i++)
		{
			find_word+=part_sentence[0];
			part_sentence.erase(part_sentence.begin());
			value[i] = GetBEValues(find_word,i+1)*ViterbiStyleAlgorithm(part_sentence,code_result);
		}
		//�������ֵ
		float max_value=value[0];
		if (value[1] >max_value)
		{
			max_value = value[1];
			return max_value;
		}
		else if (value[2] >max_value)
		{
			max_value =value[2];
			return max_value;
		}
		else
		{

			return max_value;
		}
		
		
	}
}*/


bool ChiSeg::MainProcess(const char* pun_file_path,const char* one_gram_filepath,string dictionary_filepaths[3],string source_file,string result_file)
{
	//��ʼ������
	PreProcessing *pre=new PreProcessing();
	// ������֤
	if (NULL == pun_file_path || NULL == one_gram_filepath)
	{
		cout<< "Parameter is NULL ";
		return false;
	}
	//��ʼ��Ԥ������
	pre->InitPrePro(pun_file_path,one_gram_filepath);

	//���شʵ�

	GenerateDictionarys(dictionary_filepaths);
	ofstream out;
	out.open(result_file.c_str(), ios::out);
	if (! out.good())
	{
		cout << "Open result file failed ";
		return false;
	}
	ifstream in;
	in.open(source_file.c_str(), ios::in);
	if (! in.good())
	{
		cout << "Open file failed ";
		return false;
	}
	int doc_cnt = 0;
	string buff;
	Doc doc;
	string final_result;
	while (getline(in, buff))
	{
		int pun_cnt=0;
		pre->ParseLine(buff, doc);				// ������ǰ��
		//ѭ�������µ�ÿһ������з֣������γɴ�ͼ��Ȼ��ά�رȣ�
		for (unsigned int i=0; i<doc.size(); i++)
		{
			if (doc[i].size()!= 0)
			{
				final_result="";
				//�����зִ�ͼ
				GenerateGraph(doc[i]);
				//ά�ر��㷨Ѱ������·��
				final_result=ViterbiStyleAlgorithm(doc[i]);
				do 
				{
					final_result+=pre->pun_list[pun_cnt];
					pun_cnt++;
				} while (pre->pun_list[pun_cnt]=="|||");
				out<<final_result;
			}						
	    }
		out<<endl<<buff;
		out<<"\n";
		if ((doc_cnt++)%1000==0)
		{
			cout<<".";
		}		
	}
	in.close();
	out.close();
}

