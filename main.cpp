#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>



class sort_indices
{
private:
	int* mparr;
public:
	sort_indices(int* parr) : mparr(parr) {}
	bool operator()(int i, int j) const { return mparr[i] > mparr[j]; }
};

class process
{
public:
	int size_of_process;
	int no_of_machines;
	int* process_table;
	int* weight;
	int* order_of_weights;
	int* order;
	int Cmax_array[501][21];
	process(std::string);
	//int calculate_length_of_process() const;
	void print_weights() const;
	void print_order_of_weights() const;
	void do_NEH();
	void print_order() const;
	int count_cmax(int*);
	int count_part_cmax(int, int, int*);
};

void process::print_order_of_weights() const
{
	for (int i = 0; i < size_of_process; i++)
	{
		std::cout << weight[order_of_weights[i]] << " ";
	}
}

void process::do_NEH()////////////////Tu skonczylem
{
	int* ready_order = new int[size_of_process];
	int* tmp_order = new int[size_of_process];
	std::cout << std::endl;
	for (int i = 0; i < size_of_process; i++)
	{
		tmp_order[i] = order_of_weights[i];
		ready_order[i] = order_of_weights[i];
		//std::cout << "tmp_order:" << tmp_order[i] << std::endl;
		//std::cout << "weight_order:" << order_of_weights[i] << std::endl;
	}
	//tmp_order[0] = order_of_weights[0];
	ready_order[0] = order_of_weights[0];
	int tmp_Cmax = count_part_cmax(1,no_of_machines, tmp_order);
	int best_Cmax = tmp_Cmax;
	int best_position = 0;
	for (int n = 1; n < size_of_process; n++)
	{
		int best_position = 0;
		//std::cout << std::endl << std::endl << std::endl << "n= " << n;
		//tmp_order[i] = order_of_weights[i];
		//std::cout << std::endl << "!!!!!!!pierwszy order" << tmp_order[0];
		best_Cmax = count_part_cmax(n+1,no_of_machines, tmp_order);
		//std::cout << std::endl << "poczatkowe cmax: " << best_Cmax;
		for (int m = 0; m < n; m++)
		{
			//std::cout << std::endl << "m= " << m;
			//std::cout << std::endl << "n-m=" << tmp_order[n - m];
			//std::cout << std::endl << "n-m-1=" << tmp_order[n - m - 1];
			std::swap(tmp_order[n - m], tmp_order[n - m - 1]);

			//std::cout << std::endl << "Po zmianie: "<< "n-m=" << tmp_order[n - m];
			//std::cout << std::endl << "n-m-1=" << tmp_order[n - m - 1];
			tmp_Cmax = count_part_cmax(n+1, no_of_machines, tmp_order);
			//std::cout << std::endl << "kolejne" << m << " cmax: " << tmp_Cmax;
			// || (tmp_Cmax==best_Cmax&&tmp_order[n-m]>tmp_order[n-m-1])
			if (tmp_Cmax <= best_Cmax)
			{
				best_Cmax = tmp_Cmax;
				best_position = m+1;
			}
			//std::cout << "Best position: " << best_position << std::endl;
		}
		//std::cout << "TUTAJ2: "<< order_of_weights[n];
		ready_order[n] = order_of_weights[n];
		//std::cout << "TUTAJ3: " << ready_order[n];
		for (int i = 0; i <= n; i++)
		{
			//std::cout << "ready" << i << ": " << ready_order[i];
			tmp_order[i] = ready_order[i];
		}
		//std::cout << "swap: " <<ready_order[n] << " i " << ready_order[n - best_position];
		if (best_position != 0) {
			for (int k = 0; k < best_position; k++)
			{
				std::swap(ready_order[n - k],ready_order[n - k - 1]);
			}
			//std::swap(ready_order[n], ready_order[n - best_position]);
		}
		//std::cout << std::endl << "koncowe part c max" << " cmax: " << count_part_cmax(size_of_process,no_of_machines,ready_order);
		for (int i = 0; i <= n; i++)
		{
			//std::cout << "ready" << i << ": " << ready_order[i];
			tmp_order[i] = ready_order[i];
		}
		
	}
	std::cout << std::endl << "Koncowy wynik po NEH: " << count_cmax(ready_order) << std::endl;
	std::cout << "koncowy order: ";
	for(int n = 0; n < size_of_process; n++)
	{
		std::cout << ready_order[n]+1 << " ";
	}
}


void process::print_weights() const
{
	for (int i = 0; i < size_of_process; i++)
	{
		std::cout << weight[i] << " ";
	}
}
void process::print_order() const
{
	for (int i = 0; i < size_of_process; i++)
	{
		std::cout << order_of_weights[i] + 1 << " ";
	}
}

int process::count_cmax(int* order_to_cmax)
{
	int current_job;

	for (int i = 0; i < size_of_process; i++) {
		Cmax_array[i][0] = 0;
	}

	for (int i = 0; i < no_of_machines; i++) {
		Cmax_array[0][i] = 0;
	}

	for (int i = 1; i <= size_of_process; i++) {
		for (int j = 1; j <= no_of_machines; j++) {
			current_job = process_table[(order_to_cmax[i-1])*no_of_machines+j-1];
			//std::cout << "Job: " << current_job << std::endl;

			Cmax_array[i][j] = std::max(Cmax_array[i - 1][j], Cmax_array[i][j - 1]) + current_job;
		}
	}
	return Cmax_array[size_of_process][no_of_machines];
}

int process::count_part_cmax(int job, int machine, int* order_to_cmax)
{
	int current_job;
	for (int i = 0; i < job; i++)
		//std::cout << std::endl << "order2: " << order_to_cmax[i] + 1;

	for (int i = 0; i < size_of_process; i++) {
		Cmax_array[i][0] = 0;
	}

	for (int i = 0; i < no_of_machines; i++) {
		Cmax_array[0][i] = 0;
	}
	int index = 0;
	int index2 = 0;
	int index3 = 0;
	for (int i = 1; i <= job; i++) {
		for (int j = 1; j <= no_of_machines; j++) {
			index3 = order_to_cmax[i];
			index2 = order_to_cmax[i - 1];
			index = (order_to_cmax[i - 1] * no_of_machines) + j - 1;
			current_job = process_table[index];
			//std::cout << "Job: " << current_job << std::endl;
			Cmax_array[i][j] = std::max(Cmax_array[i - 1][j], Cmax_array[i][j - 1]) + current_job;
		}
	}
	return Cmax_array[job][machine];
}

process::process(std::string name)
{
	std::ifstream infile("neh.data.txt");
	if (infile.is_open()) { ; }
	else {
		std::cout << "Blad podczas otwierania pliku\n";
		std::cout << "Upewnij sie, ze w katalogu z programem znajduje sie plik data.txt z danymi." << std::endl;
		std::cin.get();
		exit(-1);
	}

	std::string tmp_f = "";
	while (tmp_f != name) infile >> tmp_f;

	infile >> size_of_process;
	infile >> no_of_machines;
	//size_of_process--;

	std::cout << "\nRozmiar procesu: " << size_of_process << std::endl;

	process_table = new int[size_of_process * no_of_machines];
	int tmp;
	for (int j = 0; j < size_of_process*no_of_machines; j++)
	{
		infile >> process_table[j];
		//std::cout << "Druk: " << process_table[j] << std::endl;
	}
	
	weight = new int[size_of_process];
	for (int i=0; i<size_of_process; i++)
	{
		weight[i] = 0;
		for (int j=0; j<no_of_machines; j++)
		{
			weight[i] += process_table[i * no_of_machines + j];
		}
	}

	order_of_weights = new int[size_of_process];
	int* indices = new int[size_of_process];
	order = new int[size_of_process];
	for (int i = 0; i < size_of_process; i++)
	{
		indices[i] = i;
		order[i] = i;
	}
	std::stable_sort(indices, indices + size_of_process, sort_indices(weight));
	int* inv_order_of_weights = new int[size_of_process];
	for (int i = 0; i < size_of_process; i++)
	{
		inv_order_of_weights[i] = indices[i];
	}
	
	for (int i = 0; i < size_of_process-1; i++)
	{
		if (inv_order_of_weights[i] == inv_order_of_weights[i + 1]) {
			std::cout << "Zmieniam kolejnosc" << std::endl;
			std::swap(inv_order_of_weights[i], inv_order_of_weights[i + 1]);
		}
	}

	for (int i = 0; i < size_of_process; i++)
	{
		order_of_weights[i] = inv_order_of_weights[i];
		//order_of_weights[i] = inv_order_of_weights[size_of_process-i-1];
	}

	infile.close();
	
	//teraz order_of_weights jest tablica w jakiej kolejnosci brac z tablicy zadan wg calej dlugosci
}

int load_process(int liczba) {
	process process_1("data.00" + std::to_string(liczba) + ":");
	std::cout << "wagi procesu " << liczba << " przed sortowaniem: " << std::endl;
	process_1.print_weights();
	std::cout << std::endl << "wagi procesu " << liczba << " po sortowaniu:" << std::endl;
	process_1.print_order_of_weights();
	std::cout << std::endl << "kolejnosc procesu " << liczba << " po sortowaniu:" << std::endl;
	process_1.print_order();
	//std::cout << "TUTAJ1";
	std::cout << std::endl << "Caly Cmax:" << process_1.count_cmax(process_1.order_of_weights);
	//std::cout << std::endl << "czesc Cmax: "<< process_1.count_part_cmax(2,3,process_1.order_of_weights) << std::endl;
	process_1.do_NEH();
	return 0;
}
int load_process2(int liczba) {
	process process_1("data.0" + std::to_string(liczba) + ":");
	//std::cout << "wagi procesu " << liczba << " przed sortowaniem: " << std::endl;
	//process_1.print_weights();
	//std::cout << std::endl << "wagi procesu " << liczba << " po sortowaniu:" << std::endl;
	//process_1.print_order_of_weights();
	//std::cout << std::endl << "kolejnosc procesu " << liczba << " po sortowaniu:" << std::endl;
	//process_1.print_order();
	//std::cout << "TUTAJ1";
	std::cout << std::endl << "Caly Cmax:" << process_1.count_cmax(process_1.order_of_weights);
	//std::cout << std::endl << "czesc Cmax: "<< process_1.count_part_cmax(2,3,process_1.order_of_weights) << std::endl;
	process_1.do_NEH();
	return 0;
}
int load_process3(int liczba) {
	process process_1("data." + std::to_string(liczba) + ":");
	//std::cout << "wagi procesu " << liczba << " przed sortowaniem: " << std::endl;
	//process_1.print_weights();
	//std::cout << std::endl << "wagi procesu " << liczba << " po sortowaniu:" << std::endl;
	//process_1.print_order_of_weights();
	//std::cout << std::endl << "kolejnosc procesu " << liczba << " po sortowaniu:" << std::endl;
	//process_1.print_order();
	//std::cout << "TUTAJ1";
	std::cout << std::endl << "Caly Cmax:" << process_1.count_cmax(process_1.order_of_weights);
	//std::cout << std::endl << "czesc Cmax: "<< process_1.count_part_cmax(2,3,process_1.order_of_weights) << std::endl;
	process_1.do_NEH();
	return 0;
}

int main() {
	std::cout << std::endl << "Program do sortowania zadan w procesie" << std::endl;
	std::cout << "Laduje plik neh.data.txt i rozpoczynam prace!" << std::endl;
	
	for (int i = 0; i < 10; i++)
	{
		std::cout << std::endl << "Czas na proces data.00" << i << std::endl;
		load_process(i);
	}
	for (int i = 10; i < 100; i++)
	{
		std::cout << std::endl << "Czas na proces data.0" << i << std::endl;
		load_process2(i);
	}

	for (int i = 100; i < 121; i++)
	{
		std::cout << std::endl << "Czas na proces data." << i << std::endl;
		load_process3(i);
	}

	std::cout << std::endl << "Koniec programu!" << std::endl;
	int a;
	std::cout << "Wprowadz dowolny znak i wcisnij klawisz Enter, aby wyjsc z programu." << std::endl;
	std::cin >> a;
	
	return 0;
}
