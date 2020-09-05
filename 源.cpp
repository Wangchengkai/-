#include"iostream"
#include"algorithm" 
#include <stdlib.h> 
#include<stdio.h>
#include<time.h>
#include<iomanip>
#include<math.h>
#include <string>
#include <string.h>
#include <vector>
#define random(x) (rand()%x)

using namespace std;


//定义特殊值区
#define bigM 255555
#define minS  1  //最小批量
const double T0 = 10001;
const int maxcase = 1000;
int maxcaseused = -1;

//定义问题值区
#define I  6  //工件种类数量
const int N = I;
const int NN = I;

#define K 10
const int M = 10;//5台机器
//const int d[N + 1] = { 0,5,5,5,5,5 };
//const int d1 = 5, d2 = 5, d3 = 5, d4 = 5, d5 = 5;
//const int d[N + 1] = { 0,3,3,3,3,3 };
//const int d1 = 3, d2 = 3, d3 = 3, d4 = 3, d5 = 3;
//const int d[N + 1] = { 0,4,4,4,4,4 };
//const int d1 = 4, d2 = 4, d3 = 4, d4 = 4, d5 = 4;
const int d[N + 1] = { 0,4,4,4,4,4,4 };
const int d1 = 4, d2 = 4, d3 = 4, d4 = 4, d5 = 4, d6 = 4;

const double processtime[I + 1][K + 1] = {
	{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 0, 26,59,78,88,69, 26,59,78,88,69 },
	{ 0, 38, 62, 90, 54, 30, 38, 62, 90, 54, 30 },
	{ 0,27,44, 64,47,61,27,44, 64,47,61 },
	{ 0,88,10, 49,83,35,88,10, 49,83,35 },
	{ 0,95, 23, 47,84,53, 95, 23, 47,84,53 },
	{ 0, 26,59,78,88,69, 26,59,78,88,69 },
};
int setuptime[I + 1][I + 1][K + 1] = { 0 };
//
//double a1[NN + 1] = { 0,0,500,0,500,500 };
//double b1[NN + 1] = { 0,500,1000,500,1000,1500 };
////均匀分布
//double an[NN + 1] = { 0,0,  500, 0,  500, 500 };
//double bn[NN + 1] = { 0,500,1000,500,1000,1500 };

double a1[NN + 1] = { 0,0,500,0,500,500,0 };
double b1[NN + 1] = { 0,500,1000,500,1000,1500 ,500 };
//均匀分布
double an[NN + 1] = { 0,0,  500, 0,  500, 500 ,0 };
double bn[NN + 1] = { 0,500,1000,500,1000,1500,500 };

//double a1[NN + 1] = { 0,0,0,0,0,0 };
//double b1[NN + 1] = { 0,0.1,0.1,0.1,0.1,0.1 };
////均匀分布
//double an[NN + 1] = { 0,0,  0, 0,  0, 0 };
//double bn[NN + 1] = { 0,0.1,0.1,0.1,0.1,0.1 };


//const int NN = 5;
const int m_s = 1;
const int m_b = M;

//函数列表
void stateergodic();
void label_shixiao(int* jj, int nn);
int label_youxiaoxing(int* jj, int nn);
void new_state_set(int* j, int n, int i, int nn, int dltj);
void statetransition(int* j, int n);
void statetransition_initial(int* j, int n);

double old_label[N + M + 1] = { 0 };
double new_label[N + M + 1] = { 0 };
//double f[d1 + 1][d2 + 1][d3 + 1][d4 + 1][d5 + 1][N + 1][maxcase + 1][m_b - m_s + N + 1];
std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<float>>>>>>>>> f;
void vector_chushihua()
{
	int counti = 0;
	int counti1 = 0;
	f.reserve(d1 + 1);

	for (size_t i = 0; i < d1 + 1; i++)
	{
		std::vector< std::vector  < std::vector < std::vector <std::vector<std::vector<std::vector<std::vector<float>>>>>>>> submatrix;
		submatrix.reserve(d2 + 1);

		for (size_t j = 0; j < d2 + 1; j++)
		{
			std::vector < std::vector   < std::vector <std::vector<std::vector<std::vector<std::vector<float>>>>>>> submatrix1;
			submatrix1.reserve(d3 + 1);

			for (size_t j3 = 0; j3 < d3 + 1; j3++)
			{
				counti++;
				cout << counti << endl;
				std::vector < std::vector <std::vector<std::vector<std::vector<std::vector<float>>>>>> submatrix2;
				submatrix2.reserve(d4 + 1);

				for (size_t j4 = 0; j4 < d4 + 1; j4++)
				{
					counti1++;
					cout << "256per " << counti1 << endl;
					std::vector < std::vector<std::vector<std::vector<std::vector<float>>>>> submatrix3;
					submatrix3.reserve(d5 + 1);

					for (size_t j5 = 0; j5 < d5 + 1; j5++)
					{

						std::vector<std::vector<std::vector<std::vector<float>>>> submatrix4;
						submatrix4.reserve(d6 + 1);

						for (size_t j6 = 0; j6 < d6 + 1; j6++)
						{
							std::vector<std::vector<std::vector<float>>> submatrix5;
							submatrix5.reserve(N + 1);







							for (size_t j11 = 0; j11 < N + 1; j11++)
							{
								std::vector<std::vector<float>> submatrix10;
								submatrix10.reserve(maxcase + 1);

								for (size_t j12 = 0; j12 < maxcase + 1; j12++)
								{
									std::vector<float> row;
									row.resize(m_b - m_s + N + 1);

									submatrix10.push_back(row);
								}
								submatrix5.push_back(submatrix10);
							}




							submatrix4.push_back(submatrix5);

						}
						submatrix3.push_back(submatrix4);

					}
					submatrix2.push_back(submatrix3);

				}
				submatrix1.push_back(submatrix2);

			}
			submatrix.push_back(submatrix1);

		}
		f.push_back(submatrix);


	}

}



void chushihuaf()
{
	//memset(f, 0, sizeof(f));
	int j[N + 1] = { 0 };
	for (j[1] = 0; j[1] <= d1; j[1]++)
		for (j[2] = 0; j[2] <= d2; j[2]++)
			for (j[3] = 0; j[3] <= d3; j[3]++)
				for (j[4] = 0; j[4] <= d4; j[4]++)
					for (j[5] = 0; j[5] <= d5; j[5]++)
						for (j[6] = 0; j[6] <= d6; j[6]++)


								for (int n = 0; n <= N; n++)
									for (int i = 0; i <= maxcase; i++)
										for (int m = 0; m <= m_b - m_s + N; m++)
										{
											f[j[1]][j[2]][j[3]][j[4]][j[5]][j[6]][n][i][m] = 0;
										}




	for (int n = 1; n <= N; n++)f[0][0][0][0][0][0][n][0][m_b - m_s] = T0;


}
void chushihuasettime()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			for (int k = 1; k <= M; k++)
			{
				if (i == j)
				{
					setuptime[i][j][k] = ceil(processtime[i][k] * 0.25);
					//setuptime[0][j][k] = setuptime[i][j][k];//j=0未定义
				}
				else
				{
					setuptime[i][j][k] = ceil((processtime[i][k] + processtime[j][k]) * 0.25);
				}
			}
		}
	}
}


void showdouble(double* a)
{
	cout << "showdouble" << endl;
	for (int i = 0; i < sizeof(a); i++)cout << a[i] << ",";
	cout << endl;
}
void showint(int* a)
{
	cout << "showint" << endl;
	for (int i = 0; i < sizeof(a); i++)cout << a[i] << ",";
	cout << endl;
}

void stateergodic()
{
	int j[N + 1] = { 0 };
	//00000情形下的特殊处理
	for (int n = 1; n <= N; n++)statetransition_initial(j, n);
	for (j[1] = 0; j[1] <= d1; j[1]++)
		for (j[2] = 0; j[2] <= d2; j[2]++)
		{
			for (j[3] = 0; j[3] <= d3; j[3]++)
				for (j[4] = 0; j[4] <= d4; j[4]++)
					for (j[5] = 0; j[5] <= d5; j[5]++)
						for (j[6] = 0; j[6] <= d6; j[6]++)

								for (int n = 1; n <= N; n++)
								{
									int bool1 = 0;
									for (int i = 1; i <= N; i++)bool1 += j[i];
									if (bool1 > 0)
										statetransition(j, n);
									cout << "j1:" << j[1] << " j2: " << j[2] << " j3: " << j[3] << " j4: " << j[4] << " j5: " << j[5] << "nn " << n << " MAXcase " << maxcaseused << endl;// " time0 " << f[j[1]][j[2]][j[3]][j[4]][j[5]][1][0][m_b - m_s] << endl;
								}
			//cout << "j1:" << j[1] << " j2: " << j[2] << " j3: " << j[3]-1 << " j4: " << j[4]-1 << " j5: " << j[5]-1 << " time0 " << f[j[1]][j[2]][j[3]-1][j[4]-1][j[5]-1][0][0][m_b - m_s]<<endl;

		}
	//cout << "ceshi " << endl;
	//for (int i = 0; i <= 30; i++)
	//{
	//	cout << endl;
	//	for (int m = 0; m <= m_b - m_s; m++)
	//		cout << f[0][3][1][0][1][5][i][m] << "   ";

	//}
	//cout << endl;
}

double max1(double a, double b)
{
	if (a <= b)
	{
		a = b;
	}
	return a;
}
double min1(double a, double b)
{
	if (a >= b)
	{
		a = b;
	}
	return a;
}

void label_shixiao(int* jj, int nn)
{
	for (int n = 1; n <= N; n++)
	{
		for (int n1 = 1; n1 <= N; n1++)
		{
			if (n1 != n && new_label[m_b - m_s + n1] > 0 && new_label[m_b - m_s + n] > 0) {
				if (new_label[m_b - m_s + n1] - a1[n1] <= new_label[m_b - m_s + n] - b1[n])
					new_label[m_b - m_s + n] = -bigM;//工件n被判定为不紧要
			}


		}
	}



}

double value_function(double* delta_value)
{
	double out = -1;
	int choose_i = 0;
	if (choose_i == 0)//斜率
	{
		out = 0;
		for (int m = 1; m <= m_b - m_s; m++)out += delta_value[m];
		out = out / (m_b - m_s);
	}
	else if (choose_i == 1)//abel
	{
		out = 0;
		for (int m = 1; m <= m_b - m_s; m++)out += m * delta_value[m];
		out = out / (m_b - m_s);
	}
	else if (choose_i == 2)//累积
	{
		out = 0;
		for (int m = 1; m <= m_b - m_s; m++)out = out * 1.2 + delta_value[m];
		out = out / (m_b - m_s);
	}
	return out;
}

int label_youxiaoxing(int* jj, int nn)//此处输入新情形。*jj为tempj，已经经过了变换
{

	int boolnum = -1;//-1代表无效。
	int i = 0;
	//int ceshi = 900;
	while (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][i][m_b - m_s] != 0 && i <= maxcase)//说明i处存了方案
	{
		i = i + 1;
	}//0到i-1处存了方案


	if (i == 0)//还没有方案
	{
		return 0;
	}
	else if (i >= maxcase)
	{

		double delta[maxcase][M + 1] = { 0 };
		double deltanew[M + 1] = { 0 };
		for (int m = 1; m <= m_b - m_s; m++)
		{
			deltanew[m] = new_label[m] - new_label[m - 1];
		}
		double xielv_new = value_function(deltanew);
		//double xielv_new = value_function_lookup(a,jj,1);


		for (int k = 0; k < i; k++)for (int m = 1; m <= m_b - m_s; m++)
		{
			delta[k][m] = (double)f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][k][m] - (double)f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][k][m - 1];
		}
		double xielv[maxcase] = { 0 };
		for (int k = 0; k < i; k++)xielv[k] = value_function(delta[k]);
		//for (int k = 0; k < i; k++)xielv[k] = value_function_lookup(a,jj,1);

		int replace_num = -1; double tempvalue = bigM;

		tempvalue = bigM;
		for (int kk = 0; kk < i; kk++) {
			if (fabs(xielv[kk] - xielv_new) < tempvalue)
			{
				int bool11 = 0;
				for (int iii = 1; iii <= N; iii++)if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][kk][m_b - m_s + iii] > -bigM / 2 && new_label[m_b - m_s + iii] > -bigM / 2)bool11 = 1;

				if (bool11 == 1) {
					tempvalue = fabs(xielv[replace_num] - xielv_new);
					replace_num = kk;


				}


			}
		}


		if (replace_num != -1)for (int m = 0; m <= m_b - m_s + N; m++)
		{
			if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] < -bigM / 2 || new_label[m] < -bigM / 2)
				f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] = -bigM;
			else if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] < new_label[m])
				f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] = new_label[m];
		}
		else { cout << "???" << endl; }

		//cout << "replacenum: " << replace_num << endl;
		//if (replace_num != -1)for (int m = 0; m <= m_b - m_s + N; m++)f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] = new_label[m];
		boolnum = -1;


	}
	else
	{
		int boolnum1 = 0;//是否被压制
		for (int ii = 0; ii < i; ii++)
		{
			int boolnum11 = 1;//是否被ii压制
			for (int m = 0; m < m_b - m_s; m++)
			{
				if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] < min1(new_label[m] - 0.1, new_label[m + 1] - 0.1 - processtime[nn][m + 1]) && f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m]>-bigM / 2)
				{
					//change
					boolnum11 = 0;//不被压制* *********************************************************** debug
				}
			}
			for (int m = m_b - m_s; m <= m_b - m_s + N; m++)
			{
				if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] < new_label[m] - 0.1 && f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m]>-bigM / 2)
				{
					boolnum11 = 0;//不被压制* *********************************************************** debug
				}
			}
			if (boolnum11 == 1)//被压制
			{
				boolnum1 = 1;
			}
		}


		//cout << "** "<<boolnum1 << endl;
		if (boolnum1 == 0) //不被=制
		{


			int boolnum2 = 1;//是否压制其他label
			for (int ii = 0; ii < i; ii++)
			{
				boolnum2 = 1;
				for (int m = 0; m < m_b - m_s; m++)
				{
					if (min1(f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m], f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m + 1] - processtime[nn][m + 1]) > new_label[m] && new_label[m] > -bigM / 2)
					{
						boolnum2 = 0;
					}
				}
				for (int m = m_b - m_s; m <= m_b - m_s + N; m++)
				{
					if ((f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m]) > new_label[m] && new_label[m] > -bigM / 2)
						//if (f[a][jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][jj[7]][jj[8]][ii][m] > new_label[m] && new_label[m] > -bigM / 2)
					{
						boolnum2 = 0;
					}
				}

				//boolnum2==1:压制ii，，否则不压制。
				if (boolnum2 == 1)//压制
				{
					if (ii != i - 1)
					{
						for (int m = 0; m <= m_b - m_s + N; m++)
						{
							f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] = f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][i - 1][m];
							f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][i - 1][m] = 0;
							//cout << "ok%%%%%%%%%%" << endl;
						}
					}
					else {
						for (int m = 0; m <= m_b - m_s + N; m++)
						{
							f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] = 0;
						}
					}
					ii--;
					i--;
				}
			}
			boolnum = i;
		}
		//end1 = clock();
	}

	//cout << "!!! "<<  boolnum;
	//time2 += (double)(end1 - start1) / CLOCKS_PER_SEC;
	return boolnum;
}

int label_youxiaoxing_include_shixiao(int* jj, int nn)//此处输入新情形。*jj为tempj，已经经过了变换
{

	int boolnum = -1;//-1代表无效。
	int i = 0;
	//int ceshi = 900;
	while (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][i][m_b - m_s] != 0 && i <= maxcase)//说明i处存了方案
	{
		i = i + 1;
	}//0到i-1处存了方案


	if (i == 0)//还没有方案
	{
		return 0;
	}
	else if (i >= maxcase)
	{

		double delta[maxcase][M + 1] = { 0 };
		double deltanew[M + 1] = { 0 };
		for (int m = 1; m <= m_b - m_s; m++)
		{
			deltanew[m] = new_label[m] - new_label[m - 1];
		}
		double xielv_new = value_function(deltanew);
		//double xielv_new = value_function_lookup(a,jj,1);


		for (int k = 0; k < i; k++)for (int m = 1; m <= m_b - m_s; m++)
		{
			delta[k][m] = (double)f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][k][m] - (double)f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][k][m - 1];
		}
		double xielv[maxcase] = { 0 };
		for (int k = 0; k < i; k++)xielv[k] = value_function(delta[k]);
		//for (int k = 0; k < i; k++)xielv[k] = value_function_lookup(a,jj,1);

		int replace_num = -1; double tempvalue = bigM;

		tempvalue = bigM;
		for (int kk = 0; kk < i; kk++) {
			if (fabs(xielv[kk] - xielv_new) < tempvalue)
			{
				tempvalue = fabs(xielv[replace_num] - xielv_new);
				replace_num = kk;
			}
		}
		;

		if (replace_num != -1)for (int m = 0; m <= m_b - m_s + N; m++)
		{
			if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] < -bigM / 2 || new_label[m] < -bigM / 2)
				f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] = -bigM;
			else if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] < new_label[m])
				f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] = new_label[m];
		}
		else { cout << "???" << endl; }

		//cout << "replacenum: " << replace_num << endl;
		//if (replace_num != -1)for (int m = 0; m <= m_b - m_s + N; m++)f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][replace_num][m] = new_label[m];
		boolnum = -1;


	}
	else
	{
		int boolnum1 = 0;//是否被压制
		for (int ii = 0; ii < i; ii++)
		{
			int boolnum11 = 1;//是否被ii压制
			for (int m = 0; m < m_b - m_s; m++)
			{
				if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] < min1(new_label[m] - 0.1, new_label[m + 1] - 0.1 - processtime[nn][m + 1]) && f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m]>-bigM / 2)
				{
					//change
					boolnum11 = 0;//不被压制* *********************************************************** debug
				}
			}
			for (int m = m_b - m_s; m <= m_b - m_s; m++)
			{
				if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] < new_label[m] - 0.1 && f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m]>-bigM / 2)
					boolnum11 = 0;//不被压制* *********************************************************** debug
			}


			for (int m = m_b - m_s + 1; m <= m_b - m_s + N; m++)
			{
				if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] < new_label[m] - 0.1 && f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m]>-bigM / 2)
				{
					int bool1 = 1;
					for (int nnn = 1; nnn <= N; nnn++)if (nnn != m - m_b + m_s)if (f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m_b - m_s + nnn] - a1[nnn] <= f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] - b1[m - m_b + m_s] && f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] > 0 && f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m_b - m_s + nnn] > 0)bool1 = 0;//当前当前工件被认为不重要

					if (bool1 == 1)boolnum11 = 0;//不被压制* *********************************************************** debug
				}
			}
			if (boolnum11 == 1)//被压制
			{
				boolnum1 = 1;
			}
		}


		//cout << "** "<<boolnum1 << endl;
		if (boolnum1 == 0) //不被=制
		{


			int boolnum2 = 1;//是否压制其他label
			for (int ii = 0; ii < i; ii++)
			{
				boolnum2 = 1;
				for (int m = 0; m < m_b - m_s; m++)
				{
					if (min1(f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m], f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m + 1] - processtime[nn][m + 1]) > new_label[m] && new_label[m] > -bigM / 2)
					{
						boolnum2 = 0;
					}
				}
				for (int m = m_b - m_s; m <= m_b - m_s; m++)
				{
					if ((f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m]) > new_label[m] && new_label[m] > -bigM / 2)
					{
						boolnum2 = 0;
					}
				}
				for (int m = m_b - m_s + 1; m <= m_b - m_s + N; m++)
				{
					if ((f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m]) > new_label[m] && new_label[m] > -bigM / 2)
					{
						int bool1 = 1;
						for (int nnn = 1; nnn <= N; nnn++)if (nnn != m - m_b + m_s)if (new_label[m_b - m_s + nnn] - a1[nnn] <= new_label[m] - b1[m - m_b + m_s] && new_label[m] > 0 && new_label[m_b - m_s + nnn] > 0)bool1 = 0;;//当前当前工件被认为不重要

						if (bool1 == 1)boolnum2 = 0;
					}
				}

				//boolnum2==1:压制ii，，否则不压制。
				if (boolnum2 == 1)//压制
				{
					if (ii != i - 1)
					{
						for (int m = 0; m <= m_b - m_s + N; m++)
						{
							f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] = f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][i - 1][m];
							f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][i - 1][m] = 0;
							//cout << "ok%%%%%%%%%%" << endl;
						}
					}
					else {
						for (int m = 0; m <= m_b - m_s + N; m++)
						{
							f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][ii][m] = 0;
						}
					}
					ii--;
					i--;
				}
			}
			boolnum = i;
		}
		//end1 = clock();
	}

	//cout << "!!! "<<  boolnum;
	//time2 += (double)(end1 - start1) / CLOCKS_PER_SEC;
	return boolnum;
}



void new_state_set(int* j, int n, int i, int nn, int dltj)
{
	memset(old_label, 0, sizeof(old_label));
	memset(new_label, 0, sizeof(new_label));
	for (int m1 = 0; m1 <= m_b - m_s + N; m1++)old_label[m1] = f[j[1]][j[2]][j[3]][j[4]][j[5]][j[6]][n][i][m1];
	//cout << "old_label:" << endl;
	//cout << "j1:" << j[1] << " j2: " << j[2] << " j3: " << j[3] << " j4: " << j[4] << " j5: " << j[5] << endl;
	//for (int kk = 0; kk <= m_b - m_s + N; kk++)cout << old_label[kk] << endl;

	new_label[m_b - m_s] = old_label[m_b - m_s] - setuptime[nn][n][m_b] - processtime[n][m_b] * dltj;
	for (int m1 = m_b - m_s - 1; m1 >= 0; m1--)new_label[m1] = (min1(new_label[m1 + 1], old_label[m1])) - setuptime[nn][n][m1 + m_s] - processtime[n][m1 + m_s] * dltj;

	//cout<<dltj<<"  "<< setuptime[nn][n][m1] + processtime[n][m1] * dltj

	//cout << endl;
	//showdouble(old_label);
	//showdouble(new_label);
	// f[j[1]][j[2]][j[3]+dltj][j[4]][j[5]][nn][?][m1]; 加入位置

	/*cout << "new_label-1:" << endl;*/
	//for (int kk = 0; kk <= m_b - m_s + N; kk++)cout << new_label[kk] << endl;

	for (int m1 = m_b - m_s + 1; m1 <= m_b - m_s + N; m1++)new_label[m1] = old_label[m1];

	//cout << "new_label0:" << endl;
	//for (int kk = 0; kk <= m_b - m_s + N; kk++)cout << new_label[kk] << endl;

	if ((j[n] + dltj) == d[n])
	{
		double temp1 = new_label[0]; for (int m = 1; m < m_s; m++)temp1 -= (setuptime[nn][n][m] + processtime[n][m] * dltj);
		new_label[m_b - m_s + n] = temp1;
	}

	//cout << "new_label:" << endl;
	//for (int kk = 0; kk < m_b - m_s + N; kk++)cout << new_label[kk] << endl;

	int jj[N + 1] = { 0 }; for (int n1 = 0; n1 <= N; n1++)jj[n1] = j[n1]; jj[n] += dltj;
	//
	label_shixiao(jj, nn);
	//占优合并
	//int temp = label_youxiaoxing_include_shixiao(jj, nn);//原始情形
	int temp = label_youxiaoxing(jj, nn);//原始情形

	if (temp > maxcaseused) { maxcaseused = temp; }
	if (temp != -1)
	{
		//cout << "SSS" << endl;
		for (int m = 0; m <= m_b - m_s + N; m++)
		{
			f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][temp][m] = new_label[m];
		}
		//if (temp >= 100)showdouble(new_label);
		//if (temp >= 100) {
		//	for (int mm = 0; mm <= 7; mm++)
		//		cout << f[jj[1]][jj[2]][jj[3]][jj[4]][jj[5]][jj[6]][nn][temp][mm] << " ";
		//	cout << endl;
		//}

	}


	if (j[1] == 0 && j[2] == 0 && j[3] == 0 && j[4] == 3 && j[5] == 0 && n == 5 && nn == 3 && dltj == 3)
	{
		cout << "find1111" << endl;
		showdouble(old_label);
		showdouble(new_label);

		cout << setuptime[nn][n][0 + m_s] << endl;
		cout << processtime[n][0 + m_s] << endl;

	}


}


void new_state_go(int* j, int n, int i, int nn, int dltj)
{
	memset(old_label, 0, sizeof(old_label));
	memset(new_label, 0, sizeof(new_label));
	for (int m1 = 0; m1 <= m_b - m_s + N; m1++)old_label[m1] = f[j[1]][j[2]][j[3]][j[4]][j[5]][j[6]][n][i][m1];
	//cout << "old_label:" << endl;
	//cout << "j1:" << j[1] << " j2: " << j[2] << " j3: " << j[3] << " j4: " << j[4] << " j5: " << j[5] << endl;
	//for (int kk = 0; kk <= m_b - m_s + N; kk++)cout << old_label[kk] << endl;

	new_label[m_b - m_s] = old_label[m_b - m_s] - setuptime[nn][n][m_b] - processtime[n][m_b] * dltj;
	for (int m1 = m_b - m_s - 1; m1 >= 0; m1--)new_label[m1] = min1(new_label[m1 + 1], old_label[m1]) - setuptime[nn][n][m1 + m_s] - processtime[n][m1 + m_s] * dltj;
	// f[j[1]][j[2]][j[3]+dltj][j[4]][j[5]][nn][?][m1]; 加入位置

	/*cout << "new_label-1:" << endl;*/
	//for (int kk = 0; kk <= m_b - m_s + N; kk++)cout << new_label[kk] << endl;

	for (int m1 = m_b - m_s + 1; m1 <= m_b - m_s + N; m1++)new_label[m1] = old_label[m1];

	//cout << "new_label0:" << endl;
	//for (int kk = 0; kk <= m_b - m_s + N; kk++)cout << new_label[kk] << endl;

	if ((j[n] + dltj) == d[n])
	{
		double temp1 = new_label[0]; for (int m = 1; m < m_s; m++)temp1 -= (setuptime[nn][n][m] + processtime[n][m] * dltj);
		new_label[m_b - m_s + n] = temp1;
	}


}



void statetransition(int* j, int n)
{
	int lastnum[N + 1] = { 0 };
	for (int n = 1; n <= N; n++)lastnum[n] = d[n] - j[n];


	int i = 0;
	while (f[j[1]][j[2]][j[3]][j[4]][j[5]][j[6]][n][i][m_b - m_s] != 0 && i < maxcase) { i++; }
	//0~ i-1 位置都有label
	for (int ii = 0; ii < i; ii++)
		for (int nn = 0; nn <= N; nn++)
			for (int dltj = 1; dltj <= lastnum[n]; dltj++)
			{
				//在上一个状态的之上加上 一个工件为nn，批量为lastnum的子批
				new_state_set(j, n, ii, nn, dltj);
			}

}

void statetransition_initial(int* j, int n)
{

	int lastnum[N + 1] = { 0 };
	for (int n = 1; n <= N; n++)lastnum[n] = d[n] - j[n];

	//0~ i-1 位置都有label

	double label_all[M + 1];
	for (int nn = 1; nn <= N; nn++)
		for (int dltj = 1; dltj <= lastnum[n]; dltj++)
		{
			memset(new_label, 0, sizeof(new_label));
			memset(label_all, 0, sizeof(label_all));

			label_all[M] = T0 - setuptime[nn][n][M] - processtime[n][M] * dltj;
			for (int m = M - 1; m >= 1; m--)
				label_all[m] = label_all[m + 1] - setuptime[nn][n][m] - processtime[n][m] * dltj;
			for (int m = 0; m <= m_b - m_s; m++)
				new_label[m] = label_all[m + m_s];
			if (dltj == d[n])
			{
				double temp1 = new_label[0];
				for (int m = 1; m < m_s; m++)temp1 -= (setuptime[nn][n][m] + processtime[n][m] * dltj);
				new_label[m_b - m_s + n] = temp1;
			}

			for (int m = 0; m <= m_b - m_s + N; m++)
			{
				f[j[1] + dltj * (n == 1)][j[2] + dltj * (n == 2)][j[3] + dltj * (n == 3)][j[4] + dltj * (n == 4)][j[5] + dltj * (n == 5)][j[6] + dltj * (n == 6)][nn][0][m] = new_label[m];
			}



		}

}

//从标签计算时间
double LAT[maxcase][NN + 1] = { 0 };
double fu_EI[maxcase];
int duqu()
{
	for (int i = 0; i < maxcase; i++)
	{
		for (int n = 0; n <= NN; n++)
		{
			LAT[i][n] = 0;
		}
	}
	for (int i = 0; i < maxcase; i++)
	{
		fu_EI[i] = 0;
	}
	int i = 0;
	while (f[d1][d2][d3][d4][d5][d6][0][i][m_b - m_s] != 0 || f[d1][d2][d3][d4][d5][d6][0][i][m_b - m_s - 1] != 0)
	{
		for (int n = 1; n <= NN; n++)LAT[i][n] = bigM / 2;
		for (int m = m_b + 1; m <= m_b + N; m++)
		{
			if (f[d1][d2][d3][d4][d5][d6][0][i][m - m_s] > -bigM)
				LAT[i][m - m_b] = f[d1][d2][d3][d4][d5][d6][0][i][m - m_s];
		}
		if (NN != N) {
			//fu_EI[i] = -f[1][dd1][dd2][dd3][dd4][dd5][i][M + NN + 1];
		}
		else
		{
			fu_EI[i] = -bigM;
		}
		//showdouble(f[d1][d2][d3][d4][d5][0][i]);

		i++;
	}

	for (int n = 0; n <= NN; n++)cout << LAT[0][n] << endl;


	return i;//一共有i个解。存在0 - i-1上。
}


double U_math_way(int i)//当前处理的标签为第i个标签
{

	//为了适应失效而进行转换
	for (int n = 1; n <= NN; n++)
	{
		if (LAT[i][n] <= -bigM / 2)
		{
			LAT[i][n] = bigM;
		}
	}
	//max(an[n]-lat[n])
	double max_an_LATn = -bigM;
	for (int n = 1; n <= NN; n++)
	{
		max_an_LATn = max1(max_an_LATn, an[n] - LAT[i][n]);
	}
	//	cout << max_an_LATn << " ))) " << fu_EI[i] << endl;

	max_an_LATn = max1(max_an_LATn, fu_EI[i]);//此时max_an_LATn已经包含了 比-EI大 了

											  //max(bn[n]-lat[n])
	double max_bn_LATn = -bigM;
	for (int n = 1; n <= NN; n++)
	{
		max_bn_LATn = max1(max_bn_LATn, bn[n] - LAT[i][n]);
	}
	//J个的排序。
	double b_LAT[NN + 1] = { 0 };
	for (int n = 1; n <= NN; n++)
	{
		b_LAT[n] = bn[n] - LAT[i][n];
	}
	int J[NN + 1] = { 0 };
	for (int n = 1; n <= NN; n++)
	{
		J[n] = n;
	}
	double tempc; int tempJ;
	for (int n = 1; n <= NN; n++)//冒泡法排序
	{
		int stop1 = 1;
		for (int nn = 1; nn <= NN - 1; nn++)
		{
			if (b_LAT[nn] > b_LAT[nn + 1])
			{
				tempc = b_LAT[nn]; b_LAT[nn] = b_LAT[nn + 1]; b_LAT[nn + 1] = tempc;
				tempJ = J[nn]; J[nn] = J[nn + 1]; J[nn + 1] = tempJ;
				stop1 = 0;
			}
		}
		if (stop1) { break; }
	}
	for (int n = 1; n <= NN; n++)
	{
		//	cout << "b-LAT" << n << ":" << b_LAT[n] << "  ";
		//cout << J[n] << endl;
	}

	//此时b_LAT内存放的已经是从小到大的值，而J内存放其工件下标。
	int k = 1;
	while (max_an_LATn > b_LAT[k])
	{
		k++;
	}
	//	cout << "k:" << k << endl;
	//k为第一个大于的值
	int c_j[NN + 1];
	for (int n = 0; n <= NN; n++)
	{
		c_j[n] = 0;
	}
	for (int n = 1; n <= NN - k + 1; n++)
	{
		c_j[n] = J[n + k - 1];//从k到NN结束共NN-k+1个
	}
	b_LAT[0] = max_an_LATn;
	int JJ = NN - k + 1;
	//	cout << "JJ:" << JJ << endl;

	double m[NN + 1][NN + 2]; for (int n = 0; n <= NN; n++) { for (int nn = 0; nn <= NN + 1; nn++) { m[n][nn] = 0; } }
	int line[NN + 1]; for (int nn = 0; nn <= NN; nn++) { line[nn] = 0; }
	int count[NN + 1]; for (int nn = 0; nn <= NN; nn++) { count[nn] = 0; }
	//m的计算
	int tempchachong;
	for (int jj = 0; jj < JJ; jj++)
	{
		for (int ii = 1; ii <= JJ - jj + 1; ii++)
		{

			//从JJ-jj个数中 取 JJ-jj+1-ii个数
			int mm = JJ - jj + 1 - ii, nn = JJ - jj;
			for (int nnn = 0; nnn <= mm; nnn++) { count[nnn] = nnn; }


			while (1)
			{
				for (int nn1 = 0; nn1 <= NN; nn1++) { line[nn1] = 0; }
				for (int l = 1; l <= mm; l++)
				{
					line[l] = count[l];
				}
				tempchachong = 0;
				for (int l = 1; l <= mm - 1; l++)
				{
					if (line[l] >= line[l + 1]) { tempchachong = 1; }
				}
				//对一个取值情形
				if (tempchachong == 0)
				{
					//cout << "jinru" << endl;
					long double temp2 = 1;
					for (int l = JJ - nn + 1; l <= JJ; l++)
					{
						int select = 0;
						for (int ll = 1; ll <= mm; ll++)
						{
							if (line[ll] == JJ - l + 1) { select = 1; }
						}
						if (select)
						{
							//cout << "0;" << temp2 << endl;
							temp2 = temp2 / (bn[c_j[l]] - an[c_j[l]]);
							//cout << bn[c_j[l]] - an[c_j[l]] << endl;
							//cout << "1:" << temp2 << endl;
						}
						else
						{
							temp2 = temp2 * (LAT[i][c_j[l]] - an[c_j[l]]) / (bn[c_j[l]] - an[c_j[l]]);
							//cout << "2:" << temp2 << endl;
						}
						//	cout << "c[j[1]]:" << c_j[l] << endl;
						//	cout << "temp2:" << temp2 << endl;
					}
					m[jj][ii] = m[jj][ii] + temp2;
				}
				if (mm == 0) { break; }
				count[mm]++;
				for (int nnn = mm; nnn >= 2; nnn--)
				{
					if (count[nnn] > nn) {
						count[nnn - 1]++;
						count[nnn] = 1;
					}
				}
				if (count[1] > nn - mm + 1) { break; }
			}
			//cout << "m[" << jj << "][" << ii << "]的计算完成,为： " << m[jj][ii] << endl;
		}
	}
	//cout << "m的全部计算完成" << endl;
	//cout << LAT[i][3] << endl;



	double temp1 = 0;
	for (int jj = 0; jj <= JJ - 1; jj++)
	{
		for (int ii = 1; ii <= JJ + 1 - jj; ii++)
		{
			//cout <<"m" <<m[jj][ii] << endl;
			if (jj == 0)
			{
				temp1 = temp1 + (pow((bn[c_j[jj + 1]] - LAT[i][c_j[jj + 1]]), JJ + 2 - jj - ii) - pow(max_an_LATn, JJ + 2 - jj - ii)) * m[jj][ii] / (JJ + 2 - jj - ii);
			}
			else
			{
				temp1 = temp1 + (pow((bn[c_j[jj + 1]] - LAT[i][c_j[jj + 1]]), JJ + 2 - jj - ii) - pow((bn[c_j[jj]] - LAT[i][c_j[jj]]), JJ + 2 - jj - ii)) * m[jj][ii] / (JJ + 2 - jj - ii);
			}
			//cout << "jj:" << jj << " ii: " << ii << " temp1:" << temp1 << endl;
			//cout << bn[c_j[jj]] - LAT[i][c_j[jj]] << "   " << (bn[c_j[jj + 1]] - LAT[i][c_j[jj + 1]]) << endl;
		}
	}
	double ex = max_bn_LATn - temp1;
	double U_time = ex + T0;
	//cout << "E(x):" << ex << "    U_time:" << U_time << endl;
	return U_time;
}

double label_realtime_U_mathway(double* LAT_time)//当前处理的标签为第i个标签
{

	//为了适应失效而进行转换
	for (int n = 1; n <= NN; n++)
	{
		if (LAT_time[n] <= -bigM / 2)
		{
			LAT_time[n] = bigM;
		}
	}
	//max(an[n]-lat[n])
	double max_an_LATn = -bigM;
	for (int n = 1; n <= NN; n++)
	{
		max_an_LATn = max1(max_an_LATn, an[n] - LAT_time[n]);
	}
	//	cout << max_an_LATn << " ))) " << fu_EI[i] << endl;

	double fu_EI1 = 0;
	if (NN != N) {
		fu_EI1 = -LAT_time[M + NN + 1];
	}
	else
	{
		fu_EI1 = -bigM;
	}
	max_an_LATn = max1(max_an_LATn, fu_EI1);//此时max_an_LATn已经包含了 比-EI大 了

											  //max(bn[n]-lat[n])
	double max_bn_LATn = -bigM;
	for (int n = 1; n <= NN; n++)
	{
		max_bn_LATn = max1(max_bn_LATn, bn[n] - LAT_time[n]);
	}
	//J个的排序。
	double b_LAT[NN + 1] = { 0 };
	for (int n = 1; n <= NN; n++)
	{
		b_LAT[n] = bn[n] - LAT_time[n];
	}
	int J[NN + 1] = { 0 };
	for (int n = 1; n <= NN; n++)
	{
		J[n] = n;
	}
	double tempc; int tempJ;
	for (int n = 1; n <= NN; n++)//冒泡法排序
	{
		int stop1 = 1;
		for (int nn = 1; nn <= NN - 1; nn++)
		{
			if (b_LAT[nn] > b_LAT[nn + 1])
			{
				tempc = b_LAT[nn]; b_LAT[nn] = b_LAT[nn + 1]; b_LAT[nn + 1] = tempc;
				tempJ = J[nn]; J[nn] = J[nn + 1]; J[nn + 1] = tempJ;
				stop1 = 0;
			}
		}
		if (stop1) { break; }
	}
	for (int n = 1; n <= NN; n++)
	{
		//	cout << "b-LAT" << n << ":" << b_LAT[n] << "  ";
		//cout << J[n] << endl;
	}

	//此时b_LAT内存放的已经是从小到大的值，而J内存放其工件下标。
	int k = 1;
	while (max_an_LATn > b_LAT[k])
	{
		k++;
	}
	//	cout << "k:" << k << endl;
	//k为第一个大于的值
	int c_j[NN + 1];
	for (int n = 0; n <= NN; n++)
	{
		c_j[n] = 0;
	}
	for (int n = 1; n <= NN - k + 1; n++)
	{
		c_j[n] = J[n + k - 1];//从k到NN结束共NN-k+1个
	}
	b_LAT[0] = max_an_LATn;
	int JJ = NN - k + 1;
	//	cout << "JJ:" << JJ << endl;

	double m[NN + 1][NN + 2]; for (int n = 0; n <= NN; n++) { for (int nn = 0; nn <= NN + 1; nn++) { m[n][nn] = 0; } }
	int line[NN + 1]; for (int nn = 0; nn <= NN; nn++) { line[nn] = 0; }
	int count[NN + 1]; for (int nn = 0; nn <= NN; nn++) { count[nn] = 0; }
	//m的计算
	int tempchachong;
	for (int jj = 0; jj < JJ; jj++)
	{
		for (int ii = 1; ii <= JJ - jj + 1; ii++)
		{

			//从JJ-jj个数中 取 JJ-jj+1-ii个数
			int mm = JJ - jj + 1 - ii, nn = JJ - jj;
			for (int nnn = 0; nnn <= mm; nnn++) { count[nnn] = nnn; }


			while (1)
			{
				for (int nn1 = 0; nn1 <= NN; nn1++) { line[nn1] = 0; }
				for (int l = 1; l <= mm; l++)
				{
					line[l] = count[l];
				}
				tempchachong = 0;
				for (int l = 1; l <= mm - 1; l++)
				{
					if (line[l] >= line[l + 1]) { tempchachong = 1; }
				}
				//对一个取值情形
				if (tempchachong == 0)
				{
					//cout << "jinru" << endl;
					long double temp2 = 1;
					for (int l = JJ - nn + 1; l <= JJ; l++)
					{
						int select = 0;
						for (int ll = 1; ll <= mm; ll++)
						{
							if (line[ll] == JJ - l + 1) { select = 1; }
						}
						if (select)
						{
							//cout << "0;" << temp2 << endl;
							temp2 = temp2 / (bn[c_j[l]] - an[c_j[l]]);
							//cout << bn[c_j[l]] - an[c_j[l]] << endl;
							//cout << "1:" << temp2 << endl;
						}
						else
						{
							temp2 = temp2 * (LAT_time[c_j[l]] - an[c_j[l]]) / (bn[c_j[l]] - an[c_j[l]]);
							//cout << "2:" << temp2 << endl;
						}
						//	cout << "c[j[1]]:" << c_j[l] << endl;
						//	cout << "temp2:" << temp2 << endl;
					}
					m[jj][ii] = m[jj][ii] + temp2;
				}
				if (mm == 0) { break; }
				count[mm]++;
				for (int nnn = mm; nnn >= 2; nnn--)
				{
					if (count[nnn] > nn) {
						count[nnn - 1]++;
						count[nnn] = 1;
					}
				}
				if (count[1] > nn - mm + 1) { break; }
			}
			//cout << "m[" << jj << "][" << ii << "]的计算完成,为： " << m[jj][ii] << endl;
		}
	}
	//cout << "m的全部计算完成" << endl;
	//cout << LAT_time[3] << endl;



	double temp1 = 0;
	for (int jj = 0; jj <= JJ - 1; jj++)
	{
		for (int ii = 1; ii <= JJ + 1 - jj; ii++)
		{
			//cout <<"m" <<m[jj][ii] << endl;
			if (jj == 0)
			{
				temp1 = temp1 + (pow((bn[c_j[jj + 1]] - LAT_time[c_j[jj + 1]]), JJ + 2 - jj - ii) - pow(max_an_LATn, JJ + 2 - jj - ii)) * m[jj][ii] / (JJ + 2 - jj - ii);
			}
			else
			{
				temp1 = temp1 + (pow((bn[c_j[jj + 1]] - LAT_time[c_j[jj + 1]]), JJ + 2 - jj - ii) - pow((bn[c_j[jj]] - LAT_time[c_j[jj]]), JJ + 2 - jj - ii)) * m[jj][ii] / (JJ + 2 - jj - ii);
			}
			//cout << "jj:" << jj << " ii: " << ii << " temp1:" << temp1 << endl;
			//cout << bn[c_j[jj]] - LAT_time[c_j[jj]] << "   " << (bn[c_j[jj + 1]] - LAT_time[c_j[jj + 1]]) << endl;
		}
	}
	double ex = max_bn_LATn - temp1;
	double U_time = ex + T0;
	//cout << "E(x):" << ex << "    U_time:" << U_time << endl;
	return U_time;
}

//获得子批批量
int seq[50] = { 0 };
int seqsize[50] = { 0 };

double temp_label[M + NN + 2];
void sublot_size(double* ans, double* a1, double* b1)//输入整个标签
{
	double rel[m_b - m_s + N + 1] = { 0 }; for (int m = 0; m <= m_b - m_s + N; m++)rel[m] = ans[m];
	int now1 = 1;
	int lastsize[N + 1] = { 0 }; for (int n = 1; n <= N; n++) { lastsize[n] = d[n]; }
	cout << "lattsize:" << endl;
	showint(lastsize);

	int prevN = 0;
	int endorder = 0; int count1 = 0;
	while (endorder == 0)
	{
		count1++;
		for (int n = 1; n <= N; n++)for (int dltj = 1; dltj <= lastsize[n]; dltj++)
		{
			int oldsize[N + 1] = { 0 }; for (int nn = 1; nn <= N; nn++) { oldsize[nn] = lastsize[nn]; } oldsize[n] -= dltj;
			for (int i = 0; i <= maxcaseused; i++)
			{
				new_state_go(oldsize, n, i, prevN, dltj);

				//cout << "lattsize:" << endl;
				//showint(lastsize);
				//cout << "oldsize:" << endl;
				//showint(oldsize);

				int bool1 = 0;
				/*		cout << "duibi " << endl;
						showdouble(new_label);
						showdouble(rel);*/

				for (int nn = 0; nn <= m_b - m_s; nn++) { if (new_label[nn] != rel[nn])bool1 = 1; }
				if (bool1 == 0)
				{
					cout << "配对成功" << endl;
					seq[now1] = n; seqsize[now1] = dltj;
					for (int m = 0; m <= m_b - m_s + N; m++)rel[m] = old_label[m];
					//rel[m] = f[oldsize[1]][oldsize[2]][oldsize[3]][oldsize[4]][oldsize[5]][n][i][m];
					now1++;
					lastsize[n] -= dltj;
					prevN = n;
					//cout << "now:" << now1 << " seq " << seq[now1 - 1] << " seqsize: " << seqsize[now1 - 1]<<endl;

					//break
					//dltj = d[n];
					//n = N + 1;
					i = maxcase + 1;
					endorder = 1; for (int nn = 1; nn <= N; nn++)if (lastsize[nn] > 0)endorder = 0;
				}

			}


		}
		if (count1 > 50) {
			for (int i = 1; i <= N; i++)if (lastsize[i] > 0) { seq[now1] = i; seqsize[now1] = lastsize[i]; }
			break;
		}
	}



}


double min_label_real_time_U(double* a1, double* b1)
{
	int i = duqu();
	cout << i << endl;
	int counti = -1;
	double temp = bigM;
	for (int ii = 0; ii < i; ii++)
	{
		cout << "ceshi:" << ii << "  " << LAT[ii][1] << "  " << LAT[ii][2] << "  " << LAT[ii][3] << "  " << LAT[ii][4] << "  " << LAT[ii][5] << endl;
	}

	for (int ii = 0; ii < i; ii++)
	{
		double time1 = U_math_way(ii);
		//cout << "标签" << ii << "的实际完工时间为：" << time1 << endl;
		if (time1 < temp) { counti = ii; }
		temp = min1(temp, time1);
	}
	cout << "min real time: " << temp << endl;
	cout << "最小的是第" << counti << "个标签" << endl;
	cout << "过程中最多存储" << maxcaseused + 1 << "个标签" << endl;
	//计算最小的标签的子批批量
	//
	double temp2[M + NN + 2] = { 0 };
	for (int m = 0; m <= m_b - m_s + N; m++) {
		temp2[m] = f[d1][d2][d3][d4][d5][d6][0][counti][m];
	}
	sublot_size(temp2, a1, b1);
	cout << "最优子批批量为：" << endl;
	for (int a = 1; a < 50; a++)
	{
		cout << seq[a] << ",";
	}
	cout << endl;
	for (int a = 1; a < 50; a++)
	{
		cout << seqsize[a] << ",";
	}
	cout << endl;
	return temp;
}


double t[N + 1] = { 0 };

double label_real_time(int i)//给定一个场景;给定标签编号i；
{


	double case_t[N + 1] = { 0,t[1],t[2],t[3],t[4],t[5],t[6]};
	//强制要求，NN+1往后的工件必须是其确定性到达时间。
	for (int n = NN + 1; n <= N; n++)
	{
		case_t[n] = t[n];
	}
	double temp = -bigM;
	for (int n = 1; n <= NN; n++)
	{
		if ((case_t[n] - LAT[i][n]) <= bigM / 2)temp = max1(temp, (case_t[n] - LAT[i][n]));
	}
	temp = max1(temp, fu_EI[i]);
	temp = temp + T0;
	//cout << "new ceshi" << LAT[0][1] << endl;
	//cout << "new ceshi1" <<fu_EI[0] << endl;
	return temp;
}

double min_label_real_time(double* a1, double* b1)
{
	int i = duqu();
	cout << i << endl;

	for (int ii = 0; ii < i; ii++)
	{
		cout << "ceshi:" << ii << "  " << LAT[ii][1] << "  " << LAT[ii][2] << "  " << LAT[ii][3] << "  " << LAT[ii][4] << "  " << LAT[ii][5] << endl;
	}
	int counti = -1;
	double temp = bigM;
	for (int ii = 0; ii < i; ii++)
	{
		cout << "标签" << ii << "的实际完工时间为：" << label_real_time(ii) << endl;
		if (label_real_time(ii) < temp) { counti = ii; }
		temp = min1(temp, label_real_time(ii));
	}
	cout << "min real time: " << temp << endl;
	cout << "最小的是第" << counti << "个标签" << endl;
	cout << "过程中最多存储" << maxcaseused + 1 << "个标签" << endl;
	//计算最小的标签的子批批量
	//
	double temp2[M + NN + 2] = { 0 };
	for (int m = 1; m <= M + NN + 1; m++) {
		temp2[m] = f[d1][d2][d3][d4][d5][d6][0][counti][m];
	}
	sublot_size(temp2, a1, b1);
	cout << "最优子批批量为：" << endl;
	for (int a = 0; a < 50; a++)
	{
		cout << seq[a] << " , ";
	}
	cout << endl;
	for (int a = 0; a < 50; a++)
	{
		cout << seqsize[a] << " , ";
	}
	cout << endl;
	return temp;
}





//验算
double yansuan()//场景下
{
	//seq,seqsize
	double time[50][M + 1] = { 0 };


	double tcase[N + 1] = { 0 };
	for (int n = 1; n <= N; n++)tcase[n] = t[n];
	double tstartbool[N + 1] = { 0 };
	int now1 = 1;
	while (seq[now1] != 0)
	{
		double temp1 = t[seq[now1]]; for (int m = 1; m < m_s; m++)temp1 += setuptime[seq[now1 - 1]][seq[now1]][m] + processtime[seq[now1]][m] * seqsize[now1];
		time[now1][0] = temp1;

		time[now1][m_s] = max1(time[now1 - 1][m_s], temp1) + setuptime[seq[now1 - 1]][seq[now1]][m_s] + processtime[seq[now1]][m_s] * seqsize[now1];
		for (int m = m_s + 1; m <= m_b; m++)time[now1][m] = max1(time[now1 - 1][m], time[now1][m - 1]) + setuptime[seq[now1 - 1]][seq[now1]][m] + processtime[seq[now1]][m] * seqsize[now1];
		cout << time[now1][m_b] << endl;
		cout << "now" << now1 << endl;
		now1++;

	}
	for (int m = m_b + 1; m <= M; m++)time[now1 - 1][m] = time[now1 - 1][m - 1] + setuptime[seq[now1 - 2]][seq[now1 - 1]][m] + processtime[seq[now1 - 1]][m] * seqsize[now1 - 1];

	for (int n = 1; n <= 30; n++)
	{
		cout << endl;
		for (int m = 0; m <= M; m++)
			cout << time[n][m] << " '  ";
	}


	return time[now1 - 1][M];
}

double yansuan1()//场景下
{
	//seq,seqsize
	double time[50][M + 1] = { 0 };
	for (int i = 0; i <= 49; i++)for (int j = 0; j <= M; j++)time[i][j] = T0;



	double tcase[N + 1] = { 0 };
	for (int n = 1; n <= N; n++)tcase[n] = t[n];
	double tstartbool[N + 1] = { 0 };
	int now1 = 49;
	while (seq[now1] == 0)now1--;

	double temp1 = T0; for (int m = M; m > m_b; m--)temp1 -= setuptime[seq[now1 - 1]][seq[now1]][m] + processtime[seq[now1]][m] * seqsize[now1];
	time[now1][M] = temp1;

	time[now1][m_b] = temp1 - setuptime[seq[now1 - 1]][seq[now1]][m_b] - processtime[seq[now1]][m_b] * seqsize[now1];
	for (int m = m_b - 1; m >= m_s; m--)time[now1][m] = time[now1][m + 1] - setuptime[seq[now1 - 1]][seq[now1]][m] - processtime[seq[now1]][m] * seqsize[now1];
	now1--;

	while (now1 > 0)
	{

		time[now1][m_b] = time[now1 + 1][m_b] - setuptime[seq[now1 - 1]][seq[now1]][m_b] - processtime[seq[now1]][m_b] * seqsize[now1];
		for (int m = m_b - 1; m >= m_s; m--)time[now1][m] = min1(time[now1 + 1][m], time[now1][m + 1]) - setuptime[seq[now1 - 1]][seq[now1]][m] - processtime[seq[now1]][m] * seqsize[now1];
		cout << time[now1][m_s] << endl;
		//cout << "now " << now1 << endl;
		now1--;

	}
	for (int m = m_s - 1; m >= 1; m--)time[now1 + 1][m] = time[now1 + 1][m + 1] - setuptime[seq[now1]][seq[now1 + 1]][m] - processtime[seq[now1 + 1]][m] * seqsize[now1 + 1];

	for (int n = 0; n <= 30; n++)
	{
		cout << endl;
		for (int m = 0; m <= M; m++)
			cout << time[n][m] << " '  ";
	}


	return 0;
}


int main()
{
	vector_chushihua();
	chushihuaf();
	chushihuasettime();
	clock_t start1, end1;
	start1 = clock();
	stateergodic();
	cout << maxcaseused << endl;
	
	duqu();

	min_label_real_time_U(a1, b1);
	//min_label_real_time(a1, b1);
	end1 = clock();

	cout << "time use:" << 1000 * (end1 -start1) / (double)CLOCKS_PER_SEC << "ms" << endl;

	yansuan1();
	return 0;
}