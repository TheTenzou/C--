#include <vector> 
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

//double fitnessNew(Dna, Param);

typedef vector<vector<int>> Dna;
typedef vector<Dna> Population;

struct Param {
	vector<int> efficiency;
	vector<int> resources;
	vector<int> dayInterval;
	vector<int> load;
	int loadTarget;
};

struct sort_pred {
	bool operator()(const std::pair<Dna, double> &left, const std::pair<Dna, double> &right) {
		return left.second < right.second;
	}
};

struct sort_des {
	bool operator()(const std::pair<Dna, double> &left, const std::pair<Dna, double> &right) {
		return left.second > right.second;
	}
};

double tst(double x) {
	return abs(x);
}

//фитнес функци€
double fitnessNew(Dna dna, Param param) {
	int eff = 0;
	int res = 0;

	int dayDelta = 0;
	int dayCount = 0;

	int test = 1;

	vector<double> interval(param.dayInterval.size(), 0);
	int intervalCount = 0;
	vector<double> tmpV(param.dayInterval.size(), -1);

	for (int i = 0; i < dna.size(); ++i) {
		int tmpDayL = 0;
		for (int j = 0; j < dna[i].size(); ++j) {
			eff += param.efficiency[j] * dna[i][j];
			res += param.resources[j] * dna[i][j];
			tmpDayL += dna[i][j] * param.load[j];
			if (dna[i][j]) {

				if (tmpV[j] == -1) {
					tmpV[j] = 0;
				}
				else {
					//interval[i] = abs(param.dayInterval[i] - tmpV[i]);
					if (tmpV[j] == 0)
					{
						tmpV[j] += 0.1;
					}
					interval[j] += (pow(param.dayInterval[j]/tmpV[j],2) + pow(tmpV[j]/param.dayInterval[j],2))/2;
					++intervalCount;
					tmpV[j] = 0;
					//cout << "i = " << i << " j = " << j << " | " << pow(2, -pow(((param.dayInterval[i] - tmpV[i]) / (param.dayInterval[i] * 0.25)), 2)) << ' ' << endl;
				}
				
			}
			++tmpV[j];
		}
		//cout << endl;
		++dayCount;
		dayDelta += abs(param.loadTarget - tmpDayL);
		//cout << tmpDayL << endl;
		if (param.loadTarget < tmpDayL) {
			test = 0;
		}
	}
	double dayIntervalDelta = 0;
	for (int i = 0; i < interval.size(); ++i) {
		dayIntervalDelta += interval[i] /*/ param.dayInterval[i]*/;
	}
	double avgDayDelta = (double)dayDelta / dayCount;
	double avgIntervalDelta = dayIntervalDelta / interval.size();

	//double fit = eff / (res * (1 + avgDayDelta) * (1 + avgIntervalDelta));
	//double fit = eff / (res * (1 + avgDayDelta)*avgIntervalDelta);
	double fit = test * eff / (res *avgIntervalDelta);
	//cout << avgIntervalDelta << endl;

	return fit;
}

Dna propotionalSampling(Population population, Param param) {

	vector<pair<Dna, double>> tmpV;

	for (int i = 0; i < population.size(); ++i) {
		tmpV.push_back(make_pair(population[i], fitnessNew(population[i], param)));
	}

	double sum = 0;
	for (int i = 0; i < tmpV.size(); ++i) {
		sum += tmpV[i].second;
	}

	vector<double> tmp;
	for (int i = 0; i < tmpV.size(); ++i) {
		tmp.push_back(tmpV[i].second / sum);
	}

	/*cout << "=========================" << endl;

	for (int i = 0; i < a.size(); ++i) {
		cout << a[i].second << " | " << tmp[i] << endl;
	}*/

	sort(tmpV.begin(), tmpV.end(), sort_pred());
	sort(tmp.begin(), tmp.end());

	/*cout << "=========================" << endl;

	for (int i = 0; i < a.size(); ++i) {
		cout << a[i].second << " | " << tmp[i] << endl;
	}*/

	vector<double> csum;
	csum.resize(population.size());
	csum[0] = tmp[0];
	for (int i = 1; i < csum.size(); ++i) {
		csum[i] = csum[i - 1] + tmp[i];
	}

	/*cout << "=========================" << endl;

	for (int i = 0; i < a.size(); ++i) {
		cout << a[i].second << " | " << tmp[i] << " | " << csum[i] << endl;
	}

	cout << "=========================" << endl;*/

	double r = (double)rand() / RAND_MAX;

	Dna result;

	for (int i = 0; i < csum.size(); ++i) {
		if (r <= csum[i]) {
			result = tmpV[i].first;
			break;
		}
	}
	return result;
}

Dna backwardPropotionalSampling(Population population, Param param) {

	vector<pair<Dna, double>> tmpV;

	for (int i = 0; i < population.size(); ++i) {
		tmpV.push_back(make_pair(population[i], fitnessNew(population[i], param)));
	}

	double sum = 0;
	double max = 0;
	for (int i = 0; i < tmpV.size(); ++i) {
		if (tmpV[i].second > max) {
			max = tmpV[i].second;
		}
	}

	for (int i = 0; i < tmpV.size(); ++i) {
		sum += max - tmpV[i].second;
	}

	vector<double> tmp;
	for (int i = 0; i < tmpV.size(); ++i) {
		tmp.push_back((max - tmpV[i].second) / sum);
	}

	sort(tmpV.begin(), tmpV.end(), sort_des());
	sort(tmp.begin(), tmp.end());

	vector<double> csum;
	csum.resize(population.size());
	csum[0] = tmp[0];
	for (int i = 1; i < csum.size(); ++i) {
		csum[i] = csum[i - 1] + tmp[i];
	}

	double r = (double)rand() / RAND_MAX;
	//cout << r << endl;
	Dna result;

	for (int i = 0; i < csum.size(); ++i) {
		if (r <= csum[i]) {
			result = tmpV[i].first;
			break;
		}
	}
	if (!result.size()) {
		return tmpV[0].first;
	}
	return result;
}

Dna randomSampling(Population population) {
	int index = rand() % population.size();
	return population[index];
}

int fitness(vector<int> efficiency, Dna dna) {
	int res = 0;
	for (int i = 0; i < dna.size(); ++i) {
		for (int j = 0; j < dna[i].size(); ++j) {
			res += efficiency[j] * dna[i][j];
		}
	}
	return res;
}

//затрачиваемые ресурсы
int resources(vector<int> resources, Dna dna) {
	int res = 0;
	for (int i = 0; i < dna.size(); ++i) {
		for (int j = 0; j < dna[i].size(); ++j) {
			res += resources[j] * dna[i][j];
		}
	}
	return res;
}

//максимально загруженный день
int maxLoadDay(vector<int> load, Dna dna) {
	int result = 0;
	for (int i = 0; i < dna.size(); ++i) {
		int tmp = 0;
		for (int j = 0; j < dna[i].size(); ++j) {
			tmp += load[j] * dna[i][j];
		}
		if (tmp > result) {
			result = tmp;
		}
	}
	return result;
}

int timeIterval(vector<int> dayInterval, Dna dna) {
	if (!dna.size()) {
		return 0;
	}
	int works = dna[0].size();
	int days = dna.size();
	for (int i = 0; i < works; ++i) {
		int tmp = 0;
		for (int j = 0; j < days; ++j) {
			if (!dna[j][i]) {
				tmp++;
			}
			else {
				if (tmp < dayInterval[i]) {
					//return 0;
					return 1;
				}
				tmp = 0;
			}
		}
	}
	return 1;
}






// создание случайной днк
Dna initDna(int days, int works, vector<int> load, int loadTarget, vector<int> dayInterval) {
	Dna dna(days, vector<int>(works));
	for (int i = 0; i < dna.size(); ++i) {
		for (int j = 0; j < dna[i].size(); ++j) {
			dna[i][j] = (rand() % 100) < 10;
		}
	}
	return dna;
	/*vector<int> tmpV(dayInterval.size(), 360);
	Dna dna(days, vector<int>(works));
	for (int i = 0; i < dna.size(); ++i) {
		int tmp = 0;
		for (int j = 0; j < dna[i].size(); ++j) {
			if ((tmp + load[j] < loadTarget) && (tmpV[j] > dayInterval[j])) {
				dna[i][j] = (rand() % 100) < 70;
				if (dna[i][j]) {
					tmp += dna[i][j] * load[j];
					tmpV[j] = 0;
				}
			}
			else {
				++tmpV[j];
			}
		}
	}
	return dna;*/
}

// создание изначальной попул€ции
Population initPopulation(int populationSize, int days, int works, vector<int> load, int loadTarget, vector<int> dayInterval) {
	Population population;
	population.resize(populationSize);

	for (int i = 0; i < population.size(); ++i) {
		population[i] = initDna(days, works, load, loadTarget, dayInterval);
	}
	return population;
}

// скрешивание
Dna crosingover(Dna dna1, Dna dna2) {
	Dna newDna = dna1;
	int parts = 3;
	int currentPart = 1;
	/*
	int index = 0;
	for (; currentPart < parts;) {

		for (; index < newDna.size()*currentPart / 3; ++index) {
			newDna[index] = dna1[index];
		}
		currentPart++;

		for (; index < newDna.size()*currentPart / 3; ++index) {
			newDna[index] = dna2[index];
		}
		currentPart++;
	}*/
	// old selection
	for (int i = (rand() % newDna.size()); i < newDna.size(); ++i) {
		newDna[i] = dna2[i];
	}
	return newDna;
}

//мутации
Dna mutation(Dna dna) {
	for (int i = 0; i < dna.size(); ++i) {
		for (int j = 0; j < dna[i].size(); ++j) {
			if ((rand() % 100) < 10) {
				dna[i][j] = (dna[i][j] == 0);
			}
		}
	}
	return dna;
}

Dna decriseResources(Dna dna) {
	for (int i = 0; i < dna.size(); ++i) {
		for (int j = 0; j < dna[i].size(); ++j) {
			if (dna[i][j]) {
				if ((rand() % 100) < 20) {
					dna[i][j] = 0;
				}
			}
		}
	}
	return dna;
}

Dna addOnes(Dna dna) {
	for (int i = 0; i < dna.size(); ++i) {
		for (int j = 0; j < dna[i].size(); ++j) {
			if (!dna[i][j]) {
				if ((rand() % 100) < 2) {
					dna[i][j] = 1;
				}
			}
		}
	}
	return dna;
}

Dna mixUpDays(Dna dna) {
	int days = dna.size();
	int countOfMixUpDays = days * 0.3;
	for (int i = 0; i < countOfMixUpDays; ++i) {
		iter_swap(dna.begin() + (rand() % days), dna.begin() + (rand() % days));
	}
	return dna;
}

Population addRondom(Population population, int populationSize, int days, int works, vector<int> eff, vector<int> load, int loadTarget, vector<int> dayInterval) {
	while (population.size() < populationSize) {
		Dna tmp = initDna(days, works, load, loadTarget, dayInterval);
		population.push_back(tmp);
	}
	return population;
}

Population selection(Population population, double proportionOfSelection, Param param) {
	int newDnaCount = population.size() * proportionOfSelection; // оличество новых особей

	Population newPopulation = population;

	for (int i = 0; i < newDnaCount; ++i) {
		Dna tmp = crosingover(propotionalSampling(population, param), propotionalSampling(population, param));
		//newPopulation.push_back(make_pair(tmp, fitness(eff, tmp)));
		newPopulation.push_back(tmp);
	}
	return newPopulation;
}

Population generationMutation(Population population, double proportionOfMutation) {
	int mutatedDnaCount = population.size() * proportionOfMutation;

	Population newPopulation = population;

	for (int i = 0; i < mutatedDnaCount; ++i) {
		Dna tmp = mutation(randomSampling(population));
		//newPopulation.push_back(make_pair(tmp, fitness(eff, tmp)));
		newPopulation.push_back(tmp);
	}
	return newPopulation;
}

Population mutateMixDays(Population population, vector<int> dayInterval) {
	for (int i = 0; i < population.size(); ++i) {
		
			population[i] = mixUpDays(population[i]);
		
	}
	return population;
}

Population removeExtra(Population population, int populationSize, Param param) {
	while (population.size() > populationSize) {
		Dna tmp = backwardPropotionalSampling(population, param);
		if (tmp.size() != 0) {
			//population.erase(find(population.begin(), population.end(), make_pair(tmp, fitness(eff, tmp))));

			population.erase(find(population.begin(), population.end(), tmp));
		}
	}
	return population;
}

Dna findMostFited(Population population, Param param) {
	double max = 0;
	int index = 0;
	for (int i = 0; i < population.size(); ++i) {
		double tmp = fitnessNew(population[i], param);
		if ( tmp > max) {
			max = tmp;
			index = i;
		}
	}
	/*if (index) {
		return population[index].first;
	}
	else {
		return Dna();
	}*/
	return population[index];
}


Dna solve(vector<int> load, int loadTarget, vector<int> resources, vector<int> efficiency, vector<int> dayInterval,
	int days, int works, double proportionOfSelection, double proportionOfMutation) {

	Param param;
	param.dayInterval = dayInterval;
	param.efficiency = efficiency;
	param.load = load;
	param.loadTarget = loadTarget;
	param.resources = resources;

	srand(time(0));
	int populationSize = 20; // попул€ци€

	// ќценка попул€ции
	Population population = initPopulation(populationSize, days, works, load, loadTarget, dayInterval);

	Dna mostFited = findMostFited(population, param);
	int maxGeneration = 20;
	int currentGeneraion = 0;
	while (currentGeneraion < maxGeneration) {

		if (population.size() > populationSize) {
			population = removeExtra(population, populationSize, param);
		}
		else if (population.size() < populationSize) {
			population = addRondom(population, populationSize, days, works, efficiency, load, loadTarget, dayInterval);
		}

		population = selection(population, proportionOfSelection, param);

		population = generationMutation(population, proportionOfMutation);


		mostFited = findMostFited(population, param);

		currentGeneraion++;
		cout << "Generaton: " << currentGeneraion << " Efficiency: " << fitnessNew(mostFited, param) << " Size: " << population.size() << endl;
	}

	//cout << "size " << mostFitedV.size() << endl;

	/*int max = 0;
	int index = 0;
	for (int i = 0; i < mostFitedV.size(); ++i) {
		//cout <<
		if (mostFitedV[i].second > max) {
			max = mostFitedV[i].second;
			index = i;
		}
	}
	//cout << "index " << index << endl;
	//cout << "most fit " << mostFitedV[index].first.size() << endl;
	return mostFitedV[index].first;*/
	return mostFited;
}

int main() {
	vector<int> dif = { 1, 1, 1, 2, 2, 3, 3, 3, 2, 1, 2, 1, 2, 2, 2, 2, 1, 2 };
	vector<int> len = { 1, 1, 1, 2, 3, 4, 5, 2, 2, 1, 3, 1, 2, 2, 3, 3, 2, 4 };
	vector<int> res = { 1, 1, 1, 2, 1, 2, 4, 3, 2, 1, 2, 1, 3, 2, 3, 3, 2, 5 };
	vector<int> eff = { 2, 2, 2, 1, 3, 4, 5, 6, 1, 2, 3, 4, 2, 1, 2, 3, 1, 5 };
	vector<int> ti(18, 3);

	//cout << "size ti " << ti.size() << ' ' << ti[0] << endl;

	//Dna ans = solve(dif, len, 8, res, 100, eff, 160, ti, 5, 18, 0.2, 0.2);
	Dna ans = solve(len, 16, res, eff, ti, 90, 18, 0.7, 0.7);

	/*s
	for (int i = 0; i < ans.size(); ++i) {
		for (int j = 0; j < ans[i].size(); ++j) {
			cout << ans[i][j] << ' ';
		}
		cout << endl;
	}
	*/
	setlocale(LC_ALL, "rus");
	cout << endl << "ћакимальна€ продолдительность за день: " << maxLoadDay(len, ans) << endl;
	cout << "—уммарные ресурсы за весь промежуток: " << resources(res, ans) << endl;
	cout << "—умарна€ эффективность за весь промежуток: " << fitness(eff, ans) << endl;

	ofstream file;
	file.open("answer.txt");
	for (int i = 0; i < ans[0].size(); ++i) {
		for (int j = 0; j < ans.size(); ++j) {
			file << ans[j][i] << '	';
		}
		file << endl;
	}

	system("pause");
	return 0;
}