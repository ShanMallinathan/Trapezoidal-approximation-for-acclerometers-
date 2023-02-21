/**C++ program to read accleration values from csvand compute velocity
and distance using trapezoidal intergration method */

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>

using namespace std;
float sample_time = 0.02; //sampling time given in kaggle website in s

//Csv to vector
vector <vector<double>> csv2vec(string file)
{
	ifstream data(file);

	if (!data.is_open())
	{
		cout << "Cannot open source file";
	}

	vector<vector<double>> accleration; //2D vector for accleration data
	string line; //string to one row of the file

	while (getline(data, line))//read and store every line of the file in line 
	{
		stringstream delimit(line);//stringstream stores the string so as to be used for delimiting
		vector < double> linenum;//double 1d vector
		string value;// store delimited value in value

		while (getline(delimit, value, ','))
		{
			double d = stod(value);//stod string to double conversion
			linenum.push_back(d);
		}

		accleration.push_back(linenum);
	}
	return accleration;
}

//intergration using trapezoidal approximation

vector<double> intergrate(vector<vector<double>> value)
{
	//5Xn vector col 3, 4, 5 holding X, Y and Z values
	vector<double> result(6, 0); //creating 3d vector with 0 initial value
	for (int i = 1; i < value.size(); i++)
	{
		// for X
		
		result[0] = result[0] + (value[i][2] + value[i - 1][2]) * sample_time * 0.5;
		// for Y
		result[1] = result[1] + (value[i][3] + value[i - 1][3]) * sample_time * 0.5;
		// for Z
		result[2] = result[2] + (value[i][4] + value[i - 1][4]) * sample_time * 0.5;
	}
	return result;
}

int main()
{
	string filename = "acc.csv";
	vector<vector<double>> accleration = csv2vec(filename);
	vector<double> velocity = intergrate(accleration);
	int time = accleration.size() * sample_time;
	cout << "\nVx = " << velocity[0];
	cout << "\nVy = " << velocity[1];
	cout << "\nVz = " << velocity[2];
	cout << "\nDx = " << velocity[0] * time;
	cout << "\nDy = " << velocity[1] * time;
	cout << "\nDz = " << velocity[2] * time;
	
}