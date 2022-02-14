#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include "GraphGenerator.h"

using namespace std;

int main()
{
	GraphGenerator a;
	int op;
	string str;
	int num;
	int second;
	double weight;
	vector<int> result;
	while (true)
	{
		cout << "1 - generate a graph file within x-line input(in this file folder)" << endl;
		cout << "2 - add y-line input to refered graph file(in this file folder)" << endl;
		cout << "3 - divide the refered graph file(in this file folder) into several subGraphs" << endl;
		cout << "4 - search the appointed node in  this file folder and find nodes it could reach" << endl;
		cout << "5 - search the appointed two nodes in  this file folder and find the shortest path" << endl;
		cout << "6 - set the range of node's number" << endl;
		cout << "7 - set the range of weight's number" << endl;
		cout << "8 - exit" << endl;
		cout << endl;
		cin >> op;
		
		switch (op)
		{
		case 1:
			cout << "please input the file name" << endl;
			cin >> str;
			cout << "please input the input num" << endl;
			if(!(cin >> num));
			{
				op = 0; 
				cout << "input error" << endl;
				break;
			}
			a.generate(num, str);
			break;

		case 2:
			cout << "please input the file name" << endl;
			cin >> str;
			cout << "please input the add num" << endl;
			if (!(cin >> num))
			{
				op = 0;
				cout << "input error" << endl;
				break;
			}
			a.add(str, num);
			break;

		case 3:
			cout << "please input the file name" << endl;
			cin >> str;
			cout << "please input the max node number" << endl;
			if (!(cin >> num))
			{
				op = 0;
				cout << "input error" << endl;
				break;
			}
			cout << "the weight is "<<a.divideGraph(num, str)<<endl;
			break;
		case 4:
			cout << "please input the node number" << endl;
			if (!(cin >> num))
			{
				op = 0;
				cout << "input error" << endl;
				break;
			}
			result.clear();
			result = a.searchAllSubGraph(num);
			if (result.size() == 1 && result[0] == -1)
				break;
			cout << "through node " << num << " could reach ";
			for (int i = 0; i < result.size(); ++i)
				cout << result[i] << " ";
			cout << endl;
			break;

		case 5:
			cout << "please input the node1 number" << endl;
			if (!(cin >> num))
			{
				op = 0;
				cout << "input error" << endl;
				break;
			}
			cout << "please input the node2 number" << endl;
			if (!(cin >> second))
			{
				op = 0;
				cout << "input error" << endl;
				break;
			}
			result.clear();
			result = a.searchAllSubGraph(num, second, weight);
			if (result.size() == 1 && result[0] == -1)
				break;
			cout << "the min path from " << num <<" to "<< second<< " is ";
			cout << result[0];
			for (int i = 1; i < result.size(); ++i)
				cout << " -> "<<result[i] ;
			cout << endl;
			cout << "the weight is " << weight << endl;
			break;
		case 6:
			cout << "please input the node range" << endl;
			if (!(cin >> num) || num < 0)
			{
				op = 0;
				cout << "input error" << endl;
				break;
			}
			a.setNodeRange(num);
		case 7:
			cout << "please input the weight range" << endl;
			if (!(cin >> num) || num < 0)
			{
				op = 0;
				cout << "input error" << endl;
				break;
			}
			a.setWeightRange(num);
			break;
		}
		if (op >= 8 || op <= 0)
			break;
		cout << endl;
	}
	return 0;
}
