#include <iostream>
#include <cstdio>
#include <ctime>
#include <malloc.h>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <ratio>
#include "sqlite\sqlite3.h"
#pragma warning ( disable : 4703 )
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

struct dbpoint {
	string task;
	int time_task;
	bool checkbox = NULL;

	
};

struct DayPlan* create_DayPlan() {
	DayPlan* dayname = new DayPlan;
	dayname->start = NULL;
	return dayname;

}
static int callback(void* NotUsed, int argc, char** argv, char** someName) {
	for (int i = 0; i < argc; i++) {
		cout << someName[i] << ": " << argv[i] << endl;
	}
	return 0;
}
static int integrate(void* NotUsed, int argc, char** argv, char** someName) {

	int i;
	dbpoint* some = (dbpoint*)NotUsed;
		for (i = 0; i < argc; i++) {
			if (strcmp(someName[i], "Planpoint_Name") == 0)
				some->task = argv[1];
			if (strcmp(someName[i], "Time") == 0)
				some->time_task = atoi(argv[2]); 
			if (strcmp(someName[i], "Checkbox") == 0)
				some->checkbox = atoi(argv[3]);
		}
		
		
	return 0;
}

static int createTable(const char* dir)
{
	sqlite3* DB;
	char* messageError;

	string sql = "CREATE TABLE IF NOT EXISTS Day("
		"ID          INT NOT NULL,"
		"Planpoint_Name      TEXT NOT NULL, "
		"Time   INT NOT NULL, "
		"Checkbox     INT);";


	int exit = 0;
	exit = sqlite3_open(dir, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in createTable function." << endl;
		sqlite3_free(messageError);
	}
	else

	sqlite3_close(DB);


	return 0;
}
static int insertData(const char* dir,DayPlan* plan,int count) {
	sqlite3* DB;
	int exit;
	char* messageError;
	
	struct Planpoint* list = plan->start;
	for (int i = 1; i < count; i++) {
		list = list->next;
	}
	sqlite3_open(dir, &DB);
	if (list->checkbox == false) list->checkbox = 0;
	else list->checkbox = 1;
	if (list->time_task == NULL) list->time_task = 0;
	string sql = "INSERT INTO Day (ID, Planpoint_Name, Time, Checkbox) VALUES (" + to_string(count) + ",'" + list->task + "'," + to_string(list->time_task) +"," + to_string(list->checkbox) + ");; ";
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK) {
		cerr << "Error Insert " << messageError << endl;
		sqlite3_free(messageError);
	}
	else
	sqlite3_close(DB);
	
		return 0;

}

int add_db_planpoint(struct DayPlan* plan, int Maincount, const char* s) {

	sqlite3* DB;
	Planpoint* point = new Planpoint;
	dbpoint db;
	char* messageError;
	int check = 1;
	string checktext = " ";
	int exit = sqlite3_open(s, &DB);
	
		string add = "Select * FROM Day;";
		exit = sqlite3_exec(DB, add.c_str(), integrate, &db, &messageError);
		if (exit != 0) cout << messageError;
		if (checktext != db.task) checktext = db.task;
		else checktext = "";
		point->task = db.task;
		
		point->time_task = db.time_task;
		point->checkbox = db.checkbox;
		point->next = NULL;
		string to_del = "DELETE FROM Day WHERE ID=" + to_string(Maincount+1) + ";";
		exit = sqlite3_exec(DB, to_del.c_str(), NULL, 0, &messageError);
		if (checktext == "")  
			return Maincount; 
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
		Maincount++;
	
	return Maincount;

}
int add_new_planpoint(struct DayPlan* plan, int Maincount) {
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
			printf("Incorrect data entry, 1.Try again. \n 2.Get back \n");
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
		}
		switch (hours) {
		case 0:
			hours = 21;
			break;
		case 1:
			hours = 22;
			break;

		case 2:
			hours = 23;
			break;
		default:
			hours = hours - 3;
			break;
		}


		SettingTime = std::time(NULL);
		if (SettingTime % 86400 < (hours * 3600 + minutes * 60)) {
			SettingTime = SettingTime - SettingTime % 86400;
			SettingTime = SettingTime + (hours * 3600 + minutes * 60);
		}
		else {
			SettingTime = SettingTime + 86400 - SettingTime % 86400;
			SettingTime = SettingTime + (hours * 3600 + minutes * 60);

		}

		break;
	default:
		SettingTime = NULL;
		break;
	}


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

	Maincount++;
	return Maincount;

}
void time_sort(struct DayPlan* l, int Maincount)
{
	struct Planpoint* compare = l->start;
	struct Planpoint* compare2 = l->start;
	string swaptask;
	bool swapcheckbox;

	for (int i = 0; i < Maincount - 1; i++) {
		time_t compareTime = 3000000000;
		compare = l->start;
		compare2 = l->start;
		for (int f = 0; f < i; f++) {
			compare = compare->next;
			compare2 = compare2->next;

		}
		for (int j = i; j < Maincount-1; j++) {
			if (compareTime > compare2->time_task) {
				compareTime = compare2->time_task;
				swaptask = compare2->task;
				swapcheckbox = compare2->checkbox;
			}
			compare2 = compare2->next;
		}
		compare = l->start;
		compare2 = l->start;
		for (int f = 0; f < i; f++) {
			compare = compare->next;
			compare2 = compare2->next;
		}
		while (compare2->time_task > compareTime) {
			compare2 = compare2->next;
		}

		compare2->time_task = compare->time_task;
		compare->time_task = compareTime;
		compare2->checkbox = compare->checkbox;
		compare->checkbox = swapcheckbox;
		compare2->task = compare->task;
		compare->task = swaptask;

	}
	return;
}
int emergency_pop(struct DayPlan* l, int Maincount, int point_to_delete) {
	struct Planpoint* poplist2 = l->start;
	struct Planpoint* poplist = NULL;
	string deleted_task;
	time_t deleted_time;
	bool deleted_check;
	if (poplist2 == NULL)
	{
		cout << "Uncorrect command\n";
		return Maincount;
	}

	
	for (int i = 1; i < point_to_delete; i++) {
		poplist = poplist2;
		poplist2 = poplist->next;
		if (poplist2 == NULL)
		{
			cout << "Uncorrect command\n";
			return Maincount;
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
	if (poplist != NULL) {
		poplist->next = NULL;
	}
	else l->start = NULL;
	Maincount--;
	return Maincount;

}

int delete_list(struct DayPlan* plan, int Maincount) {
	struct Planpoint* deletelist = plan->start;
	struct Planpoint* nextdelete;
	if (deletelist == NULL) {
		return Maincount;

	}
	while (deletelist->next != NULL) {
		nextdelete = deletelist->next;
		delete (deletelist);
		deletelist = nextdelete;
	}
	delete deletelist;
	plan->start = NULL;
	Maincount = 0;
	return Maincount;
}
int pop(struct DayPlan* l, int Maincount) {
	struct Planpoint* poplist2 = l->start;
	struct Planpoint* poplist = NULL;
	string deleted_task;
	time_t deleted_time;
	bool deleted_check;
	int point_to_delete;
	if (poplist2 == NULL)
	{
		cout << "Uncorrect command\n";
		return Maincount;
	}

	cout << "What planpoint are you want to delete?:\n";
	cin >> point_to_delete;
	for (int i = 1; i < point_to_delete; i++) {
		poplist = poplist2;
		poplist2 = poplist->next;
		if (poplist2 == NULL)
		{
			cout << "Uncorrect command\n";
			return Maincount;
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
	if (poplist != NULL) {
		poplist->next = NULL;
	}
	else l->start = NULL;
	Maincount--;
	return Maincount;

}
void show_list(struct DayPlan* plan, int Maincount)
{
	time_t day = time(NULL);
	day = day + (86400 - day % 86400)- 3*3600;
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
		if ((day - 86400) > list->time_task && list->time_task!=0) {
			emergency_pop(plan, Maincount, markcount);
			markcount++;
			printf("\n");
			if (list->next == NULL) break;
		}
		
		if (day < list->time_task) {
			day =day+86400;
			printf("NEXT DAY\n");
			printf("_______________________________________________\n");
		}
		cout << markcount << '.' << list->task;
		if (list->checkbox == NULL) {
			cout << " -";
		}
		else {
			cout << " +";
		}
		if (list->time_task != NULL && list->time_task!= -858993460) {
			cout << " Appointed time: " << ctime(&list->time_task);

		}
		if (list->checkbox == 1 && (list->time_task == 0|| list->time_task == -858993460)) {
			emergency_pop(plan, Maincount, markcount);
			markcount++;
			printf("\n");
			if (list->next == NULL) break;
		}
		printf("\n");
		list = list->next;
		markcount++;
	}
		if (day < list->time_task) {
			printf("NEXT DAY\n");
			printf("_______________________________________________\n");
		}
	cout << markcount << '.' << list->task;
	if (list->checkbox == NULL) {
		cout << " -";
	}
	else {
		cout << " +";
	}
	if (list->time_task != NULL && list->time_task != -858993460) {
		cout << " Appointed time: " << ctime(&list->time_task);

	}
	if (list->checkbox == 1 && (list->time_task == 0 || list->time_task == -858993460)) {
		emergency_pop(plan, Maincount, markcount);
	
	}
	if ((day - 86400) > list->time_task && list->time_task != 0) {
		emergency_pop(plan, Maincount, markcount);
	}
	printf("\n");


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
void menu(struct DayPlan* plan, const char* dir ) {
	createTable(dir);
	int Maincount = 0;
	int check = 0;
	int compare_Maincount = 0;
	do {
		Maincount = add_db_planpoint(plan, Maincount, dir);
		compare_Maincount++;
	} while (compare_Maincount == Maincount);
	while (check != 6) {
		printf("**********************************************************************");
		printf("\n1. Show Plan;\n2. Add new Planpoint;\n3. Delete Planpoint;\n4. Mark a completed Planpoint\n5. Delete all plan\n6. Leave Programm\n");
		printf("**********************************************************************\n");
		printf("Choose action: ");
		scanf_s("%d", &check);
		printf(" check vot tut ->%d\n ", check);

		switch (check) {
		case 1:
			time_sort(plan, Maincount);
			show_list(plan,Maincount);
			break;
		case 2:
			Maincount = add_new_planpoint(plan, Maincount);
			break;
		case 3:
			Maincount = pop(plan, Maincount);
			break;
		case 4:
			fill_CheckBox(plan);
			break;

		case 5:
			Maincount = delete_list(plan, Maincount);
			break;
			/*case 6:
				break;*/
		case 6:
			for (int i = Maincount; i >0; i--) {
				insertData(dir, plan, i);
			}
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
	const char* dir = R"(C:\Users\gdima\source\repos\console-time-tracker\kursach\Plan_Data.db)";

	struct DayPlan* plan = create_DayPlan();
	menu(plan, dir);
	
	return 0;
}