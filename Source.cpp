#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm> 
#include <cstdlib>
#include <cmath>


using namespace std;

void addBt2_8(vector<int> &V, int &bursttime2_8, int &q_process);
void addBt20_30(vector<int> &V, int &bursttime20_30, int &q_process);
void addBt35_40(vector<int> &V, int &bursttime35_40, int &q_process);
void show_all(vector<int> &V, int &q_process);
void random_arr(vector<int> &V);
void fcfs(vector<int> V, vector<int> &fcfs_wt, vector<int> &fcfs_tat, int &q_process);
void sjf(vector<int> V, vector<int> &sjf_wt, vector<int> &sjf_tat, int &q_process);
void rr(vector<int> V, vector<int> &rr_wt, vector<int> &rr_tat, int &q_process);


int main() {

	srand(time(NULL));
	int q_process = 0;
	int bursttime2_8 = 0;
	int bursttime20_30 = 0;
	int bursttime35_40 = 0;
	vector<int>V;
	vector<int>fcfs_wt;
	vector<int>fcfs_tat;
	vector<int>sjf_wt;
	vector<int>sjf_tat;
	vector<int>rr_wt;
	vector<int>rr_tat;
	
	cout << "Please imput quantity of process " << endl;
	cin >> q_process;
	cout << "How many Use burst time 2-8 msc in percent % " << endl;
	cin >> bursttime2_8;
	cout << "How many Use burst time 20-30 msc in percent % " << endl;
	cin >> bursttime20_30;
	int check1 = 0;
	while (check1 == 0) {
		cout << "How many Use burst time 35-40 msc in percent % " << endl;
		cin >> bursttime35_40;
		if (bursttime2_8 + bursttime20_30 + bursttime35_40 > 100) {
			cout << "all of burst time can't more than 100 in %" << endl;
			cout << "burst time 35-40 must be = " << 100 - (bursttime2_8 + bursttime20_30) << endl;

		}
		else {
			check1 = 1;
		}

	}

	addBt2_8(V, bursttime2_8, q_process);
	addBt20_30(V, bursttime20_30, q_process);
	addBt35_40(V, bursttime35_40, q_process);

	show_all(V, q_process);
	random_arr(V);
	show_all(V, q_process);
	
	fcfs(V, fcfs_wt, fcfs_tat, q_process);

	sjf(V, sjf_wt, sjf_tat, q_process);

	rr(V, rr_wt, rr_tat, q_process);

	system("pause");
	return 0;
	

}


void addBt2_8(vector<int> &V, int &bursttime2_8, int &q_process) {
	srand(time(NULL));
	int value;
	for (int i = 0; i < ((q_process * bursttime2_8) / 100); i++) {
		value = rand() % 7 + 2;
		V.push_back(value);
	}
	

}

void addBt20_30(vector<int> &V, int &bursttime20_30, int &q_process) {
	srand(time(NULL));
	int value;
	for (int i = 0; i < ((q_process * bursttime20_30) / 100); i++) {
		value = rand() % 11 + 20;
		V.push_back(value);
	}
	

}

void addBt35_40(vector<int> &V, int &bursttime35_40, int &q_process) {
	srand(time(NULL));
	int value;
	for (int i = 0; i < ((q_process * bursttime35_40) / 100); i++) {
		value = rand() % 6 + 35;
		V.push_back(value);
	}

}

void show_all(vector<int> &V, int &q_process) {

	for (int i = 0; i < V.size(); i++) {
		cout << V[i] << " ";
	}
	cout << endl;
}

void random_arr(vector<int> &V) {

	random_shuffle(V.begin(), V.end());

}

void fcfs(vector<int> V, vector<int> &fcfs_wt, vector<int> &fcfs_tat, int &q_process) {

	//wt[i] = bt[i-1] + wt[i-1] .
	float avg_wt = 0;
	float avg_tat = 0;
	float tp = 0;
	int wt = 0;
	int tat = 0;
	/*for (int i = 1; i< q_process; i++){
	
		fcfs_wt[i] = 0;
		for (int j = 0; j < i; j++) {
			fcfs_wt[i] += V[j];
		}
	}
	*/
	fcfs_wt.push_back(0);
	
	for (int i = 1; i< q_process; i++) {
		
		wt = fcfs_wt[i - 1] + V[i - 1] ;
		fcfs_wt.push_back(wt);
	}
	
	cout << "\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";

	for (int i = 0; i< q_process; i++)
	{
		//fcfs_tat[i] = V[i] + fcfs_wt[i];
		tat = V[i] + fcfs_wt[i];
		fcfs_tat.push_back(tat);

		avg_wt += fcfs_wt[i];
		avg_tat += fcfs_tat[i];
		cout << "\nP[" << i + 1 << "]" << "\t\t" << V[i] << "\t\t" << fcfs_wt[i] << "\t\t" << fcfs_tat[i];

		
	}
	tp = fcfs_tat[q_process - 1];
	
	avg_wt = avg_wt / q_process;
	avg_tat = avg_tat / q_process;
	
	cout << "\n\nAverage Waiting Time:" << avg_wt;
	cout << "\nAverage Turnaround Time:" << avg_tat << endl;
	cout << "Through put = " << tp / q_process << endl;

}

void sjf(vector<int> V, vector<int> &sjf_wt, vector<int> &sjf_tat, int &q_process) {

	vector<int> p;
	int pos;
	int temp;
	float avg_wt = 0;
	float avg_tat = 0;
	float tp = 0;
	int wt = 0;
	int tat = 0;
	//add vector p which contain process number
	for (int i = 0; i < q_process; i++)
	{
		p.push_back(i + 1);       //contains process number
	}
	//sorting burst time 
	for (int i = 0; i<q_process; i++)
	{
		pos = i;
		for (int j = i + 1; j<q_process; j++)
		{
			if (V[j]<V[pos])
				pos = j;
		}

		temp = V[i];
		V[i] = V[pos];
		V[pos] = temp;

		temp = p[i];
		p[i] = p[pos];
		p[pos] = temp;
	}

	//wt[0] = 0;            //waiting time for first process will be zero
	sjf_wt.push_back(0);    //calculate waiting time
						 
	//for (int i = 1; i<q_process; i++)
	//{
	//	wt[i] = 0;
	//	for (j = 0; j<i; j++)
	//		wt[i] += bt[j];

	//	total += wt[i];
	//}

	//avg_wt = (float)total / n;      //average waiting time
	//total = 0;
	for (int i = 1; i< q_process; i++) {

		wt = sjf_wt[i - 1] + V[i - 1];
		sjf_wt.push_back(wt);
		avg_wt += sjf_wt[i];
	}
	avg_wt = avg_wt / q_process;

	cout << "\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";

	//for (i = 0; i<n; i++)
	//{
	//	tat[i] = bt[i] + wt[i];     //calculate turnaround time
	//	total += tat[i];
	//	printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", p[i], bt[i], wt[i], tat[i]);
	//}

	//avg_tat = (float)total / n;     //average turnaround time
	//printf("\n\nAverage Waiting Time=%f", avg_wt);
	//printf("\nAverage Turnaround Time=%f\n", avg_tat);

	for (int i = 0; i< q_process; i++)
	{
		tat = V[i] + sjf_wt[i];   //calculate turnaround time
		sjf_tat.push_back(tat);
		avg_tat += sjf_tat[i];
		//printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", p[i], V[i], sjf_wt[i], sjf_tat[i]);
		cout << "\nP[" << p[i] << "]" << "\t\t" << V[i] << "\t\t" << sjf_wt[i] << "\t\t" << sjf_tat[i];
	}
	tp = sjf_tat[q_process - 1];

	avg_tat = avg_tat / q_process;     //average turnaround time
	
	cout << endl;
	cout << "\n\nAverage Waiting Time:" << avg_wt;
	cout << "\nAverage Turnaround Time:" << avg_tat << endl;
	cout << "Through put = " << tp / q_process << endl;

}

void rr(vector<int> V, vector<int> &rr_wt, vector<int> &rr_tat, int &q_process) {

	vector<int> p;
	int quantum;
	//int wt[n], tat[n]  = rr_wt, rr_tat
	int total_wt = 0;
	int total_tat = 0;

	for (int i = 0; i < q_process; i++)
	{
		p.push_back(i + 1);       //contains process number
	}

	cout << "Enter time_quantum " << endl;
	cin >> quantum;
	cout << endl;

	// Make a copy of burst times bt[] to store remaining 
	// burst times. 
	//int rem_bt[n];
	vector<int> rem_bt;
	for (int i = 0; i < q_process; i++) {
		//rem_bt[i] = bt[i];
		rem_bt.push_back(V[i]);
	}

	int t = 0; // Current time 

	while (1)
	{
		bool done = true;

		// Traverse all processes one by one repeatedly 
		for (int i = 0; i < q_process; i++)
		{
			// If burst time of a process is greater than 0 
			// then only need to process further 
			if (rem_bt[i] > 0)
			{
				done = false; // There is a pending process 

				if (rem_bt[i] > quantum)
				{
					// Increase the value of t i.e. shows 
					// how much time a process has been processed 
					t += quantum;

					// Decrease the burst_time of current process 
					// by quantum 
					rem_bt[i] -= quantum;
				}

				// If burst time is smaller than or equal to 
				// quantum. Last cycle for this process 
				else
				{
					// Increase the value of t i.e. shows 
					// how much time a process has been processed 
					t = t + rem_bt[i];

					// Waiting time is current time minus time 
					// used by this process 
					//rr_wt[i] = t - V[i];
					rr_wt.push_back(t - V[i]);

					// As the process gets fully executed 
					// make its remaining burst time = 0 
					rem_bt[i] = 0;
				}
			}
		}

		// If all processes are done 
		if (done == true)
			break;
	}

	// Function to calculate turn around time 

	// calculating turnaround time by adding 
	// bt[i] + wt[i] 
	for (int i = 0; i < q_process; i++) {
		//rr_tat[i] = V[i] + wt[i];
		rr_tat.push_back(V[i] + rr_wt[i]);
	}


	cout << "Processes " << " Burst time "
		<< " Waiting time " << " Turn around time\n";

	for (int i = 0; i<q_process; i++)
	{
		total_wt = total_wt + rr_wt[i];
		total_tat = total_tat + rr_tat[i];
		cout << " " << i + 1 << "\t\t" << V[i] << "\t "
			<< rr_wt[i] << "\t\t " << rr_tat[i] << endl;
	}


	cout << "Average waiting time = " << (float)total_wt / (float)q_process;
	cout << "\nAverage turn around time = " << (float)total_tat / (float)q_process;


	



}