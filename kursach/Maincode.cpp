#include <iostream>
#include <stdio.h>
#include <ctime>
#include <malloc.h>
#include <string>
#include <vector>


using namespace std;
struct DayPlan {
	struct Planpoint* start;
};
struct Planpoint {
	string task;
	time_t seconds;
	//int time;
	bool checkbox=NULL;
	Planpoint* next;
};

struct DayPlan* create_DayPlan() {
	DayPlan* dayname = new DayPlan;
	dayname->start = NULL;
	return dayname;

}



void add_new_planpoint(struct DayPlan* plan) {
	Planpoint* key = new Planpoint;
	string Task;
	printf("add new planpoint:");
	cin.ignore();
    std::getline(cin, Task);
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
	struct Planpoint* swap = NULL;
	string g;
	bool check;
	int n;
	if (s2 == NULL)
	{
		cout << "Uncorrect command\n";
		return;
	}
	cout << "What planpoint are you want to delete?:\n";
	cin >> n;
	for (int i = 1; i < n; i++) {
		s = s2;
		s2 = s->next;
		if (s2 == NULL)
		{
			cout << "Uncorrect command\n";
			return;
		}

	}
	while (s2->next != NULL) {
		s = s2;
		s2 = s->next;
		  g = s->task;
		  s->task = s2->task;
		  s2->task = g;
		  check = s->checkbox;
		  s->checkbox = s2->checkbox;
		  s2->checkbox = check;
	}
	
	delete s2;
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

		cout << n << '.' << list->task;
		if (list->checkbox == NULL) {
			cout << " -";
		}
		else {
			cout << " +";
		}
		printf("\n");
		list = list->next;
		n++;
	}

	cout << n << '.' << list->task;
	if (list->checkbox == NULL) {
		cout << " -";
	}
	else {
		cout << " +";
	}


	printf("\n______________________________________\n");



}
void fill_CheckBox(struct DayPlan* plan) {
	struct Planpoint* list = plan->start;
	int n;
	if (list == NULL)
	{
		cout << "Uncorrect command\n";
		return;
	}
	cout << "What planpoint are comleted?:\n";
	cin >> n;
		for (int i = 1; i < n; i++){
			list = list->next;
			if (list == NULL)
			{
				cout << "Uncorrect command\n";
				return;
			}
			
	}
		list->checkbox = true;
		return;
}
void menu(struct DayPlan* plan) {
	int check = 0;
	while (check != 7) {
		printf("**********************************************************************");
		printf("\n1. Show Plan;\n2. Add new Planpoint;\n3. Delete Planpoint;\n4. Mark a completed Planpoint\n5. Delete all plan\n6. Sort for nothing\n7. Leave Programm\n");
		printf("**********************************************************************\n");
		printf("Choose action: ");
		scanf_s("%d", &check);
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
			fill_CheckBox(plan);
			break;

		case 5:
			delete_list(plan);
			break;
		/*case 6:

			break;*/
		case 7:
			break;
		//case 0:
			//break;
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