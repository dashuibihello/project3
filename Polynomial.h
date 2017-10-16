#include<iostream>
#include<string>
#include<Windows.h>
#include<map>
#include<cmath>

using namespace std;


class polynomail {
public:
	map<int, double> pol;   //存储指数与系数
	int vaild;				//作为是否返回主菜单的依据
	polynomail (string input);//生产多项式的构造函数
	polynomail(int vai);
	polynomail() {};
	//重载运算符
	bool operator==(const polynomail& poly);
	polynomail& operator=(const polynomail& poly);
	polynomail operator+(const polynomail& poly);
	polynomail operator-(const polynomail& poly);
	polynomail operator*(const polynomail& poly);
	friend ostream& operator<<(ostream& out, const polynomail& poly); //重载输出
};

polynomail input(map<string, polynomail> &goods);                                   //运算常输入界面
polynomail saveinput(map<string, polynomail> &goods);                               //保存多项式的实现函数
polynomail getderivative(const polynomail& poly);                                   //得到导数
ostream& operator<<(ostream& out, const polynomail& poly);                          //重载<<
void maininterface(map<string, polynomail>& goods);                                 //主界面
void welcome();			                                                            //第一次进入主界面的感谢
bool verifyinput(string input);                                                     //判断输入是否合法
void savepol(polynomail pol, map<string, polynomail>& ware);                        //保存多项式的输入界面
bool verifyname(const string &keyName, map<string, polynomail> &goods);             //判断姓名是否存在
bool verifyindex(const int &keyName, map<int, double> &goods);						//判断指数是否存在
void pluspol(map<string, polynomail> &goods);										//加法界面
void subtraction(map<string, polynomail> &goods);			                        //减法界面
void multiplication(map<string, polynomail> &goods);                                //乘法界面
void save(map<string, polynomail> &goods);                                          //保存界面
void evaluate(map<string, polynomail> &goods);                                      //求值界面
void derivative(map<string, polynomail> &goods);                                    //求导界面
void display(map<string, polynomail> &goods);                                       //展示多项式的实现
void ifequal(map<string, polynomail> &goods);										//是否相等界面
void deletepol(map<string, polynomail> &goods);                                     //删除界面



void maininterface(map<string, polynomail> &goods) {
	string command;
	cout << "1.加法运算\n" << "2.减法运算\n" << "3.乘法运算\n" << "4.多项式求导\n" << "5.判断两个多项式是否相等\n" << "6.保存新的多项式\n" 
		<< "7.进行求值\n" << "8.查看已存储的多项式\n" << "9.删除存在的多项式\n" << "10.退出程序" << endl;
	cin >> command;
	system("cls");
	if (command == "1") {
		pluspol(goods);
	}
	else if (command == "2") {
		subtraction(goods);
	}
	else if (command == "3") {
		multiplication(goods);
	}
	else if (command == "4") {
		derivative(goods);
	}
	else if (command == "5") {
		ifequal(goods);
	}
	else if (command == "6") {
		save(goods);
	}
	else if (command == "7") {
		evaluate(goods);
	}
	else if (command == "8") {
		display(goods);
	}
	else if (command == "9") {
		deletepol(goods);
	}
	else if(command == "10") {
		cout << "即将退出程序" << endl;
		exit(0);
	}
	else {
		cout << "输入错误" << endl;
		Sleep(500);
		system("cls");
		maininterface(goods);
	}
}

void welcome() {
	cout << "亲爱的表弟，请不要给你的同学用这个软件噢！" << endl;
}

polynomail input(map<string, polynomail> &goods) {
	string in;
	string input;
	do {
		cout << "1.输入新的多项式\n2.输入已存储的多项式\n3.返回上一步" << endl;
		cin >> in;
		system("cls");
		if (in == "3" || in == "1" || in == "2") {
			break;
		}
		else {
			cout << "输入有误，请重新输入" << endl;
		}		
	} while (1);
	if (in == "1") {
		do {
			cout << "请按（，）（，）....的格式输入，若要返回主界面请输入[backtomaininterface]（不输入中括号）（系数可以输入小数但是不可以输入分数，指数只能输入整数噢！" << endl;
			cin >> input;
			system("cls");
			if (input == "backtomaininterface") {
				polynomail temp(0);
				return temp;
			}
			if (verifyinput(input) == 1) {
				break;
			}
			else {
				cout << "输入错误，请重新输入" << endl;
			}
		} while (1);
		polynomail temp(input);
		return temp;
	}
	else if (in == "2") {
		do {
			cout << "请输入名称，若要返回主界面请输入[backtomaininterface]（不输入中括号）" << endl;
			cin >> input;
			system("cls");
			if (input == "backtomaininterface") {
				polynomail temp(0);
				return temp;
			}
			if (verifyname(input,goods) == true) {
				break;
			}
			else {
				cout << "输入错误，请重新输入" << endl;
			}
		} while (1);
		polynomail temp = goods[input];
		return temp;
	}
	else {
		polynomail back(0);
		return back;
	}
	
}

bool verifyinput(string input) {
	int count1 = 0, count2 = 0,count3 = 0;
	for (size_t a = 0; a < input.size(); a++) {
		if (input[a] == '(') {
			count1++;
		}
		else if (input[a] == ',') {
			count2++;
		}
		else if (input[a] == ')') {
			count3++;
		}
	}
	if (count1 != count3 || count1 !=  count2) {
		return false;
	}
	for (size_t a = 0; a < input.size(); a++) {
		if (input[a] == '(' && input[a+1] != ',') {
			a++;
			if (input[a] == '-') {
				a++;
			}if (input[a] == '(') {
				return false;
			}
			int ifmorepoint = 0;
			for (; a < input.size(); a++) {
				if (input[a] == '.'&&input[a + 1] != ',') {
					a++;
					ifmorepoint++;
				}
				if (ifmorepoint == 2) {
					return false;
				}
				if (input[a] != ','){
					if (input[a] < 48 && input[a]>57) {
						return false;
					}
				}
				else {
					if (input[a + 1] != ',' && input[a + 1] != ')') {
						break;
					}
					else {
						return false;
					}
				}
			}
			a++;
			if (input[a] == '-') {
				a++;
			}
			for (; a < input.size(); a++) {
				if (input[a] != ')') {
					if (input[a] < 48 || input[a]>57) {
						return false;
					}
				}
				else {
					break;
				}
			}
		}
		else {
			return false;
		}
	}
	return true;
}

polynomail::polynomail(string input) {
	vaild = 1;
	int index;
	double coefficient;
	bool ifneg = true;
	
	for (size_t a = 0; a < input.size(); a++) {
		bool ifcoe = true;
		index = 0;
		coefficient = 0;
		if (input[a] == '(') {
			a++;
		}
		if (input[a] == '-') {
			ifneg = false;
			a++;
		}
		for (; input[a] != ','; a++) {
			if (input[a] == '.') {
				ifcoe = false;
				a++;
				break;
			}
			coefficient = coefficient * 10 + input[a] - 48;
		}
		if (ifcoe == false) {
			int count = 1;
			for (; input[a] != ','; a++) {
				coefficient = coefficient + (input[a] - 48) / pow(10, count);
				count++;
			}
		}
		if (ifneg == false) {
			coefficient = -coefficient;
			ifneg = true;
		}
		a++;
		if (input[a] == '-') {
			ifneg = false;
			a++;
		}
		for (; input[a] != ')'; a++) {
			index = index * 10 + input[a] - 48;
		}
		if (ifneg == false) {
			index = -index;
			ifneg = true;
		}
		if (verifyindex(index, pol) == false) {
			pol.insert(pair<int, double>(index, coefficient));
		}
	}
}

polynomail::polynomail(int vai) {
	vaild = vai;
}

ostream& operator<<(ostream& out, polynomail& poly) {
	map<int, double>::iterator it = poly.pol.end();
	it--;
	if (it->second < 0) {
		if (it->first == 0) {
			out << it->second;
		}
		else {
			if (it->second == -1) {
				out << '-';
			}
			else {
				out << it->second;
			}
			if (it->first == 1) {
				out << "x";
			}
			else if (it->first != 0) {
				out << "x^" << it->first;
			}
		}
	}
	else if (it->second == 0) {
		if (poly.pol.size() == 1) {
			out << 0;
		}
	}
	else {
		if (it->second != 1) {
			out << it->second;
		}
		if (it->first == 1) {
			out << "x";
		}
		else if (it->first != 0) {
			out << "x^" << it->first;
		}
	}
	if (it == poly.pol.begin()) {
		if (it->second == 1 && it->first == 0) {
			out << 1;
		}
		return out;
	}
	it--;
	for (; it != poly.pol.begin(); --it) {
		if (it->second < 0) {
			if (it->first == 0) {
				out << it->second;
			}
			else {
				if (it->second == -1) {
					out << '-';
				}
				else {
					out << it->second;
				}
				if (it->first == 1) {
					out << "x";
				}
				else if (it->first != 0){
					out << "x^" << it->first;
				}
			}
		}
		else if (it->second == 0) {
			if (++it == poly.pol.end()) {
				out << 0;
			}
			it--;
		}
		else {
			out << "+";
			if (it->second != 1) {
				out << it->second;
			}
			if (it->first == 1) {
				out << "x";
			}
			else if (it->first != 0){
				out << "x^" << it->first;
			}
		}
	}
		if (it->second < 0) {
			if (it->first == 0) {
				out << it->second;
			}
			else {
				if (it->second == -1) {
					out << '-';
				}
				else {
					out << it->second;
				}
				if (it->first == 1) {
					out << "x";
				}
				else if (it->first != 0) {
					out << "x^" << it->first;
				}
			}
		}
		else if (it->second == 0) {
			if (--it == poly.pol.begin()) {
				out << 0;
			}
			it++;
		}
		else {
			out << "+";
			if (it->second != 1) {
				out << it->second;
			}
			if (it->second == 1 && it->first == 0) {
				out << 1;
			}
			if (it->first == 1) {
				out << "x";
			}
			else if (it->first != 0) {
				out << "x^" << it->first;
			}
		}
	return out;
}

polynomail& polynomail::operator=(const polynomail& poly) {
	pol = poly.pol;
	vaild = poly.vaild;
	return *this;
}

void savepol(polynomail pol, map<string, polynomail>& ware) {
	string name;
	do {
		cout << "请给你的多项式取个名字吧，若要返回主界面请输入[backtomaininterface]" << endl;
		cin >> name;
		system("cls");
		if (name != "backtomaininterface" && verifyname(name,ware) == false) {
			cout << "保存成功！,即将返回主界面" << endl;
			ware.insert(pair<string, polynomail>(name, pol));
			Sleep(500);
			break;
		}
		else if (verifyname(name, ware) == true) {
			cout << "该用户名已存在，请重新输入" << endl;
		}
		else {
			break;
		}
	} while (1);
	system("cls");
	maininterface(ware);
}

bool verifyname(const string &keyName, map<string, polynomail> &goods) {
	return (goods.find(keyName) != goods.end());
}

void save(map<string, polynomail> &goods) {
	polynomail temp = saveinput(goods);
	if (temp.vaild == 0) {
		maininterface(goods);
	}
	else {
		savepol(temp, goods);
	}
}

polynomail saveinput(map<string, polynomail> &goods) {
	string in;
	string input;
	do {
		cout << "1.输入新的多项式\n2.返回上一步" << endl;
		cin >> in;
		system("cls");
		if (in == "1" || in == "2") {
			break;
		}
		else {
			cout << "输入有误，请重新输入" << endl;
		}
	} while (1);
	if (in == "1") {
		do {
			cout << "请按（，）（，）....的格式输入，若要返回主界面请输入[backtomaininterface]（不输入中括号）" << endl;
			cin >> input;
			system("cls");
			if (input == "backtomaininterface") {
				polynomail temp(0);
				return temp;
			}
			if (verifyinput(input) == 1) {
				break;
			}
			else {
				cout << "输入错误，请重新输入" << endl;
			}
		} while (1);
		polynomail temp(input);
		return temp;
	}
	else {
		polynomail back(0);
		return back;
	}

}

void pluspol(map<string, polynomail> &goods) {
	cout << "请输入第一个多项式" << endl;
	polynomail temp1 = input(goods);
	if (temp1.vaild != 0) {
		cout << "请输入第二个多项式" << endl;
		polynomail temp2 = input(goods);
		if (temp2.vaild != 0) {
			polynomail temp = temp1 + temp2;
			cout << "结果如下，若要保存请按1，否则按其他任意键返回主界面（不包括回车）" << endl;
			cout << temp << endl;
			string command;
			cin >> command;
			system("cls");
			if (command == "1") {
				savepol(temp, goods);
			}
		}
	}
	system("cls");
	maininterface(goods);
}

void subtraction(map<string, polynomail> &goods) {
	cout << "请输入第一个多项式" << endl;
	polynomail temp1 = input(goods);
	if (temp1.vaild != 0) {
		cout << "请输入第二个多项式" << endl;
		polynomail temp2 = input(goods);
		if (temp2.vaild != 0) {
			polynomail temp = temp1 - temp2;
			cout << "结果如下，若要保存请按1，否则按其他任意键返回主界面（不包括回车）" << endl;
			cout << temp << endl;
			string command;
			cin >> command;
			system("cls");
			if (command == "1") {
				savepol(temp, goods);
			}
		}
	}
	system("cls");
	maininterface(goods);
}

void multiplication(map<string, polynomail> &goods) {
	cout << "请输入第一个多项式" << endl;
	polynomail temp1 = input(goods);
	if (temp1.vaild != 0) {
		cout << "请输入第二个多项式" << endl;
		polynomail temp2 = input(goods);
		if (temp2.vaild != 0) {
			polynomail temp = temp1 * temp2;
			cout << "结果如下，若要保存请按1，否则按其他任意键返回主界面（不包括回车）" << endl;
			cout << temp << endl;
			string command;
			cin >> command;
			system("cls");
			if (command == "1") {
				savepol(temp, goods);
			}
		}
	}
	system("cls");
	maininterface(goods);
}

void evaluate(map<string, polynomail> &goods) {
	polynomail temp = input(goods);
	if (temp.vaild != 0) {
		string num;
		do {
			cout << "请输入x的值若要返回主界面则输入0" << endl;
			cin >> num;
			system("cls");
			bool legel = true;
			for (size_t a = 0; a < num.size(); a++) {
				if (num[a] == '-') {
					a++;
				}
				if (num[a] < 48 || num[a]>57) {
					legel = false;
					break;
				}
			}
			if (legel == true) {
				break;
			}
			else {
				cout << "输入错误，请重新输入" << endl;
			}
		} while (1);
		double x = 0;
		size_t a = 0;
		if (num[a] == '-') {
			a++;
		}
		for (; a < num.size(); a++) {
			x = num[a] - 48 + x * 10;
		}
		if (num[0] == '-') {
			x = -x;
		}
		if (x != 0) {
			long double answer = 0;
			map<int, double>::iterator it = temp.pol.begin();
			for (; it != temp.pol.end(); ++it) {
				answer += pow(x, it->first)*it->second;
			}
			cout << "多项式答案：" << answer << endl;
			cout << "若要退出则按任意键" << endl;
			cin >> num;
		}
	}
	
	system("cls");
	maininterface(goods);
}

void display(map<string, polynomail> &goods) {
	map<string, polynomail>::iterator it = goods.begin();
	if (goods.size() == 0) {
		cout << "不存在多项式" << endl;
		Sleep(500);
		system("cls");
		maininterface(goods);
	}
	for (; it != goods.end(); ++it) {
		cout << "多项式名称：" << it->first << "\t\t" << "多项式：" <<it->second << endl;
	}
	string temp;
	cout << "输入任意字符返回主界面（不包括回车）" << endl;
	cin >> temp;
	system("cls");
	maininterface(goods);
}

polynomail polynomail::operator+(const polynomail& poly) {
	polynomail temp2 = poly;
	map<int, double>::iterator it = pol.begin();
	for (; it != pol.end(); ++it) {
		if (verifyindex(it->first, temp2.pol) == true) {
			temp2.pol[it->first] += it->second;
		}
		else {
			temp2.pol.insert(pair<int, double>(it->first, it->second));
		}
	}
	return temp2;
}

bool verifyindex(const int &keyName, map<int, double> &goods) {
	return (goods.find(keyName) != goods.end());
}

polynomail polynomail::operator-(const polynomail& poly) {
	polynomail temp2 = poly;
	map<int, double>::iterator it1 = temp2.pol.begin();
	for (; it1 != temp2.pol.end(); it1++) {
		it1->second = -it1->second;
	}
	map<int, double>::iterator it = pol.begin();
	for (; it != pol.end(); ++it) {
		if (verifyindex(it->first, temp2.pol) == true) {
			temp2.pol[it->first] += it->second;
		}
		else {
			temp2.pol.insert(pair<int, double>(it->first, it->second));
		}
	}
	return temp2;
}

polynomail polynomail::operator*(const polynomail& poly) {
	polynomail temp1 = poly;
	polynomail temp(1);
	map<int, double>::iterator it2 = pol.begin();
	for (; it2 != pol.end(); ++it2) {
		polynomail temp2(1);
		map<int, double>::iterator it1 = temp1.pol.begin();
		for (; it1 != temp1.pol.end(); ++it1) {
			int index = it1->first + it2->first;
			double coe = it1->second*it2->second;
			temp2.pol.insert(pair<int, double>(index, coe));
		}
		temp = temp + temp2;
	}
	return temp;
}

void derivative(map<string, polynomail> &goods) {
	polynomail temp = input(goods);
	if (temp.vaild != 0) {
		polynomail der = getderivative(temp);
		cout << "导数为：" << der << endl;
		string command;
		cout << "若要保存请输入1,退出请输入其他任意键（不包括回车）" << endl;
		cin >> command;
		system("cls");
		if (command == "1") {
			savepol(der, goods);
		}
	}
	system("cls");
	maininterface(goods);
}

polynomail getderivative(const polynomail& poly) {
	polynomail temp = poly;
	polynomail der(1);
	map<int, double>::iterator it = temp.pol.begin();
	for (; it != temp.pol.end(); ++it) {
		if (it->first == 0) {
			if (temp.pol.size() == 1) {
				der.pol.insert(pair<int, double>(1, 0));
			}
			continue;
		}
		if (verifyindex(it->first - 1, der.pol) == false) {
			der.pol.insert(pair<int, double>(it->first - 1, it->first*it->second));
		}		
	}
	return der;
}

bool polynomail::operator==(const polynomail& poly) {
	polynomail temp = poly;
	map<int, double>::iterator it1 = temp.pol.begin();
	map<int, double>::iterator it2 = pol.begin();
	if (pol.size() == temp.pol.size()) {
		for (; it2 != pol.end(); it2++) {
			if (it2->first != it1->first || it2->second != it1->second) {
				return false;
			}
			it1++;
		}
	}
	else {
		return false;
	}
	return true;
	
}

void ifequal(map<string, polynomail> &goods) {
	cout << "请输入第一个多项式" << endl;
	polynomail temp1 = input(goods);
	if (temp1.vaild != 0) {
		cout << "请输入第二个多项式" << endl;
		polynomail temp2 = input(goods);
		if (temp2.vaild != 0) {
			if (temp1 == temp2) {
				cout << "相等！" << endl;
			}
			else {
				cout << "不相等！" << endl;
			}
			cout << "输入任意键返回主界面（不包括回车）" << endl;
			string command;
			cin >> command;
		}
	}
	system("cls");
	maininterface(goods);
	
}

void deletepol(map<string, polynomail> &goods) {
	string input;
	do {
		if (goods.size() == 0) {
			break;
		}
		cout << "请输入名称，若要返回主界面请输入[backtomaininterface]（不输入中括号）" << endl;
		cin >> input;
		system("cls");
		if (input == "backtomaininterface") {
			break;
		}
		if (verifyname(input, goods) == true) {
			goods.erase(input);
			cout << "删除成功" << endl;
			break;
		}
		else {
			cout << "输入错误，请重新输入" << endl;
		}
	} while (1);
	Sleep(500);
	system("cls");
	maininterface(goods);
}
