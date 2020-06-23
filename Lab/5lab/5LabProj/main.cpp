//����������� ����������
#include <iostream>
//������
#include <string>
//���������� ��� ������ � �������� �����-������ 
//(��� ������ � ������ ������ � �����)
#include <fstream>
//�������
#include <vector>
//��������� ���������� ��� ���������� ����������� ������� � �������� ������� ����
#include <WinSock2.h>

using namespace std;

//����������, ��� ����������� �� ��������� ������, �������� ����� �� ���������
int ultima;

//����� ���������
class Passenger {
public:
	//ID ���������
	int passengerId;
	//������: 0 = �����/ 1 =�� �����
	bool survived;
	//��� ������ ��������� (1 = 1st; 2 = 2nd; 3 = 3rd)
	int pClass;
	//���
	string name;
	//���
	string sex;
	//�������
	int age;
	//����� �������, ������ ��� �������� �� ����� � ��������
	int sibSp;
	//���������� ��������� ��� ����� �� �����
	int parch;
	//����� ������
	string ticket;
	//������������ �����
	int fare;
	//����� ��������
	string cabin;
	//���� �������: (C = Cherbourg; Q = Queenstown; S = Southampton)
	char embarked;
};

//�������, ��� ������ �� ������ ������������ ��������� � ��� �����������
string read(
	//������� ���� ������
	string string, 
	//� �����������
	std::string del) {
	//����� ��������� ��������� ��� ����������, ������ �� ����������� ����������
	int start = ultima;
	//���������� ����� ������ ����� �������� �� ������ �������� �� ��� �����������
	int end = string.find(del, start);
	//�������� ���������, ������� ����� ��������� ��� ���������� 
	ultima = end + del.size();
	//��������� � ���� ������ ������� �����
	return string.substr(start, end - start);
}

int main() {
	//����� ���, ����� ������� ������� ���� ��� ��� ����� ������, ��� � ��� ������
	//��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleCP(1251);
	//��������� ������� �������� win-cp 1251 � ����� ������
	SetConsoleOutputCP(1251);
	//������ ������, ������� ����� ������� ������ ��� ���� ����������
	vector
		//��� �������� ��� ����� Passenger
		<Passenger> 
		passengers;
	//������ ��������� ������, ��������������� ��� ������ ������ �� ����� 
	ifstream fin;
	//���������, ��� �������� ���� � ����� ��� ������
	string pathInput = "0";
	//�������� � �������� �� ������� �����
	do {
		cout << "������� �������� �����, �� �������� ������ ������� ������ (train.csv): ";
		cin >> pathInput;

		//�������� ������� � ������
		fin.open("Sources/" + pathInput);
		//���� �� �����������
		if (!fin.is_open()) {
			cout << "���� �� ��������! ��������� �������." << endl;
			pathInput = "0";
		}
	} while (pathInput == "0");

	//������, ������� ����� ������� � ���� ��� ������ �� ���������
	string strInData;

	//������� �������, ��������� � ������ � ���������� �������, �� ����� �������� ������
	getline(fin, strInData, '\r');

	//�������� ���� ����������
	while (getline(fin, strInData, '\r')) {
		//����������, ��� �������� ������������ ��������
		string readText;
		//������������� ���������� ������ ������ ������� ���������
		ultima = 0;
		//������ ������ ���������� ���������
		Passenger passenger;
		//���� ����
		//���������� �������� ����������
		readText = read(strInData, ",");
		//�������� �� string � int � ���������� ���� ������
		passenger.passengerId = stoi(readText);

		readText = read(strInData, ",");
		passenger.survived = stoi(readText);

		readText = read(strInData, ",\"");
		passenger.pClass = stoi(readText);

		passenger.name = read(strInData, "\",");
		readText = read(strInData, ",");
		if (readText == "male") passenger.sex = "Male";
		else passenger.sex = "Female";

		//����� �
		readText = read(strInData, ",");
		//���� ���� � ��������� �� ������
		if (readText != "") {
			//����� �� ������� string �������������� � double
			passenger.age = stod(readText);
		}
		//���� ���-���� �����, ����� ���������� �������� -1
		else passenger.age = -1;

		//���������� ��������, �������� �� string � int
		readText = read(strInData, ",");
		passenger.sibSp = stoi(readText);

		readText = read(strInData, ",");
		passenger.parch = stoi(readText);

		passenger.ticket = read(strInData, ",");

		readText = read(strInData, ",");
		passenger.fare = stod(readText);

		passenger.cabin = read(strInData, ",");

		//����������� ��������� �������� � ��������� ����� ������ ������ ������
		passenger.embarked = read(strInData, " ")[0];

		//�������� ����� ��������� � ������
		passengers.push_back(passenger);
	}
	//����������, ������� ����� ������� ���������� ���������� �� ����������
	int survivors = 0,
		survivors1 = 0,
		survivors2 = 0,
		survivors3 = 0,
		embarkedC = 0,
		embarkedQ = 0,
		embarkedS = 0,
		totalPerson = 0,
		totalMen = 0,
		totalWomen = 0,
		survivorsWomen = 0,
		survivorsMen = 0;
	//���������� ����� �������� �������, ��� ���������� �������� ��������
	int agePerson = 0, ageMen = 0, ageWomen = 0;
	//������, �������� ������ (������) ����� �� �����
	vector<int> childrenId;

	//������� �� ����� ������ ����������
	for (int i = 0; i < passengers.size(); i++) {
		//���������� ��������� ���-�� ���������� �� ���� ������
		if (passengers[i].embarked == 'S') embarkedS++;
		else if (passengers[i].embarked == 'C') embarkedC++;
		else if (passengers[i].embarked == 'Q') embarkedQ;

		//�������� ������� � �������� � ������ ����� �� 0 �� 18 ���
		if ((passengers[i].age != -1) && (passengers[i].age < 18))
			childrenId.push_back(passengers[i].passengerId);

		//���������� ��������� ���-�� �������� ����������
		if (passengers[i].survived) {
			survivors++;
			//������� ���-�� �������� ���������� �� �������
			if (passengers[i].pClass == 1) survivors1++;
			else if (passengers[i].pClass == 2) survivors2++;
			else if (passengers[i].pClass == 3) survivors3++;
			
			if (passengers[i].age != -1) {
				//������ �������� ������� � ��������� ���������� ���������
				agePerson += passengers[i].age;
				//����������� ���������� ����������
				totalPerson++;

				//������� ���-�� �������� ���������� �� ����
				if (passengers[i].sex == "Female") survivorsWomen++;
				else survivorsMen++;

				//�������� �������� � ��������� ���������� ������
				if (passengers[i].sex == "Female") {
					ageWomen += passengers[i].age;
					totalWomen++;
				}
				//�������� �������� � ��������� ���������� ������ 
				else {
					ageMen += passengers[i].age;
					totalMen++;
				}	
			}
		}
	}

	//������ ��������� ������, ��������������� ��� ������ ������ � ����
	ofstream fout;
	//���������, ��� �������� ���� � ����� ��� ������
	string pathOutput = "0";
	//�������� ���� � �������� �� ����������� �����
	do {
		cout << "������� �������� �����, � ������� ������ �������� ������, ��� ���������� (�� ��������� - '.txt'): ";
		cin >> pathOutput;
		//�������� � ������ ����, ���� ���� ���������� ��� ������ �����
		fout.open("Results/" + pathOutput + ".txt");
		/*//���� ���� �������� � ������������ ���������� ����� (� ����� �����)
		fout.open("Results/" + pathOutput + ".txt", ofstream::app);*/
		//���� �� ���������� �������
		if (!fout.is_open()) {
			//������ ������
			cout << "������ �������� ����� ��� ������" << endl;
			//�������� �������
			pathOutput = "0";
		}
	} while (pathOutput == "0");

	//����� � ���� ���������� �����������
	fout << "����� ����� ��������: " << survivors << endl;
	fout << "����� �������� �� 1 ������: " << survivors1 << endl;
	fout << "����� �������� �� 2 ������: " << survivors2 << endl;
	fout << "����� �������� �� 3 ������: " << survivors3 << endl;
	fout << "���������� �������� ������: " << survivorsWomen << endl;
	fout << "���������� �������� ������: " << survivorsMen << endl;

	//����� � ���� �������� ��������
	if (totalPerson > 0) fout << "������� ������� ���������: " << agePerson / totalPerson << endl; 
	if (totalMen > 0) fout << "������� ������� ������: " << ageMen / totalMen << endl;
	if (totalWomen > 0) fout << "������� ������� ������: " << ageWomen / totalWomen << endl;
	//����� � �����, � ������� ���� ������ ����� ����������
	fout << "����(-�), � ������� ���� ������ ����� ����������: ";

	//��������� ��� ���������
	bool CMore = false, QMore = false, SMore = false;

	//��������� ���������� ��������� � ���������� ��� ���������
	if (embarkedC > embarkedQ) { CMore = true; QMore = false; }
	else if (embarkedC < embarkedQ) { CMore = false; QMore = true; }
	else if (embarkedC == embarkedQ) { CMore = true; QMore = true; }
	
	if (CMore != QMore) {
		if (CMore) {
			if (embarkedC > embarkedS) { CMore = true; SMore = false; }
			else if (embarkedC < embarkedS) { CMore = false; SMore = true; }
			else if (embarkedC == embarkedS) { CMore = true; SMore = true; }
		}

		if (QMore) {
			if (embarkedQ > embarkedS) { QMore = true; SMore = false; }
			else if (embarkedQ < embarkedS) { QMore = false; SMore = true; }
			else if (embarkedQ == embarkedS) { QMore = true; SMore = true; }
		}
	}
	else {
		if (embarkedC > embarkedS) { CMore = true; SMore = false; }
		else if (embarkedC < embarkedS) { CMore = false; SMore = true; }
		else if (embarkedC == embarkedS) { CMore = true; SMore = true; }

		if (embarkedQ > embarkedS) { QMore = true; SMore = false; }
		else if (embarkedQ < embarkedS) { QMore = false; SMore = true; }
		else if (embarkedQ == embarkedS) { QMore = true; SMore = true; }
	}

	//������ �� �������� ������ ���������� �� �����
	if (CMore) {
		fout << "Cherbourg";
		if (QMore || SMore) fout << ", ";
		else fout << endl;
	}
	if (QMore) {
		fout << "Queenstown";
		if (SMore) fout << ", ";
		else fout << endl;
	}
	if (SMore) fout << "Southampton" << endl;

	//� ����� ������ �������������� �����
	fout << "������ ��������������� ������������������ ����������: ";
	for (int it = 0; it < childrenId.size(); it++) {
		if (it != (childrenId.size() - 1)) fout << childrenId[it] << ", ";
		else fout << childrenId[it] << '.' << endl;
	}

	cout << "���������� ���������:" << endl;
	//�������� ���������� ���� ��� ����, ����� ������� ���� � ������������
	fin.close();
	//�������� ���� ���� � ������������
	fin.open("Results/" + pathOutput + ".txt");
	//����� ������� ����� ��� ������ � �������
	string message;
	//��������. ���� �� ����� �����
	while (getline(fin, message, '\r')) {
		//��������� ����� � ���������� message
		getline(fin, message, '\r');
		//������ � � �������
		cout << message << endl;
	}

	//�������� �����, ���������� ������� �������� fout � fin
	//���� ������ ���� ���� ������ ����� ���������� �� ������� ����� � ����
	fout.close();
	fin.close();
}