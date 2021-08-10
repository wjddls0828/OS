#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct process {
	int arrival_time;
	int Burst_time;
	int waiting_time;
	int turnaround_time;
	int response_time;
}Process;

void FCFS(Process* pro);
void SJF(Process* pro);
void RR(Process* pro);
void gantt(Process* pro);
void rearrange(Process* pro);
void RR(Process* p);
void RR_gantt(Process* p, int len, int q);

int main() {
	STARTUPINFO si; 
	PROCESS_INFORMATION pi; 

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	Process pro[5];
	Process qu[5];
	if (!CreateProcess(NULL, "C:\\Users\\82105\\source\\repos\\sumto10000\\Release\\sumto10000.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "Create Process Failed");
		return -1;
	}
	clock_t proces1_start_time = clock();
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t proces1_end_time = clock();
	double p1_bt = (proces1_end_time - proces1_start_time);
	pro[0].arrival_time = 1;
	pro[0].Burst_time = p1_bt;

	clock_t proces2_start_time = clock();
	if (!CreateProcess(NULL, "C:\\Users\\82105\\source\\repos\\sumto100\\Release\\sumto100.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "Create Process Failed");
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t proces2_end_time = clock();
	double p2_bt = (proces2_end_time - proces2_start_time);
	pro[1].arrival_time = 2;
	pro[1].Burst_time = p2_bt;

	clock_t proces3_start_time = clock();
	if (!CreateProcess(NULL, "C:\\Users\\82105\\source\\repos\\sumto500\\Release\\sumto500", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "Create Process Failed");
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t proces3_end_time = clock(); 
	double p3_bt = (proces3_end_time - proces3_start_time);
	pro[2].arrival_time = 3;
	pro[2].Burst_time = p3_bt;

	clock_t proces4_start_time = clock();
	if (!CreateProcess(NULL, "C:\\Users\\82105\\source\\repos\\Project7\\Release\\Project7.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "Create Process Failed");
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t proces4_end_time = clock();
	double p4_bt = (proces4_end_time - proces4_start_time);
	pro[3].arrival_time = 4;
	pro[3].Burst_time = p4_bt;
	
	clock_t proces5_start_time = clock();
	if (!CreateProcess(NULL, "C:\\Users\\82105\\source\\repos\\sumto10\\Release\\sumto10.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "Create Process Failed");
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t proces5_end_time = clock();
	double p5_bt = (proces5_end_time - proces5_start_time);
	pro[4].arrival_time = 5;
	pro[4].Burst_time = p5_bt;

	CloseHandle(pi.hProcess); 
	CloseHandle(pi.hThread); 

	printf("\nFCFS\n");
	for (int i = 0; i < 5; i++)
	{
		qu[i].arrival_time = pro[i].arrival_time;
		qu[i].Burst_time = pro[i].Burst_time;
		qu[i].waiting_time = pro[i].waiting_time;
	}
	FCFS(qu);
	gantt(qu);

	printf("Nonpreemptive SJF\n");
	for (int i = 0; i < 5; i++)
	{
		qu[i].arrival_time = pro[i].arrival_time;
		qu[i].Burst_time = pro[i].Burst_time;
		qu[i].waiting_time = pro[i].waiting_time;
	}
	SJF(qu);
	gantt(qu);

	printf("RR\n");
	for (int i = 0; i < 5; i++)
	{
		qu[i].arrival_time = pro[i].arrival_time;
		qu[i].Burst_time = pro[i].Burst_time;
		qu[i].waiting_time = pro[i].waiting_time;
	}
	RR(qu);

	system("PAUSE"); 
	return 0;
}

void FCFS(Process* pro) {
	Process tmp;
	
	for (int i = 4; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (pro[j].arrival_time > pro[j + 1].arrival_time) {
				pro[j + 1] = pro[j];
				tmp = pro[j + 1];
				pro[j] = tmp;
			}
		}
	}
	pro[0].waiting_time = 0;
	pro[0].turnaround_time = pro[0].Burst_time;
	for (int t = 1; t < 5; t++)
	{
		pro[t].waiting_time = 0;
		for (int e = 0; e < t; e++)
			pro[t].waiting_time += pro[e].Burst_time;
		pro[t].turnaround_time = pro[t].waiting_time + pro[t].Burst_time;
	}
}

void SJF(Process* pro) {
	Process tmp;
	for (int t = 4; t > 0; t--) {
		for (int e = 0; e < t; e++) {
			if (pro[e].Burst_time > pro[e + 1].Burst_time) {
				pro[e + 1] = pro[e];
				tmp = pro[e + 1];
				pro[e] = tmp;
			}
		}
	}
	pro[0].waiting_time = 0;
	pro[0].turnaround_time = pro[0].Burst_time;
	for (int i = 1; i < 5; i++)
	{
		pro[i].waiting_time = 0;
		for (int j = 0; j < i; j++)
			pro[i].waiting_time += pro[j].Burst_time;
		pro[i].turnaround_time = pro[i].waiting_time + pro[i].Burst_time;
	}
}



void rearrange(Process* pro) {
	Process tmp;
	for (int i = 4; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if ( pro[j + 1].arrival_time<pro[j].arrival_time) {
				pro[j + 1] = pro[j];
				tmp = pro[j + 1];
				pro[j] = tmp;
			}
		}
	}
}

void gantt(Process* p)
{
	int i, j;
	double wt_aver = 0;
	printf(" ");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < p[i].Burst_time; j++) 
			printf("--");
		printf(" ");
	}
	printf("\n|");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < p[i].Burst_time - 1; j++) 
			printf(" ");
		printf("P%d", i);
		for (j = 0; j < p[i].Burst_time - 1; j++) 
			printf(" ");
		printf("|");
	}
	printf("\n ");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < p[i].Burst_time; j++) 
			printf("--");
		printf(" ");
	}
	printf("\n");
	printf("0");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < p[i].Burst_time; j++) 
			printf("  ");
		if (p[i].turnaround_time > 9) 
			printf("\b"); 
		printf("%d", p[i].turnaround_time);
	}
	printf("\n");
	rearrange(p);
	printf("waiting time:");
	for (int i = 0; i < 5; i++) {
		printf("P%d = %d(ms), ", i + 1, p[i].waiting_time);
		wt_aver += p[i].waiting_time;
	}
	printf("\n");
	printf("average waiting time : %f(ms)\n\n", wt_aver / 5);

}

void RR(Process* p)
{
	int wt_total = 0;
	int turnaround = 0;
	int res_t_total = 0;
	double ave_wt = 0;
	int time_tm = 0;
	int len = 5;
	int q = 3;
	int left_bt[5];
	int response_c[5];
	int i;

	Process tmp;
	
	for (int i = 4; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (p[j].arrival_time > p[j + 1].arrival_time) {
				p[j + 1] = p[j];
				tmp = p[j + 1];
				p[j] = tmp;
			}
		}
	}
	for (i = 0; i < 5; i++)
	{
		left_bt[i] = p[i].Burst_time;
		response_c[i] = FALSE;
	}
	while (TRUE)
	{
		int ch = TRUE;
		for (i = 0; i < len; i++)
		{
			if (left_bt[i] > 0)
			{
				ch = FALSE;
				if (response_c[i] == FALSE)
				{
					response_c[i] = TRUE;
					p[i].response_time = time_tm - p[i].arrival_time;
				}
				if (left_bt[i] > q)
				{
					time_tm += q;
					left_bt[i] -= q;
				}
				else
				{
					time_tm += left_bt[i];
					p[i].waiting_time = time_tm - p[i].Burst_time;
					left_bt[i] = 0;
				}
			}
		}
		if (ch == TRUE)
			break;
	}
	for (int i = 0; i < len; i++)
		p[i].turnaround_time = p[i].Burst_time + p[i].waiting_time - p[i].arrival_time;
	for (i = 0; i < len; i++)
	{
		p[i].waiting_time = p[i].turnaround_time - p[i].Burst_time;
		wt_total += p[i].waiting_time;
		turnaround += p[i].turnaround_time;
		res_t_total += p[i].response_time;
	}
	RR_gantt(p, 5, 10);
	rearrange(p);
	printf("waiting time : ");
	for (int i = 0; i < 5; i++) {
		printf("P%d = %d(ms), ", i + 1, p[i].waiting_time);
		ave_wt += p[i].waiting_time;
	}
	printf("\n");
	printf("average waiting time : %f(ms)\n\n", ave_wt / 5);
}

void RR_gantt(Process* p, int len, int q)
{
	int i, j;
	int time_tm = 0;
	int bt_total = 0;
	int left_bt[5];
	q = 3;
	for (i = 0; i < len; i++)
	{
		left_bt[i] = p[i].Burst_time;
		bt_total += p[i].Burst_time;
	}
	while (TRUE)
	{
		int ch = TRUE;
		for (i = 0; i < len; i++)
		{
			if (left_bt[i] > 0)
			{
				ch = FALSE;
				if (left_bt[i] < q)
				{
					printf(" ");
					for (j = 0; j < left_bt[i]; j++)
						printf("--");
				}
				else
				{
					printf(" ");
					for (j = 0; j <= q; j++)
						printf("--");
				}
				if (left_bt[i] > q)
				{
					time_tm += q;
					left_bt[i] -= q;
				}
				else
				{
					time_tm += left_bt[i];
					p[i].waiting_time = time_tm - p[i].Burst_time;
					left_bt[i] = 0;
				}
			}
		}
		if (ch == TRUE)
			break;
	}
	printf(" \n");
	for (i = 0; i < len; i++)
	{
		left_bt[i] = p[i].Burst_time;
	}
	while (TRUE)
	{
		int ans = TRUE;
		for (i = 0; i < len; i++)
		{
			if (left_bt[i] > 0)
			{
				ans = FALSE;
				if (left_bt[i] < q)
				{
					printf("|");
					if (left_bt[i] != 1)
					{
						for (j = 0; j <= left_bt[i] / 2; j++)
							printf(" ");
						printf("P%d", i);
						for (j = 0; j <= left_bt[i] / 2; j++)
							printf(" ");
					}
					else
						printf("P%d", i);
				}
				else
				{
					printf("|");
					for (j = 0; j < q; j++)
						printf(" ");
					printf("P%d", i);
					for (j = 0; j < q; j++)
						printf(" ");
				}
				if (left_bt[i] > q)
				{
					time_tm += q;
					left_bt[i] -= q;
				}
				else
				{
					time_tm += left_bt[i];
					p[i].waiting_time = time_tm - p[i].Burst_time;
					left_bt[i] = 0;
				}
			}
		}
		if (ans == TRUE)
			break;
	}
	printf("|\n");
	for (i = 0; i < len; i++)
	{
		left_bt[i] = p[i].Burst_time;
	}
	while (TRUE)
	{
		int ans = TRUE;
		for (i = 0; i < len; i++)
		{
			if (left_bt[i] > 0)
			{
				ans = FALSE;
				if (left_bt[i] < q)
				{
					printf(" ");
					for (j = 0; j < left_bt[i]; j++)
						printf("--");
				}
				else
				{
					printf(" ");
					for (j = 0; j <= q; j++)
						printf("--");
				}
				if (left_bt[i] > q)
				{
					time_tm += q;
					left_bt[i] -= q;
				}
				else
				{
					time_tm += left_bt[i];
					p[i].waiting_time = time_tm - p[i].Burst_time;
					left_bt[i] = 0;
				}
			}
		}
		if (ans == TRUE)
			break;
	}
	printf("\n");
	for (i = 0; i < len; i++)
		left_bt[i] = p[i].Burst_time;
	time_tm = 0;
	while (TRUE)
	{
		int ans = TRUE;
		for (i = 0; i < len; i++)
		{
			if (left_bt[i] > 0)
			{
				ans = FALSE;
				if (left_bt[i] < q)
				{
					printf("%-2d", time_tm);
					for (j = 0; j < left_bt[i] - 1; j++)
						printf("  ");
					printf(" ");
				}
				else
				{
					printf("%-2d", time_tm);
					for (j = 0; j < q; j++)
						printf("  ");
					printf(" ");
				}
				if (left_bt[i] > q)
				{
					time_tm += q;
					left_bt[i] -= q;
				}
				else
				{
					time_tm += left_bt[i];
					p[i].waiting_time = time_tm - p[i].Burst_time;
					left_bt[i] = 0;
				}
			}
		}
		if (ans == TRUE)
			break;
	}
	printf("%-3d\n", bt_total);
	printf("\n");
}

