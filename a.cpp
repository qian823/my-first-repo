#include <iostream>
using namespace std;

int main()
{
	int score = 0;
	cout << "请输入一个考试分数：" << endl;
	cin >> score;
	cout << "您输入的分数为：" << score << endl;
	if(score > 600)
	{
		cout << "恭喜您，考上一本大学！" << endl;
	}
	else if(score > 500)
	{
		cout << "恭喜您，考上二本大学！" << endl;
	}
	else if(score > 400)
	{
		cout << "恭喜您，考上三本大学！" << endl;
	}
	else
	{
		cout << "很遗憾，未考上大学！" << endl;
	}
	
    cout<<"阿斯顿"<<endl;
    system("pause");

	return 0;
}