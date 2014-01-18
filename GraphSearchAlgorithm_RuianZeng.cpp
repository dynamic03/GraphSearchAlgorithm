#include<iostream>
#include<fstream>
#include<ostream>
#include<algorithm>
#include<vector>
#include<list>
#include<queue>
/*  in order to test the correctness of algorithm, you'd better try consecutive numbers and starting from 0, and use number only,not char etc.
/* my algorithm is using stack to DFS and use queue to BFS. When using the algorithm, the algorithm of DFS is similar to BFS's, input 
the first list, mark all elements in the list used, then pop one element. If this element has list(means connect to other elements)
and the elements in the list hasn't been used, then push into container, when finishing pushing, pop one. check this one again whether has 
unused elements connecting to it.
So pop and push continuely, until stack or queue is empty, but this doesn't mean the program is over,
if there's other node belonging to other graphs haven't been used, the program still run */

using namespace std;
vector<int> stack;
queue<int> que;
int *flagNode;
int totalNode,totalEdge;
list<int>::iterator Iter;
fstream output;

int findfirstUnused()
{
	int i;
	for(i=0;i<totalNode;i++)
	{
		if(flagNode[i]==0) break;
	}
	return i;
}
void DFS(vector<list<int>> graph)
{
	int v,w;
	bool end;
	int i,count=1;	
	for(i=0;i<totalNode;i++)
		if(flagNode[i]==0) break;
	if(i==totalNode) end=true;
	else end =false;
	while(!end)
	{
		v=findfirstUnused();
		flagNode[v]++;		
		Iter=graph[v].begin();	
		stack.push_back(v);
		while(Iter!=graph[v].end())//when stack is empty, initialize stack
		{
			if(flagNode[*Iter]==0)
			{
				flagNode[*Iter]++;
				stack.push_back(*Iter);			
			}
			Iter++;
		}
		v=stack[stack.size()-1];
		stack.pop_back();
		cout<<"component "<<count<<": ";
		output<<"component "<<count<<": ";
		count++;
		cout<<v<<" ";
		output<<v<<" ";
		while(!stack.empty())
		{

			Iter=graph[v].begin();
			while(Iter!=graph[v].end())
			{
				if(flagNode[*Iter]==0)
				{
					flagNode[*Iter]++;

					stack.push_back(*Iter);
				}
				Iter++;
			}
			v=stack[stack.size()-1];

			stack.pop_back();
			cout<<v<<" ";
			output<<v<<" ";
		}
		cout<<endl;	
		output<<endl;
		for(i=0;i<totalNode;i++)
			if(flagNode[i]==0) break;
		if(i==totalNode) end=true;
		else end =false;
	}
}



void BFS(vector<list<int>> graph)
{

	int v,w;
	bool end;
	int i,count=1;	
	for(i=0;i<totalNode;i++)
		if(flagNode[i]==0) break;
	if(i==totalNode) end=true;
	else end =false;

	while(!end)
	{
		v=findfirstUnused();
		flagNode[v]++;		
		Iter=graph[v].begin();	
		que.push(v);
		while(Iter!=graph[v].end())//when stack is empty, initialize stack
		{
			if(flagNode[*Iter]==0)
			{
				flagNode[*Iter]++;
				que.push(*Iter);			
			}
			Iter++;
		}
		v=que.front();			
		que.pop();
		

		cout<<"component "<<count<<": ";
		output<<"component "<<count<<": ";
		count++;
		cout<<v<<" ";
		output<<v<<" ";
		while(!que.empty())
		{
			v=que.front();
			que.pop();
			Iter=graph[v].begin();
			while(Iter!=graph[v].end())
			{
				if(flagNode[*Iter]==0)
				{
					flagNode[*Iter]++;

					que.push(*Iter);
				}
				Iter++;
			}	
			
			cout<<v<<" ";
			output<<v<<" ";
		}
		cout<<endl;	
		output<<endl;
		for(i=0;i<totalNode;i++)
			if(flagNode[i]==0) break;
		if(i==totalNode) end=true;
		else end =false;
		
	}
	
}
int main()
{
	ifstream input;
	int firstNode,secondNode;
	input.open("infile.dat");
	if(!input) 
		{cout<<"Error.Unable to open the file."<<endl;
	    return 0;
	}
	input>>totalNode>>totalEdge;
	if(input.fail())
	{
   cout<<"Error.Input number only."<<endl;
	    return 0;
	}

	list<int> *edge=new list<int>[totalNode]();
	vector<list<int>> graph;
	int *test=new int[totalNode];
	output.open("outfile.dat",ios_base::out);
	flagNode=new int[totalNode]();
	for(int i=0;i<totalNode;i++) 
		{flagNode[i]=0;//mark every node used

	test[i]=0;
	}

	while(!input.eof())//start creating adjacency list
	{
		input>>firstNode>>secondNode;   
		if(input.fail())
	{
   cout<<"Error.Input number only"<<endl;
	    return 0;
	}
		test[firstNode]++;
		test[secondNode]++;
		if(edge[firstNode].size()==0)
			edge[firstNode].push_back(secondNode);

		else 
		{
			Iter=edge[firstNode].begin();
			while(Iter!=edge[firstNode].end())
			{
				if (*Iter==secondNode) break;
				Iter++;
			}
			if(Iter==edge[firstNode].end()) edge[firstNode].push_back(secondNode);
			else totalEdge--;

		}
		if(edge[secondNode].size()==0)
			edge[secondNode].push_back(firstNode);
		else 
		{
			Iter=edge[secondNode].begin();
			while(Iter!=edge[secondNode].end())
			{
				if (*Iter==firstNode) break;
				Iter++;
			}
			if(Iter==edge[secondNode].end()) edge[secondNode].push_back(firstNode);
			else totalEdge--;
		}


	}
	int k;
	for(k=0;k<totalNode;k++)
		if(test[k]==0) break;
	if(k!=totalNode)//must input consecutive numbers and starting from 0
	{
		cout<<"you'd better try consecutive numbers and starting from 0, and use number only"<<endl;
		return 0;
	}
	for(int i=0;i<totalNode;i++)
		graph.push_back(edge[i]);	//end creating adjacency list
    cout<<"The adjacency list:"<<endl;
	output<<"The adjacency list:"<<endl; 
	for(int i=0;i<graph.size();i++)
	{
		cout<<i<<": ";
		output<<i<<": ";
		Iter=edge[i].begin();
		while(Iter!=edge[i].end())
		{
			cout<<*Iter<<" ";
			output<<*Iter<<" ";
			Iter++;
		}
		cout<<endl;
		output<<endl;

	}
	input.close();
	cout<<endl;
	output<<endl;
	
	

	cout<<"DFS: "<<endl;
	output<<"DFS "<<endl;
	DFS(graph);
	
	flagNode=new int[totalNode]();
	for(int i=0;i<totalNode;i++) flagNode[i]=0;//mark every node used

	cout<<endl;
	output<<endl;
	cout<<"BFS: "<<endl;
	output<<"BFS: "<<endl;
	BFS(graph);
	output.close();
	cout<<endl;
	cout<<"Please check \" outfile.dat \""<<endl;
	return 1;
}

