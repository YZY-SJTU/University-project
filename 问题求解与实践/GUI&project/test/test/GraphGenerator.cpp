#include "GraphGenerator.h"

string ChangeToString(int x)
{
	string result;
	int digit = 1, multiple = 1;
	int tmp = x;
	while (x >= 10)
	{
		x /= 10;
		++digit;
		multiple *= 10;
	}

	for (int i = 0; i < digit; ++i)
	{
		result += char('0' + tmp / multiple);
		tmp = tmp - (tmp / multiple) * multiple;
		multiple /= 10;
	}
	return result;
}

void GraphGenerator::setNodeRange(int x)
{
	if (x > 0)
		NodeRange = x;
}

void GraphGenerator::setWeightRange(int x)
{
	if (x > 0)
		WeightRange = x;
}

void GraphGenerator::setPInEdge(int x)
{
	if (x > 0)
		EdgeRange = x;
}

//����һ��x���������ļ���ΪfileName��ͼ�ļ�
void GraphGenerator::generate(int x, string fileName)
{
	ofstream file(fileName);
	if (!file)
	{
		cerr << "create file error" << endl;
		return;
	}

	fileNode result;
	result.fileName = fileName;

	for (int i = 0; i < x; ++i)
	{
		bool isEdge = bool(rand() % EdgeRange);//�����ָ���Ϊ1/EdgeRange
		if (!isEdge && result.currentNode.size() < NodeRange)//�������
		{
			int tmp;
			while (true)
			{
				tmp = rand() % NodeRange + 1;//�������1-NodeRange֮��
				int j;
				for (j = 0; j < result.currentNode.size(); ++j)
				{
					if (tmp == result.currentNode[j])
						break;
				}
				if (j == result.currentNode.size())
				{
					result.currentNode.push_back(tmp);
					file << '<' << tmp << '>' << endl;
					break;
				}
			}
		}
		else
		{
			int pre = rand() % NodeRange + 1;//ǰ�ý��
			int next = rand() % NodeRange + 1;//���ý��
			double weight = RandDouble();
			file << '<' << pre << ' ' << next << ' ' << weight << '>' << endl;

			int j;
			for (j = 0; j < result.currentNode.size(); ++j)
			{
				if (pre == result.currentNode[j])
					break;
			}
			if (j == result.currentNode.size())
			{
				result.currentNode.push_back(pre);
			}
			for (j = 0; j < result.currentNode.size(); ++j)
			{
				if (next == result.currentNode[j])
					break;
			}
			if (j == result.currentNode.size())
			{
				result.currentNode.push_back(next);
			}
		}
		storedNode.push_back(result);
	}
	file.close();
}

//���ļ���ΪfileName��ͼ�ļ�����׷��y������
void GraphGenerator::add(string fileName, int y)
{
	int refer;
	for (refer = 0; refer < storedNode.size(); ++refer)
	{
		if (fileName == storedNode[refer].fileName)
			break;
	}
	if (refer == storedNode.size())
	{
		fileNode tmp;
		tmp.fileName = fileName;
		storedNode.push_back(tmp);
	}

	ofstream file;
	file.open(fileName, fstream::app);
	if (!file)
	{
		cerr << "open file error" << endl;
		return;
	}
	for (int i = 0; i < y; ++i)
	{
		bool isEdge = bool(rand() % EdgeRange);//�����ָ���Ϊ1/EdgeRange
		if (!isEdge && storedNode[refer].currentNode.size() < NodeRange)//�������
		{
			while (true)
			{
				int tmp;
				tmp = rand() % NodeRange + 1;//�������1-NodeRange֮��
				int j;
				for (j = 0; j < storedNode[refer].currentNode.size(); ++j)
				{
					if (tmp == storedNode[refer].currentNode[j])
						break;
				}
				if (j == storedNode[refer].currentNode.size())
				{
					storedNode[refer].currentNode.push_back(tmp);
					file << '<' << tmp << '>' << endl;
					break;
				}
			}
		}
		else
		{
			int pre = rand() % NodeRange + 1;//ǰ�ý��
			int next = rand() % NodeRange + 1;//���ý��
			double weight = RandDouble();
			file << '<' << pre << ' ' << next << ' ' << weight << '>' << endl;

			int j;
			for (j = 0; j < storedNode[refer].currentNode.size(); ++j)
			{
				if (pre == storedNode[refer].currentNode[j])
					break;
			}
			if (j == storedNode[refer].currentNode.size())
			{
				storedNode[refer].currentNode.push_back(pre);
			}
			for (j = 0; j < storedNode[refer].currentNode.size(); ++j)
			{
				if (next == storedNode[refer].currentNode[j])
					break;
			}
			if (j == storedNode[refer].currentNode.size())
			{
				storedNode[refer].currentNode.push_back(next);
			}
		}
	}

	file.close();
}

double GraphGenerator::divideGraph(int n, string fileName)
{
	//��¼ͼ�ļ������еĳ��ֽ��

	vector<int> Node;//ͼ�ļ��Ľ�㼯
	ifstream infile(fileName);
	if (!infile)
	{
		cerr << "open file error" << endl;
		return -1;
	}
	char ch;
	int cnt = 1;
	reference tmp1, tmp2, tmp3;
	while ((ch = infile.get()) != EOF)
	{
		if ((ch <= '9' && ch >= '0') || ch == '.')
		{
			if (cnt == 1)
				tmp1.input(ch);
			if (cnt == 2)
				tmp2.input(ch);
			continue;
		}
		if (ch == '>')
		{
			if (tmp1.length() != 0)
			{
				int i;
				for (i = 0; i < Node.size(); ++i)
				{
					if (Node[i] == int(tmp1.output()))
						break;
				}
				if (i == Node.size())
					Node.push_back(int(tmp1.output()));
			}

			if (tmp2.length() != 0)
			{
				int i;
				for (i = 0; i < Node.size(); ++i)
				{
					if (Node[i] == int(tmp2.output()))
						break;
				}
				if (i == Node.size())
					Node.push_back(int(tmp2.output()));
			}
			tmp1.clear();
			tmp2.clear();
			cnt = 1;
			continue;
		}
		else
		{
			if (tmp1.length() != 0)
			{
				if (tmp2.length() != 0)
					cnt = 3;
				else cnt = 2;
			}
		}
	}
	infile.close();

	//��ͼ�ļ�ת��Ϊ�ڽӱ�
	adjListGraph<int, double> store(Node.size(), Node);
	ifstream file(fileName);

	while ((ch = file.get()) != EOF)
	{
		if ((ch <= '9' && ch >= '0') || ch == '.')
		{
			if (cnt == 1)
				tmp1.input(ch);
			if (cnt == 2)
				tmp2.input(ch);
			if (cnt == 3)
				tmp3.input(ch);
			continue;
		}
		if (ch == '>')
		{
			if (cnt >= 3)
				store.insert(int(tmp1.output()), int(tmp2.output()), tmp3.output());
			tmp1.clear();
			tmp2.clear();
			tmp3.clear();
			cnt = 1;
			continue;
		}
		else
		{
			if (tmp1.length() != 0)
			{
				if (tmp2.length() == 0)
					cnt = 2;
				else cnt = 3;
			}
		}
	}
	file.close();

	cnt = 0;//��ͼ��ż�����

	//�ж�n������λ�õ�ֵ
	if (n <= 0)
	{
		cerr << "impossible division" << endl;
		return -1;
	}
	if (n == 1)
	{
		double totalWeight = 0;
		for (int i = 0; i < Node.size(); ++i)
		{
			string subFileName("subGraph");
			++cnt;
			subFileName += ChangeToString(cnt);
			ofstream outfile(subFileName);
			if (!outfile)
			{
				cerr << "subFile create error" << endl;
				return -1;
			}
			outfile << '<' << Node[i] << '>' << endl;
			adjListGraph<int, double>::edgeNode* tmp = store.ListNode(i).head;
			while (tmp != NULL)
			{
				if (tmp->end == i)
					outfile << '<' << Node[i] << ' ' << Node[i] << ' ' << tmp->weight << '>' << endl;
				tmp = tmp->next;
			}
			tmp = store.ListNode(i).head;
			while (tmp != NULL)
			{
				if (tmp->end != i)
				{
					outfile << '<' << Node[i] << ' ' << "subGraph" << ChangeToString(tmp->end + 1) << '.' << Node[tmp->end] << ' ' << tmp->weight << '>' << endl;
					totalWeight += tmp->weight;
				}
				tmp = tmp->next;
			}
		}
		return totalWeight;
	}
	if (n >= Node.size())
	{
		ofstream outfile("subGraph1");
		if (!outfile)
		{
			cerr << "subFile create error" << endl;
			return -1;
		}
		for (int i = 0; i < store.verLength(); ++i)
		{
			outfile << '<' << Node[i] << '>' << endl;
		}
		for (int i = 0; i < store.verLength(); ++i)
		{
			adjListGraph<int, double>::edgeNode* tmp = store.ListNode(i).head;
			while (tmp != NULL)
			{
				outfile << '<' << Node[i] << ' ' << Node[tmp->end] << ' ' << tmp->weight << '>' << endl;
				tmp = tmp->next;
			}
		}
		outfile.close();
		return 0;
	}


	//�ռ�׼��
	vector<vector<int>> subGroup;
	int currentGroup = 0;
	vector<int> blank;//����subGroup��һ���ӽ�㼯
	subGroup.push_back(blank);
	bool* isInSubGraph;//�ж��Ƿ��Ѿ�������һ���ӽ�㼯��
	int NodeInSubGraph = 0;
	isInSubGraph = new bool[Node.size()];
	for (int i = 0; i < Node.size(); ++i)
		isInSubGraph[i] = false;


	//�ڽӾ���
	vector<vector<double>> adjMatrix(Node.size(), vector<double>(Node.size()));
	for (int i = 0; i < store.verLength(); ++i)
	{
		adjListGraph<int, double>::edgeNode* tmp = store.ListNode(i).head;
		while (tmp != NULL)
		{
			adjMatrix[i][tmp->end] += tmp->weight;
			tmp = tmp->next;
		}
	}

	//����ͼ

	//������㴦��
	for (int i = 0; i < Node.size(); ++i)
	{
		int sum = 0;
		for (int j = 0; j < Node.size(); ++j)
		{
			if (j != i)
				sum += adjMatrix[i][j] + adjMatrix[j][i];
		}
		if (sum == 0)
		{
			if (subGroup[currentGroup].size() == n)
			{
				currentGroup++;
				subGroup.push_back(blank);
			}
			subGroup[currentGroup].push_back(i);
			++NodeInSubGraph;
			isInSubGraph[i] = true;
		}
	}

	//�ǹ�����㴦��
	while (true)
	{
		//��ʼ��2�����
		double maxWeight = 0;
		int row = 0;
		int column = 0;
		for (int i = 0; i < Node.size(); ++i)
		{
			for (int j = i; j < Node.size(); ++j)
			{
				if (j != i && !isInSubGraph[i] && !isInSubGraph[j])
				{
					if (adjMatrix[i][j] + adjMatrix[j][i] > maxWeight)
					{
						maxWeight = adjMatrix[i][j] + adjMatrix[j][i];
						row = i;
						column = j;
					}
				}
			}
		}
		if (maxWeight == 0)
		{
			if (NodeInSubGraph != Node.size())
			{
				currentGroup++;
				subGroup.push_back(blank);
				for (int i = 0; i < Node.size(); ++i)
				{
					if (!isInSubGraph[i])
					{
						if (subGroup[currentGroup].size() == n)
						{
							currentGroup++;
							subGroup.push_back(blank);
						}
						subGroup[currentGroup].push_back(i);
						++NodeInSubGraph;
						isInSubGraph[i] = true;
					}
				}
			}
			break;
		}
		else
		{
			if (subGroup[currentGroup].size() != 0)
			{
				currentGroup++;
				subGroup.push_back(blank);
			}
			subGroup[currentGroup].push_back(row);
			subGroup[currentGroup].push_back(column);
			NodeInSubGraph += 2;
			isInSubGraph[row] = true;
			isInSubGraph[column] = true;
		}
		//����n�����
		while (subGroup[currentGroup].size() < n)
		{
			double maxW = 0;
			int newNode = -1;
			//�ҹ��������weight

			for (int i = 0; i < Node.size(); ++i)
			{
				if (isInSubGraph[i]) continue;
				else
				{
					int sum = 0;
					for (int j = 0; j < subGroup[currentGroup].size(); ++j)
						sum += adjMatrix[subGroup[currentGroup][j]][i] + adjMatrix[i][subGroup[currentGroup][j]];
					if (maxW < sum)
					{
						maxW = sum;
						newNode = i;
					}
				}
			}

			if (maxW == 0)
				break;
			else
			{
				subGroup[currentGroup].push_back(newNode);
				isInSubGraph[newNode] = true;
				NodeInSubGraph++;
			}
		}
	}
	delete[]isInSubGraph;

	//�����ͼ�ļ�
	double totalWeight = 0;
	for (int i = 0; i < subGroup.size(); ++i)
	{
		++cnt;
		string subFileName = "subGraph";
		subFileName += ChangeToString(cnt);
		ofstream subFile(subFileName);
		if (!subFile)
		{
			cerr << "subFile create error" << endl;
			return -1;
		}

		//������
		for (int j = 0; j < subGroup[i].size(); ++j)
		{
			subFile << '<' << Node[subGroup[i][j]] << '>' << endl;
		}

		//�ڲ������
		for (int j = 0; j < subGroup[i].size(); ++j)
		{
			adjListGraph<int, double>::edgeNode* tmp = store.ListNode(subGroup[i][j]).head;
			while (tmp != NULL)
			{
				for (int k = 0; k < subGroup[i].size(); ++k)
				{
					if (tmp->end == subGroup[i][k])
					{
						subFile << '<' << Node[subGroup[i][j]] << ' ' << Node[tmp->end] << ' ' << tmp->weight << '>' << endl;
						break;
					}
				}
				tmp = tmp->next;
			}
		}

		//���������
		for (int j = 0; j < subGroup[i].size(); ++j)
		{
			adjListGraph<int, double>::edgeNode* tmp = store.ListNode(subGroup[i][j]).head;
			while (tmp != NULL)
			{
				int endNodeInSubGraph = -1;
				int k;
				for (k = 0; k < subGroup[i].size(); ++k)
				{
					if (tmp->end == subGroup[i][k])
						break;
				}
				if (k == subGroup[i].size())
				{
					for (int l = 0; l < subGroup.size(); ++l)
					{
						if (l == i) continue;
						else
						{
							for (int m = 0; m < subGroup[l].size(); ++m)
							{
								if (tmp->end == subGroup[l][m])
								{
									endNodeInSubGraph = l;
									break;
								}
							}
						}
					}
					subFile << '<' << Node[subGroup[i][j]] << ' ' << "subGraph" << ChangeToString(endNodeInSubGraph + 1) << '.' << Node[tmp->end] << ' ' << tmp->weight << '>' << endl;
					totalWeight += tmp->weight;
				}
				tmp = tmp->next;
			}
		}
		subFile.close();
	}
	return totalWeight;
}

//reachNodeΪ��ǰ�ɵ���Ľ�㼯
//nextSeachΪ��������ͼ�󽻻�����ָ���������Ҫ��������ͼ����ʼ��
//initialNodeΪ��ʼ�����
void GraphGenerator::searchOneSubGraph(int NodeNum, string subGraphName, vector<int> &reachNode, vector<searchRoot> &nextSearch, int initialNode)
{
	
	ifstream inFile1(subGraphName);
	if (!inFile1)
	{
		cerr << "open file error" << endl;
		return;
	}

	//��¼��ͼ���ڵĽ��
	vector<int> Node;//����ͼ�ļ��Ľ�㼯
	char ch;
	int cnt = 1;
	reference tmp1, tmp2, tmp3, tmp4;
	while ((ch = inFile1.get()) != EOF)
	{
		if ((ch <= '9' && ch >= '0') || ch == '.')
		{
			if (cnt == 1)
			{
				tmp1.input(ch);
				continue;
			}
			if (cnt == 2)
				break;
		}
		if (ch == '>')
		{
			if (tmp1.length() != 0 && tmp2.length() != 0)
				break;
			if (tmp1.length() != 0)
			{
				int i;
				for (i = 0; i < Node.size(); ++i)
				{
					if (Node[i] == int(tmp1.output()))
						break;
				}
				if (i == Node.size())
					Node.push_back(int(tmp1.output()));
			}
			tmp1.clear();
			tmp2.clear();
			cnt = 1;
			continue;
		}
		else
		{
			if (tmp1.length() != 0)
			{
				if (tmp2.length() != 0)
					cnt = 3;
				else cnt = 2;
			}
		}
	}
	tmp1.clear();
	tmp2.clear();
	inFile1.close();

	//���ڲ��߻�Ϊ�ڽӱ�
	adjListGraph<int, double> store(Node.size(), Node);
	ifstream inFile2(subGraphName);
	if (!inFile2)
	{
		cerr << "open file error" << endl;
		return;
	}
	
	while ((ch = inFile2.get()) != EOF)
	{
		if ((ch <= '9' && ch >= '0') || ch == '.')
		{
			if (cnt == 1)
				tmp1.input(ch);
			if (cnt == 2)
				tmp2.input(ch);
			if (cnt == 3)
				tmp3.input(ch);
			continue;
		}
		if (ch == '>')
		{
			if (cnt >= 3)
				store.insert(int(tmp1.output()), int(tmp2.output()), tmp3.output());
			tmp1.clear();
			tmp2.clear();
			tmp3.clear();
			cnt = 1;
			continue;
		}
		if((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a'))
			break;
		else
		{
			if (tmp1.length() != 0)
			{
				if (tmp2.length() == 0)
					cnt = 2;
				else cnt = 3;
			}
		}
	}
	inFile2.close();

	//��Ӽ�¼�ɵ�����
	vector<int> result;//��¼���
	int order = -1;
	for (int i = 0; i < Node.size(); ++i)
	{
		if (Node[i] == NodeNum)
		{
			order = i;
			break;
		}
	} 
	result = store.dfs(order);
	for (int i = 0; i < result.size(); ++i)
	{
		int j;
		for (j = 0; j < reachNode.size(); ++j)
		{
			if (result[i] == reachNode[j])
				break;
		}
		if (j == reachNode.size())
			reachNode.push_back(result[i]);
	}

	//��¼������Ҫ�����Ľ�����Ӧ��ͼ
	ifstream inFile3(subGraphName);
	if (!inFile3)
	{
		cerr << "open file error" << endl;
		return;
	}

	bool isExternEdge = false;
	while ((ch = inFile3.get()) != EOF)
	{
		if ((ch <= '9' && ch >= '0') || ch == '.')
		{
			if (cnt == 1)
				tmp1.input(ch);
			if (cnt == 2)
			{
				if (!isExternEdge)
					tmp2.input(ch);
				else if (ch != '.')
					tmp2.input(ch);
				else
				{
					cnt = 3;
					continue;
				}
			}
			if (cnt == 3)
				tmp3.input(ch);
			if (cnt == 4)
				tmp4.input(ch);
			continue;
		}
		if (ch == '>')
		{
			if (cnt >= 4)
			{
				//cout << tmp1.output() << " " << tmp2.output() << " " << tmp3.output() << " " << tmp4.output() << " " << endl;
				int i;
				for (i = 0; i < reachNode.size(); ++i)
				{
					if (reachNode[i] == (tmp1.output()))
						break;
				}
				if (i < reachNode.size() || NodeNum == int(tmp1.output()) || initialNode == int(tmp1.output()))
				{
					
					int j;
					for (j = 0; j < reachNode.size(); ++j)
					{
						if (reachNode[j] == int(tmp3.output()))
							break;
					}
					if (j == reachNode.size() && initialNode != int(tmp3.output()) && NodeNum != int(tmp3.output()))
					{
						searchRoot tmp;
						tmp.fileName = "subGraph";
						tmp.fileName += ChangeToString(int(tmp2.output()));
						tmp.StartNodeNum = int(tmp3.output());
						nextSearch.push_back(tmp);
					}
				}
			}
			tmp1.clear();
			tmp2.clear();
			tmp3.clear();
			tmp4.clear();
			isExternEdge = false;
			cnt = 1;
			continue;
		}
		if ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a'))
		{
			isExternEdge = true;
			cnt = 2;
			continue;
		}
		else
		{
			if (tmp1.length() != 0)
			{
				if (tmp2.length() == 0)
					cnt = 2;
				else if (tmp3.length() == 0)
					cnt = 3;
				else if(isExternEdge)
					cnt = 4;
			}
		}
	}
	inFile3.close();
}

//�������ڣ������һ��ֻ��-1��vector
vector<int> GraphGenerator::searchAllSubGraph(int NodeName)
{
	//Ѱ�ҽ���Ƿ�����ͼ�д���
	int currentFileNumber = 0;
	while (true)
	{
		++currentFileNumber;
		string subFileName = "subGraph";
		subFileName += ChangeToString(currentFileNumber);
		ifstream subFile(subFileName);
		if (!subFile)
		{
			cerr << "error: No such node" << endl;
			vector<int> tmp;
			tmp.push_back(-1);
			return tmp;
		}

		//��¼��Ѱ�ҽ��
		vector<int> Node;//����ͼ�ļ��Ľ�㼯
		char ch;
		int cnt = 1;
		reference tmp1, tmp2, tmp3;
		while ((ch = subFile.get()) != EOF)
		{
			if ((ch <= '9' && ch >= '0') || ch == '.')
			{
				if (cnt == 1)
					tmp1.input(ch);
				if (cnt == 2)
					tmp2.input(ch);
				continue;
			}
			if (ch == '>')
			{
				if (tmp1.length() != 0 && tmp2.length() != 0)
					break;
				if (tmp1.length() != 0)
				{
					int i;
					for (i = 0; i < Node.size(); ++i)
					{
						if (Node[i] == int(tmp1.output()))
							break;
					}
					if (i == Node.size())
						Node.push_back(int(tmp1.output()));
				}
				tmp1.clear();
				tmp2.clear();
				cnt = 1;
				continue;
			}
			else
			{
				if (tmp1.length() != 0)
				{
					if (tmp2.length() != 0)
						cnt = 3;
					else cnt = 2;
				}
			}
		}
		subFile.close();
		int i;
		for (i = 0; i < Node.size(); ++i)
		{
			if (NodeName == Node[i])
				break;
		}
		if (i < Node.size())
			break;
	}
	//Ѱ�ҿɵ���Ľ��
	string subFileName = "subGraph";
	subFileName += ChangeToString(currentFileNumber);
	ifstream File(subFileName);
	if (!File)
	{
		cerr << "open file error" << endl;
		vector<int> tmp;
		return tmp;
	}

	vector<int> reachNode;
	vector<searchRoot> nextSearch;
	searchOneSubGraph(NodeName, subFileName, reachNode, nextSearch, NodeName);
	while (nextSearch.size() != 0)
	{
		vector<searchRoot> temp;
		for (int i = 0; i < nextSearch.size(); ++i)
			searchOneSubGraph(nextSearch[i].StartNodeNum, nextSearch[i].fileName, reachNode, temp, NodeName);
		for (int i = 0; i < nextSearch.size(); ++i)//��������벻���ٴ������Ľ�㼯��
		{
			int j;
			for (j = 0; j < reachNode.size(); ++j)
			{
				if (nextSearch[i].StartNodeNum == reachNode[j])
					break;
			}
			if (j == reachNode.size())
				reachNode.push_back(nextSearch[i].StartNodeNum);
		}
		nextSearch.clear();
		for (int i = 0; i < temp.size(); ++i)
		{
			int j;//�ж��Ƿ�������
			for (j = 0; j < reachNode.size(); ++j)
			{
				if (temp[i].StartNodeNum == reachNode[j])
					break;
			}
			if (j == reachNode.size())
			{
				int k;//���ظ�
				for (k = 0; k < nextSearch.size(); ++k)
				{
					if (temp[i].StartNodeNum == nextSearch[k].StartNodeNum)
						break;
				}
				if (k == nextSearch.size())
					nextSearch.push_back(temp[i]);
			}
		}
	}
	return reachNode;

}

//���-1��ʾ�򿪳���
double GraphGenerator::searchFromFirstToSecond(int NodeName1, int NodeName2, vector<int>& firstToSecond, vector<int>& result)
{
	int finded = 0;//�����ҵ�������ͼ�Ľ����Ŀ
	vector<int> NeedSearch;//������ڵ�������ͼ���
	//Ѱ����Ҫ��������ͼ
	int currentFileNumber = 0;
	while (true)
	{
		++currentFileNumber;
		string subFileName = "subGraph";
		subFileName += ChangeToString(currentFileNumber);
		ifstream subFile(subFileName);
		if (!subFile)
		{
			cerr << "open file error" << endl;
			return -1;
		}

		vector<int> Node;//����ͼ�ļ��Ľ�㼯
		char ch;
		int cnt = 1;
		reference tmp1, tmp2, tmp3;
		while ((ch = subFile.get()) != EOF)
		{
			if ((ch <= '9' && ch >= '0') || ch == '.')
			{
				if (cnt == 1)
					tmp1.input(ch);
				if (cnt == 2)
					tmp2.input(ch);
				continue;
			}
			if (ch == '>')
			{
				if (tmp1.length() != 0 && tmp2.length() != 0)
					break;
				if (tmp1.length() != 0)
				{
					int i;
					for (i = 0; i < Node.size(); ++i)
					{
						if (Node[i] == int(tmp1.output()))
							break;
					}
					if (i == Node.size())
						Node.push_back(int(tmp1.output()));
				}
				tmp1.clear();
				tmp2.clear();
				cnt = 1;
				continue;
			}
			else
			{
				if (tmp1.length() != 0)
				{
					if (tmp2.length() != 0)
						cnt = 3;
					else cnt = 2;
				}
			}
		}
		subFile.close();

		for (int i = 0; i < Node.size(); ++i)
		{
			for (int j = 0; j < firstToSecond.size(); ++j)
			{
				if (Node[i] == firstToSecond[j])//�жϿɴ����Ƿ��ڸ���ͼ��
				{
					++finded;
					int k;
					for (k = 0; k < NeedSearch.size(); ++k)
					{
						if (NeedSearch[k] == currentFileNumber)
							break;
					}
					if (k == NeedSearch.size())
						NeedSearch.push_back(currentFileNumber);
					break;
				}
			}
		}
		if (finded == firstToSecond.size())
			break;
	}

	//������ͼ��������Ӧ�������ͼ����
	vector<vector<double>> adjMatrix(firstToSecond.size(), vector<double>(firstToSecond.size()));
	for (int i = 0; i < NeedSearch.size(); ++i)
	{
		string subFileName = "subGraph";
		subFileName += ChangeToString(NeedSearch[i]);
		ifstream subFile(subFileName);
		if (!subFile)
		{
			cerr << "open file error" << endl;
			return -1;
		}
		char ch;
		int cnt = 1;
		reference tmp1, tmp2, tmp3, tmp4;
		bool isExternEdge = false;
		while ((ch = subFile.get()) != EOF)
		{
			if ((ch <= '9' && ch >= '0') || ch == '.')
			{
				if (cnt == 1)
					tmp1.input(ch);
				if (cnt == 2)
				{
					if (!isExternEdge)
						tmp2.input(ch);
					else if (ch != '.')
						tmp2.input(ch);
					else
					{
						cnt = 3;
						continue;
					}
				}
				if (cnt == 3)
					tmp3.input(ch);
				if (cnt == 4)
					tmp4.input(ch);
				continue;
			}
			if (ch == '>')
			{
				if (cnt == 3)
				{
					int j;
					for (j = 0; j < firstToSecond.size(); ++j)
					{
						if (firstToSecond[j] == tmp1.output())
							break;
					}
					int k;
					for (k = 0; k < firstToSecond.size(); ++k)
					{
						if (firstToSecond[k] == tmp2.output())
							break;
					}
					if (j < firstToSecond.size() && k < firstToSecond.size())
					{
						if (adjMatrix[j][k] == 0)
							adjMatrix[j][k] = tmp3.output();
						else if (adjMatrix[j][k] > tmp3.output())
							adjMatrix[j][k] = tmp3.output();
					}
				}
				if (cnt >= 4)
				{
					int j;
					for (j = 0; j < firstToSecond.size(); ++j)
					{
						if (firstToSecond[j] == tmp1.output())
							break;
					}
					int k;
					for (k = 0; k < firstToSecond.size(); ++k)
					{
						if (firstToSecond[k] == tmp3.output())
							break;
					}
					if (j < firstToSecond.size() && k < firstToSecond.size())
					{
						if (adjMatrix[j][k] == 0)
							adjMatrix[j][k] = tmp4.output();
						else if (adjMatrix[j][k] > tmp4.output())
							adjMatrix[j][k] = tmp4.output();
					}
				}
				tmp1.clear();
				tmp2.clear();
				tmp3.clear();
				tmp4.clear();
				isExternEdge = false;
				cnt = 1;
				continue;
			}
			if ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a'))
			{
				isExternEdge = true;
				cnt = 2;
				continue;
			}
			else
			{
				if (tmp1.length() != 0)
				{
					if (tmp2.length() == 0)
						cnt = 2;
					else if (tmp3.length() == 0)
						cnt = 3;
					else if (isExternEdge)
						cnt = 4;
				}
			}
		}
		subFile.close();
	}

	//�����ڽӱ�
	adjListGraph<int, double> minGraph(firstToSecond.size(), firstToSecond);
	for (int i = 0; i < firstToSecond.size(); ++i)
	{
		for (int j = 0; j < firstToSecond.size(); ++j)
		{
			if (adjMatrix[i][j] != 0)
				minGraph.insert(firstToSecond[i], firstToSecond[j], adjMatrix[i][j]);
		}
	}
	double minDistance = minGraph.dijkstra(NodeName1, NodeName2, 100000, result);
	return minDistance;
}

//�ڵ����ʱ����һ������-1��vector
vector<int> GraphGenerator::searchAllSubGraph(int NodeName1, int NodeName2, double& weight)
{
	bool AToB = false, BToA = false;
	weight = -1;
	vector<int> firstToSecond = searchAllSubGraph(NodeName1);
	if (firstToSecond.size() == 1 && firstToSecond[0] == -1)
	{
		cerr << "didn't find node" << endl;
		vector<int> tmp;
		tmp.push_back(-1);
		return tmp;
	}
	vector<int> secondToFirst = searchAllSubGraph(NodeName2);
	if (secondToFirst.size() == 1 && secondToFirst[0] == -1)
	{
		cerr << "didn't find node" << endl;
		vector<int> tmp;
		tmp.push_back(-1);
		return tmp;
	}
	int i;
	for (i = 0; i < firstToSecond.size(); ++i)
	{
		if (firstToSecond[i] == NodeName1)
			break;
	}
	if (i == firstToSecond.size())
		firstToSecond.push_back(NodeName1);
	for (i = 0; i < secondToFirst.size(); ++i)
	{
		if (secondToFirst[i] == NodeName2)
			break;
	}
	if (i == secondToFirst.size())
		secondToFirst.push_back(NodeName2);
	
	for (i = 0; i < firstToSecond.size(); ++i)
	{
		if (firstToSecond[i] == NodeName2)
		{
			AToB = true;
			break;
		}
	}
	for (i = 0; i < secondToFirst.size(); ++i)
	{
		if (secondToFirst[i] == NodeName1)
		{
			BToA = true;
			break;
		}
	}
	//����������޷�����
	if (!AToB && !BToA)
	{
		cerr << "no path" << endl;
		vector<int> tmp;
		tmp.push_back(-1);
		return tmp;
	}

	//�������
	


	if (AToB && BToA)
	{
		vector<int> result1, result2;
		double minDistance1, minDistance2;
		minDistance1 = searchFromFirstToSecond(NodeName1, NodeName2, firstToSecond, result1);
		minDistance2 = searchFromFirstToSecond(NodeName2, NodeName1, secondToFirst, result2);
		if (minDistance1 > minDistance2)
		{
			weight = minDistance2;
			return result2;
		}
		else 
		{
			weight = minDistance1;
			return result1;
		}
	}
	if (AToB && !BToA)
	{
		vector<int> result;
		weight = searchFromFirstToSecond(NodeName1, NodeName2, firstToSecond, result);
		return result;
	}
	if (!AToB && BToA)
	{
		vector<int> result;
		weight = searchFromFirstToSecond(NodeName2, NodeName1, secondToFirst, result);
		return result;
	}
}