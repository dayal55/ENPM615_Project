#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define YEAR 2016
#define NEW(x,n) (x*) malloc(n*sizeof(x))


//Check all the malloc statements and free the space - almost done checking remains
//Put all the functions below main and define them ago - no need
//Scan functions take two time values 
// Add check for date format - done
// add check for end date greater than start date - done
//Saving in a file - done
//Documentation
//Code is reused and copy pasted. Clean it.
//Doubt: Event name is with # or without # - its with #, my code is correct
//Add no input file feature - done
// Linklist data structure update for count and tail
// Check whether name is unique or not - done

//DAT = Date and Time
//date and time is divided into four integers.
typedef struct DAT{
	int hour;
	int min;
	int date;
	int month;
}DAT;

//Event structure with parameters
typedef struct EVENT{
	char name[20];
	DAT start_DAT;
	DAT end_DAT;
	char description[260];
}EVENT;

//Node structure is used to create linkedlist of events.
//It has event and pointer to the next event
typedef struct NODE{
	EVENT event;
	struct NODE* next;
}NODE;

//Linkedlist contains head, tail and number of nodes of the linklist
//Currently only head is used
typedef struct LL{
	NODE* head;
	NODE* tail;
	int number_of_nodes;
}LL;

//Global Variable for calender linkedlist
LL calender = {.head = NULL, .tail=NULL, .number_of_nodes=0};

//Convert string date format to DAT structure.
void ConvertToDate(DAT* dat,char* line)
{
	//-48 for char to int conversion
	dat->month = 10*(line[0]-48)+(line[1]-48);
	dat->date = 10*(line[3]-48)+(line[4]-48);
	dat->hour = 10*(line[6]-48)+(line[7]-48);
	dat->min = 10*(line[9]-48)+(line[10]-48);
}

//Check whether name is alphanumeric or not
int CheckAN(char* str)
{
	while(*str!='#')
	{
		if(!isalnum(*str))
			return 0;
		str++;
	}
	return 1;
}

//Check if date and time is in correct format or not.
int CheckDAT(DAT* dat)
{
	int legit=0;
	int daysinmonth[12]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (dat->month<13)
   	{
    	if(dat->date <= daysinmonth[dat->month-1])
    		legit++;
   	}
   	if(dat->hour<24 && dat->hour>=0 && dat->min>=0 && dat->min<60)
   		legit++;
   	return legit;
}

//Return node if the node exists
//Return NUll if does not exists
//Return Node based on search string
NODE* SearchNode(char* search_str)
{
	NODE* curr = calender.head;
	NODE* prev = NULL;
	while(curr != NULL)
	{
		if(strcmp(curr->event.name,search_str)==0)
			return curr;
		prev = curr;
		curr = curr->next;
	}
	return NULL;
}

//Check whether name is unique or not.
int CheckUniqueName(char* temp_title)
{
	if(SearchNode(temp_title)!=NULL)
		return 0;
	return 1;
}

char* ScanEventName()
{
	printf("Enter new event name (no more than 16 characters):");
	char* temp_title = NEW(char,17);
	while(*fgets(temp_title,5000,stdin)==10)
		;
    strtok(temp_title, "\n");
	temp_title[16] = '\0';
	int i;
	for(i=0;i<16 && temp_title[i]!='\0';i++)
	{
		if(temp_title[i]=='#')
		{
			char* return_title = NEW(char,i+1);
			strncpy(return_title,temp_title,i+2);
			if(CheckAN(temp_title))
			{
				if(CheckUniqueName(temp_title))
					return temp_title;
			else
			{
				printf("Error! Event name must be unique.\n");
				return ScanEventName();
			}
	}
	else
	{
		printf("Error! Only Alpha Numeric value\n");
		return ScanEventName();
	}
		}
	}
	if(i<15)
	{
		printf("Error! Event name must end with #\n");
		return ScanEventName();
	}
	//if string has more than 16 characters this will trim it to 15 characters and one # character
	temp_title[15] = '#';
	if(CheckAN(temp_title))
	{
		if(CheckUniqueName(temp_title))
			return temp_title;
		else
		{
			printf("Error! Event name must be unique.\n");
			return ScanEventName();
		}
	}
	else
	{
		printf("Error! Only Alpha Numeric value\n");
		return ScanEventName();
	}
}
//it will print statements according to the value
// 1 for new event start date
// 2 for new event end date
// 3 for timeblock start time
// 4 for timeblock end time

DAT ScanDAT(int value)
{
	char* temp_time = NEW(char,13);
	switch(value)
	{
		case 1:
		printf("Enter new event start time (mm/dd hh:mm):");
		break;

		case 2:
		printf("Enter new event end time (mm/dd hh:mm):");
		break;
		
		case 3:
		printf("Enter a start time (mm/dd hh:mm):");
		break;
		
		case 4:
		printf("Enter a end time (mm/dd hh:mm):");
		break;
	}
	while(*fgets(temp_time,5000,stdin)==10);
	strtok(temp_time, "\n");
	DAT dat;
	ConvertToDate(&dat,temp_time);
	if(CheckDAT(&dat)!=2 || temp_time[2]!='/' || temp_time[8]!=':')
	{
		printf("Error! Date and Time format wrong\n");
		return ScanDAT(value);
	}
	free(temp_time);
	return dat;
}
char* ScanEventDescription()
{
	printf("Enter new event description (no more than 256 characters):");
	char* temp_description = NEW(char,257);
	fgets(temp_description,5000,stdin);
	strtok(temp_description, "\n");
	temp_description[256] = '\0';
	int i;
	for(i=0;i<256 && temp_description[i]!='\0';i++)
	{
		if(temp_description[i]=='#')
		{
			char* return_description = NEW(char,i+1);
			strncpy(return_description,temp_description,i+2);
			return return_description;
		}
	}
	if(i<255)
	{
		printf("Error! Event description must end with #\n");
		return ScanEventDescription();
	}
	//if string has more than 16 characters this will trim it to 15 characters and one # character
	temp_description[255] = '#';
	return temp_description;
}
int CompareTime(DAT time1, DAT time2)
{
	int con1 = time1.month == time2.month;
	int con2 = time1.date == time2.date;
	int con3 = time1.hour == time2.hour;
	int con4 = time1.min == time2.min;

	if(time1.month > time2.month)
		return 1;
	else if(con1 && (time1.date > time2.date))
		return 1;
	else if(con1 && con2 && (time1.hour > time2.hour))
		return 1;
	else if(con1 && con2 && con3 && (time1.min > time2.min))
		return 1;
	else if(con1 && con2 && con3 && con4)
		return 1;
	return 0;
}
int CompareDAT(NODE* node1, NODE* node2)
{
	int con1 = node1->event.start_DAT.month == node2->event.start_DAT.month;
	int con2 = node1->event.start_DAT.date == node2->event.start_DAT.date;
	int con3 = node1->event.start_DAT.hour == node2->event.start_DAT.hour;
	int con4 = node1->event.start_DAT.min == node2->event.start_DAT.min;

	int con5 = node1->event.end_DAT.month == node2->event.end_DAT.month;
	int con6 = node1->event.end_DAT.date == node2->event.end_DAT.date;
	int con7 = node1->event.end_DAT.hour == node2->event.end_DAT.hour;
	int con8 = node1->event.end_DAT.min == node2->event.end_DAT.min;
	
	if(node1->event.start_DAT.month > node2->event.start_DAT.month)
		return 1;
	else if(con1 && (node1->event.start_DAT.date > node2->event.start_DAT.date))
		return 1;
	else if(con1 && con2 && (node1->event.start_DAT.hour > node2->event.start_DAT.hour))
		return 1;
	else if(con1 && con2 && con3 && (node1->event.start_DAT.min > node2->event.start_DAT.min))
		return 1;
	else if(con1 && con2 && con3 && con4)
	{
		printf("Warning %s and %s have the same start time.\n",node1->event.name,node2->event.name);
		if(node1->event.end_DAT.month > node2->event.end_DAT.month)
			return 1;
		else if(con5 && (node1->event.end_DAT.date > node2->event.end_DAT.date))
			return 1;
		else if(con5 && con6 && (node1->event.end_DAT.hour > node2->event.end_DAT.hour))
			return 1;
		else if(con5 && con6 && con7 && (node1->event.end_DAT.min > node2->event.end_DAT.min))
			return 1;
		else if(con5 && con6 && con7 && con8)
		{
			if(strcmp(node1->event.name,node2->event.name)>0)
				return 0;
		}
	}
	return 0;
}
void PrintNode(NODE* node)
{
	printf("%s\n",node->event.name);
	printf("%02d/%02d %02d:%02d\n",node->event.start_DAT.month,node->event.start_DAT.date,\
		node->event.start_DAT.hour,node->event.start_DAT.min);
	printf("%02d/%02d %02d:%02d\n",node->event.end_DAT.month,node->event.end_DAT.date,\
		node->event.end_DAT.hour,node->event.end_DAT.min);
	printf("%s\n\n\n",node->event.description);
}
void PrintAll()
{
	//clear screen
	system("clear");
	NODE* curr = calender.head;
	while(curr!=NULL)
	{
		PrintNode(curr);	
		curr = curr->next;
	}

}
int InsertNode(NODE* temp_node)
{
	NODE* curr = calender.head;
	NODE* prev = NULL;
	calender.number_of_nodes++;
	while(curr!=NULL)
	{
		//CompareDAT will return 1 if curr time is greater than new node (temp_node)
		//if that is the case than add temp node in the link list before curr node position
		//printf("%d",CompareDAT(curr,temp_node));
		if(CompareDAT(curr,temp_node))
		{
			if(curr == calender.head)
			{
				temp_node->next = calender.head;
				calender.head = temp_node;
			}
			else
			{
				prev->next = temp_node;
				temp_node->next = curr;
			}
			return 0;
		}
		prev = curr;
		curr = curr->next;
	}
	if(curr == calender.head)
	{
		temp_node->next = calender.head;
		calender.head = temp_node;
	}
	else
	{
		prev->next = temp_node;
		temp_node->next = curr;
	}
	return 0;
}
int NewEvent()
{
	NODE* temp_node = NEW(NODE,1);
	//scan event name
	strcpy(temp_node->event.name,ScanEventName());

	do{
	//scan event start time
	temp_node->event.start_DAT = ScanDAT(1);
	//scan event end time
	temp_node->event.end_DAT = ScanDAT(2);
	if(!CompareTime(temp_node->event.end_DAT,temp_node->event.start_DAT))
		printf("Error! Start time must be less than end time.\n");
	}while(!CompareTime(temp_node->event.end_DAT,temp_node->event.start_DAT));
	
	//scan event description
	strcpy(temp_node->event.description,ScanEventDescription());

	//add node to the link list
	InsertNode(temp_node);
	return 0;
}

int DeleteNode(char* search_str)
{
	NODE* curr = calender.head;
	NODE* prev = NULL;
	while(curr != NULL)
	{
		if(strcmp(curr->event.name,search_str)==0)
		{
			if(curr == calender.head)
				calender.head = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			return 1;
		}
		prev = curr;
		curr = curr->next;
	}
	printf("Error! %s not found\n",search_str);
	return 0;
}
int DeleteEvent()
{
	char search_str[17];
	printf("\nEnter the event name to be deleted:");
	scanf("%s",search_str);
	DeleteNode(search_str);
	printf("%s has been deleted\n",search_str);
	return 0;
}


int OptionModifyEventMenu(NODE* temp_node)
{
	int option;
	scanf("%d",&option);
	NODE* ModifiedNode = NEW(NODE,1);
	*ModifiedNode = *temp_node;
	DeleteNode(temp_node->event.name);
	switch(option)
	{
		case 1:
		strcpy(ModifiedNode->event.name,ScanEventName());
		break;

		case 2:
		ModifiedNode->event.start_DAT = ScanDAT(1);
		while(!CompareTime(temp_node->event.end_DAT,temp_node->event.start_DAT))
		{
			printf("Error! Start time must be less than end time.\n");
			ModifiedNode->event.start_DAT = ScanDAT(1);
		}
		break;

		case 3:
		ModifiedNode->event.end_DAT = ScanDAT(2);
		while(!CompareTime(temp_node->event.end_DAT,temp_node->event.start_DAT))
		{
			printf("Error! Start time must be less than end time.\n");
			ModifiedNode->event.end_DAT = ScanDAT(2);
		}
		break;

		case 4:
		strcpy(ModifiedNode->event.description,ScanEventDescription());
		break;

		default:
		printf("Error! option between 1-4 expected\n");
		return 1;
	}

	//PrintNode(ModifiedNode);	
	InsertNode(ModifiedNode);
	return 0;
}

void ModifyEvent()
{
	NODE* search_Node = NEW(NODE,1);
	char* search_str = NEW(char,17);
	while(1)
	{
		printf("Enter event name to modify:");
		scanf("%s",search_str);
		search_Node = SearchNode(search_str);
		if(search_Node==NULL)
			printf("Error! %s not found.\n",search_str);
		else
			break;
	}
	printf("Which field would you like to change?\n");
	printf("1. Change event name:\n");
	printf("2. Change start time:\n");
	printf("3. Change end time:\n");
	printf("4. Change description:\n");
	while(OptionModifyEventMenu(search_Node))
		;
	free(search_str);
}

void PrintTimeBlock()
{
	DAT start = ScanDAT(3);
	DAT end = ScanDAT(4);
	NODE* curr = calender.head;
	int cond1,cond2;
	while(curr!=NULL)
	{
		cond1 = CompareTime(end,curr->event.start_DAT) && CompareTime(curr->event.end_DAT,start);
		cond2 = CompareTime(start,curr->event.end_DAT) && CompareTime(curr->event.start_DAT,end);	
		if(cond1 || cond2)
			PrintNode(curr);
		curr = curr->next;
	}	
}

void PrintConflicts()
{
	printf("Enter the event name:");
	char* temp_str = NEW(char,17);
	while(*fgets(temp_str,5000,stdin)==10)
		;
    strtok(temp_str, "\n");
	NODE* node = SearchNode(temp_str);
	if(node == NULL)
	{
		printf("No conflicting event.\n");
		PrintConflicts();
	}
	else
	{
		NODE* curr = calender.head;
		int cond1,cond2,confs=0;
		while(curr!=NULL)
		{
			cond1 = CompareTime(node->event.end_DAT,curr->event.start_DAT) \
				&& CompareTime(curr->event.end_DAT,node->event.start_DAT);
			cond2 = CompareTime(node->event.start_DAT,curr->event.end_DAT) \
				&& CompareTime(curr->event.start_DAT,node->event.end_DAT);	
			if((cond1 || cond2) && node!=curr)
			{
				confs++;
				PrintNode(curr);
			}
			curr = curr->next;
		}
		if(!confs)
			printf("No conflicting event.\n");
	}
	free(temp_str);
}

void SearchName()
{
	printf("Enter the event name:");
	char* temp_str = NEW(char,17);
	while(*fgets(temp_str,5000,stdin)==10)
		;
    strtok(temp_str, "\n");
	NODE* node = SearchNode(temp_str);
	if(node == NULL)
		printf("%s not found.\n",temp_str);
	else
		PrintNode(node);
	free(temp_str);
}

void SearchKeyword()
{
	printf("Enter the event name:");
	char* temp_str = NEW(char,17);
	while(*fgets(temp_str,5000,stdin)==10)
		;
    strtok(temp_str, "\n");
	NODE* curr = calender.head;
	while(curr!=NULL)
	{
		if(strstr(curr->event.description,temp_str) != NULL)
			PrintNode(curr);
		else if(strstr(curr->event.name,temp_str) != NULL)
			PrintNode(curr);
		curr = curr->next;
	} 
	free(temp_str);
}
void SaveOutput(int argc,char* argv[])
{
	NODE* curr = calender.head;
	FILE* fpw;
	remove(argv[argc-1]);
	fpw = fopen(argv[argc-1],"w");
	if (fpw == NULL)
    	exit(EXIT_FAILURE);
	while(curr!=NULL)
	{
		fprintf(fpw,"%s\n%02d/%02d %02d:%02d\n%02d/%02d %02d:%02d\n%s\n\n\n",\
			curr->event.name,curr->event.start_DAT.month,curr->event.start_DAT.date,\
			curr->event.start_DAT.hour,curr->event.start_DAT.min,curr->event.end_DAT.month,\
			curr->event.end_DAT.date,curr->event.end_DAT.hour,curr->event.end_DAT.min,\
			curr->event.description);
		curr = curr->next;
	}
	fclose(fpw);
}
//Function to print Main Menu
void PrintMainMenu()
{
	//Add clear screen command
	system("clear");
	printf("Enter a number from the list below to select an option, or press 9 to quit.\n");
	printf("\nEdit Commands\n");
	printf("1. Add new Event\n");
	printf("2. Delete Event\n");
	printf("3. Modify Event\n");
	printf("\nPrint Commands\n");
	printf("4. Print all\n");
	printf("5. Print time block\n");
	printf("6. Print Conflicts\n");
	printf("\nSearch Commands\n");
	printf("7. Search by Name\n");
	printf("8. Search by keyword\n");
}

//User input of Main Menu
int OptionMainMenu(int argc,char* argv[])
{
	int option;
	scanf("%d",&option);
	switch(option)
	{
		case 1:
		NewEvent();
		break;

		case 2:
		DeleteEvent();
		break;

		case 3:
		ModifyEvent();
		break;

		case 4:
		PrintAll();
		break;

		case 5:
		PrintTimeBlock();
		break;

		case 6:
		PrintConflicts();
		break;

		case 7:
		SearchName();
		break;

		case 8:
		SearchKeyword();
		break;

		case 9:
		SaveOutput(argc,argv);
		PrintAll();
		exit(0);
		break;

		case 10:
		PrintMainMenu();
		break;

		default:
		printf("Error! Option between 1-9 is expected.\n");
		return 1;
	}
	return 0;
}

//This function assumes that input file is in correct format and would not check name or date and time.
void CalenderGenerator(int argc, char* argv[])
{
	FILE* fpr;
	switch(argc)
	{
		case 2:
		//I think nothing to do here
		//May be have to add something later
		//added because default won't work without this.
		break;

		case 3:
		fpr = fopen(argv[1],"r");
		if (fpr == NULL)
        	exit(EXIT_FAILURE);
        char* line = NEW(char,257);
        NODE* curr = calender.head; 
        //first fgets take name of the event 
        while(fgets(line, 20, fpr) != NULL)
        {
        	NODE* current_event = NEW(NODE,1);
        	
        	//name of the event
        	strtok(line, "\n");
        	strcpy(current_event->event.name,line);

        	//start date of the event
        	fgets(line, 15, fpr);
        	strtok(line, "\n");
        	ConvertToDate(&current_event->event.start_DAT,line);

        	//end date of the event
        	fgets(line, 15, fpr);
        	strtok(line, "\n");
        	ConvertToDate(&current_event->event.end_DAT,line);

        	//description of the event
        	fgets(line, 260, fpr);
        	strtok(line, "\n");
        	strcpy(current_event->event.description,line);
        	
        	//read empty line
        	fgets(line, 11, fpr);
        	fgets(line, 11, fpr);

        	//add node to the end of the linkedlist
        	if(calender.head == NULL)
        		calender.head = current_event;
        	else
        		curr->next = current_event;

        	current_event->next = NULL;
        	calender.tail = current_event;
        	curr = current_event;
        	calender.number_of_nodes+=1;

        }
        fclose(fpr);
		break;

		default:
		printf("Enter one or two input files\n");
		exit(0);
	}
}

int main(int argc, char* argv[])
{
	CalenderGenerator(argc,argv);
	printf("ENPM 615 Project\n\n");
	PrintMainMenu();
	while(1)
	{
		printf("\nEnter your choice. Press 10 to print the main menu again.\n");
		//ask gang qu about printing menu how many times
		while(OptionMainMenu(argc,argv));
	}
	return 0;
}