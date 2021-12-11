#include <iostream>
#include <stdio.h>
#include <ctime>
#include <malloc.h>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#pragma warning(disable : 4996)


using namespace std;
struct DayPlan {
	struct Planpoint* start;

};
struct Planpoint {
	string task;
	time_t time_task;
	bool checkbox = NULL;
	Planpoint* next;
};

struct DayPlan* create_DayPlan() {
	DayPlan* dayname = new DayPlan;
	dayname->start = NULL;
	return dayname;

}

void add_new_planpoint(struct DayPlan* plan) {
	Planpoint* point = new Planpoint;
	int check;
	string Task;
	time_t SettingTime;
	int minutes, hours;

	printf("add new planpoint:");
	cin.ignore();
	std::getline(cin, Task);

	point->task = Task;
	point->next = NULL;
	printf("Do you wanna set a timer?:\n 1. Yes.\n 2. No.\n");
	scanf_s("%d", &check);
	switch (check) {
	case 1:
		printf("Set hours:");
		scanf_s("%d", &hours);
		while (hours > 23) {
			printf("Incorrect data entry, 1.try again. \n 2.Get back \n");
			scanf_s("%d", &check);
			switch (check) {
			case 1:
				scanf_s("%d", &hours);
				break;
			default:
				hours = 0;
				break;
			}
		}
		printf("Set minutes:");
		scanf_s("%d", &minutes);
		if (check != 1) {
			while (minutes > 59) {
				printf("Incorrect data entry");
				scanf_s(".%d", &minutes);
			}
			break;
	default:
		break;
		}

		SettingTime = std::time(NULL);
		SettingTime = SettingTime - SettingTime % 60;
		SettingTime = SettingTime + (hours * 3600 + minutes * 60);
		point->time_task = SettingTime;

		if (plan->start == NULL) {
			plan->start = point;

		}
		else
		{
			struct Planpoint* structpoint = plan->start;
			while (1) {
				if (structpoint->next == NULL) {
					structpoint->next = point;
					break;

				}
				else {
					structpoint = structpoint->next;
				}
			}
		}

	}
	return;

}

void delete_list(struct DayPlan* plan) {
	struct Planpoint* deletelist = plan->start;
	struct Planpoint* nextdelete;
	if (deletelist == NULL) {
		return;

	}
	while (deletelist->next != NULL) {
		nextdelete = deletelist->next;
		delete (deletelist);
		deletelist = nextdelete;
	}
	delete deletelist;
	plan->start = NULL;

}
void pop(struct DayPlan* l) {
	struct Planpoint* poplist2 = l->start;
	struct Planpoint* poplist = NULL;
	string deleted_task;
	time_t deleted_time;
	bool deleted_check;
	int point_to_delete;
	if (poplist2 == NULL)
	{
		cout << "Uncorrect command\n";
		return;
	}
	cout << "What planpoint are you want to delete?:\n";
	cin >> point_to_delete;
	for (int i = 1; i < point_to_delete; i++) {
		poplist = poplist2;
		poplist2 = poplist->next;
		if (poplist2 == NULL)
		{
			cout << "Uncorrect command\n";
			return;
		}

	}
	while (poplist2->next != NULL) {
		poplist = poplist2;
		poplist2 = poplist->next;
		deleted_task = poplist->task;
		poplist->task = poplist2->task;
		poplist2->task = deleted_task;
		deleted_check = poplist->checkbox;
		poplist->checkbox = poplist2->checkbox;
		poplist2->checkbox = deleted_check;
		deleted_time = poplist->time_task;
		poplist->time_task = poplist2->time_task;
		poplist2->time_task = deleted_time;
	}

	delete poplist2;
	poplist->next = NULL;
	return;

}
void show_list(struct DayPlan* plan)
{
	int markcount = 1;
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

		cout << markcount << '.' << list->task;
		if (list->checkbox == NULL) {
			cout << " -";
		}
		else {
			cout << " +";
		}
		cout << " Appointed time: " << ctime(&list->time_task);
		printf("\n");
		list = list->next;
		markcount++;
	}

	cout << markcount << '.' << list->task;
	if (list->checkbox == NULL) {
		cout << " -";
	}
	else {
		cout << " +";
	}
	cout << " Appointed time: " << ctime(&list->time_task);


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
	for (int i = 1; i < n; i++) {
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