#include<iostream>
#include<string>
#include<fstream>
using namespace std;
struct link{
	int node1;
	int node2;
	int length;
	bool linked;
	bool judged;
};
class graph{
public:
	graph(){
		j = 0;
		ans = 0;
		count = 0;
		for(int i = 0;i <= 20;i++) {
			input[i].node1 = 0;
			input[i].node2 = 0;
			input[i].length = 0;
			input[i].linked = false;
			input[i].judged = false;
		}
	};
	void read(string in);
	void judge(int node2);
	void sort();
	void cycle();
	link input[20];
	int ans;
	int count;
private:
	int j;
	int flag;
	int ok;
};

void graph::read(string in){
	int i = 0;
	while(in[i] != ' '){
		input[j].node1 = input[j].node1*10 + in[i] - 48;
		i++;
	}
	i++;
	while(in[i] != ' '){
		input[j].node2 = input[j].node2*10 + in[i] - 48;
		i++;
	}
	i++;
	while(i < in.length()){
		input[j].length = input[j].length*10 + in[i] - 48;
		i++;
	}
	j++;
}

void graph::sort(){
	int tmp;
	for(int w = 0;w < 19;w++){
		for(int i = 0;i < 19;i++){
			if(input[i].length > input[i+1].length && input[i+1].length != 0){
				tmp = input[i].node1;
				input[i].node1 = input[i+1].node1;
				input[i+1].node1 = tmp;
				tmp = input[i].node2;
				input[i].node2 = input[i+1].node2;
				input[i+1].node2 = tmp;
				tmp = input[i].length;
				input[i].length = input[i+1].length;
				input[i+1].length = tmp;
			}
		}
	}
}

void graph::cycle(){
	for(ok = 0;ok <= count;ok++){
		if(input[ok].length != 0){
			flag = 0;
			input[ok].judged = 1;
			//cout << input[ok].node2 << " ";
			judge(input[ok].node2);
			if(flag == 0){
				ans += input[ok].length;
				input[ok].linked = 1;
			}
			input[ok].judged = 0;
		}
	}
}

void graph::judge(int node2){
	for(int i = 0;i < ok && flag == 0;i++){
		if(input[i].node1 == node2 && input[i].judged == 0 && input[i].linked == 1) {
		//	cout << input[ok].node2;
			//system("pause");
			input[i].judged = 1;
			if(input[i].node2 == input[ok].node1) flag = 1;
			else judge(input[i].node2);
			input[i].judged = 0;
		}
		else if(input[i].node2 == node2 && input[i].judged == 0){
			input[i].judged = 1;
			if(input[i].node1 == input[ok].node1) flag = 1;
			else judge(input[i].node1);
			input[i].judged = 0;
		}
	}
}

int main(void){
	graph mygraph;
	string in;
	ifstream file;
	file.open("test.txt", ifstream::in);
	while(getline(file,in)){
		mygraph.read(in);
		mygraph.count++;
	};
	file.close();
	mygraph.sort();
	//cout << mygraph.input[1].node1 << endl;
	mygraph.cycle();
	cout << mygraph.ans << endl;
	//system("pause");
	return 0;
}

