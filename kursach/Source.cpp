#include <iostream>
#include <stdio.h>
#include <ctime>
#include <malloc.h>
#include <string>
#include<vector>


using namespace std;
struct DayPlan {
	struct Planpoint* start;
};
struct Planpoint {
	string task;
	//time_t seconds;
	//int time;
	//bool checkbox;
	Planpoint* next;
};

struct DayPlan* create_DayPlan() {
    DayPlan* dayname = new DayPlan ;
	dayname->start = NULL;
	return dayname;

}



void add_new_planpoint(struct DayPlan* plan) {
	Planpoint* key = new Planpoint;

	printf("add new planpoint:");
	string Task;
	cin >> Task;
	size_t poz = Task.find("\n");
	Task = Task.substr(0, poz);
	
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	key->task = Task;
	key->next = NULL;
	if (plan->start == NULL) {
		plan->start = key;

	}
	else
	{
		struct Planpoint* ion = plan->start;
		while (1) {
			if (ion->next == NULL) {
				ion->next = key;
				break;

			}
			else {
				ion = ion->next;
			}
		}
	}
	return;
}
 
void delete_list(struct DayPlan* plan) {
	struct Planpoint* delete1 = plan->start;
	struct Planpoint* delete2;
	if (delete1 == NULL) {
		return;

	}
	while (delete1->next != NULL) {
		delete2 = delete1->next;
		delete (delete1);
		delete1 = delete2;
	}
	delete delete1;
	plan->start = NULL;

}
void pop(struct DayPlan* l) {
	struct Planpoint* s2 = l->start;
	struct Planpoint* s = NULL;
	string g;
	if (s2 == NULL) {
		return;
	}
	if (s2->next == NULL) {
		delete_list(l);
		return;
	}
	while (s2->next != NULL) {
		s = s2;
		s2 = s->next;
	}

	g = s2->task;

	delete (s2);
	s->next = NULL;
	return;

}
void show_list(struct DayPlan* plan)
{
	int n = 1;
	struct Planpoint* list = plan->start;
	printf("\n______________________________________\n");
	if (list == NULL)
	{

		printf("EMPTY LIST");
		printf("\n______________________________________\n");
		return;
	}
	while (list->next != NULL)
	{
		
		cout << n <<'.' << list->task;

		printf(".");



		printf("\n");
		list = list->next;
		n++;
	}

	cout << n << '.' << list->task << '.';


	printf("\n______________________________________\n");



}
void menu(struct DayPlan* plan){
	int check=0;
	while (check != 7) {
		printf("**********************************************************************");
		printf("\n1. Show Plan;\n2. Add new Planpoint;\n3. Delete last Planpoint;\n4. Swap two Planpoints\n5. Delete all plan\n6. Sort for nothing\n7. Leave Programm");
		printf("**********************************************************************\n");
		printf("Choose action: ");
		scanf_s("%d",&check);
		printf(" check vot tut ->%d\n ", check);

		switch (check) {
		case 1:
			show_list(plan);
			break;
		case 2:
			add_new_planpoint(plan);
			break;
		case 3:
			pop(plan);
			break;
		case 4:
			printf("Unavaible now");
			break;

		case 5:
			delete_list(plan);
			break;
		case 6:
			
			break;
		case 7:
			break;
		case 0:
			break;
		default:
			printf("\nUncorrect command\n");
			break;
		}
	}
	
	
		

}
int main() {
	struct DayPlan* plan = create_DayPlan();
	menu(plan);
	
	return 0;
 }