#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class counter{
public:
	counter(){
		count = 0;
		flag = 0;
		for(int i = 0;i < 20;i++){
			for(int j = 0;j < 10;j++) input[i][j] = 0;
		}
	};
	void com();
	void print();
	void file();
	void read(string in);
	char input[20][10];
	string finput;
	string foutput;
private:
	int length;//the lenth of words
	int count;
	int flag;//check if it is match
	string ans;
	ofstream ofile;//output to txt
};

void counter::com(){
	ans = input[0];
	for (int i = 0; i < length; i++){
		if (ans == input[i]){
			count++;
		}
	}
	ofile << count << endl;
	cout << "count = " << count << endl;
	cout << "total = ";
	for (int i = 0; i < length; i++){
		for (int j = 0; input[i][j] != 0; j++){
			for (int k = 0; k < ans.length(); k++){
				if (input[i][j + k] == ans[k])flag = 1;
				else{
					flag = 0;
					break;
				}
			}
			if (flag == 1){
				cout << i + 1 << " ";
				ofile << i+1;
			}
		}
	}
	ofile.close();
}

void counter::read(string in){
	int word = 0 , j = 0;
	for (int i = 0; i < in.length(); i++){
		if ((int(in[i]) <= 90 && int(in[i]) >= 65) || (int(in[i]) <= 122 && int(in[i]) >= 97)){
			input[word][j] = in[i];
			j++;
		}
		else if (in[i] == ' '){
			word++;
			j = 0;
		}
	}
	length = word + 1;
}

void counter::file(){
	ofile.open(foutput.c_str(), ios::out | ios::trunc);
	count = 0;
	flag = 0;
	for(int i = 0;i < 20;i++){
		for(int j = 0;j < 10;j++) input[i][j] = 0;
	}
}

int main(void){
	counter mycount;
	string in;
	ifstream file;
	cin >> mycount.finput >> mycount.foutput;
	file.open(mycount.finput.c_str(), ifstream::in);
	getline(file,in);
	file.close();
	mycount.file();
	mycount.read(in);
	mycount.com();
	system("pause");
	return 0;
}
