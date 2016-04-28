#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define YEAR 2016
#define NEW(x,n) (x*) malloc(n*sizeof(x))


//Check all the malloc statements and free the space
//Put all the functions below main and define them ago
//Scan functions take two time values
// Add check for date format
// add check for end date greater than start date



//DAT = Date and Time
typedef struct DAT{
	int hour;
	int min;
	int date;
	int month;
}DAT;

typedef struct EVENT{
	char name[20];
	DAT start_DAT;
	DAT end_DAT;
	char description[260];
}EVENT;

typedef struct NODE{
	EVENT event;
	struct NODE* next;
}NODE;

typedef struct LL{
	NODE* head;
	NODE* tail;
	int number_of_nodes;
}LL;

//Global Varialbe for calender linkedlist
LL calender;

void ConvertToDate(DAT* dat,char* line)
{
	//-48 for char to int converstion
	dat->month = 10*(line[0]-48)+(line[1]-48);
	dat->date = 10*(line[3]-48)+(line[4]-48);
	dat->hour = 10*(line[6]-48)+(line[7]-48);
	dat->min = 10*(line[9]-48)+(line[10]-48);
}
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
char* ScanEventName()
{
	printf("Enter new event name (no more than 16 characters):");
	char* temp_title = NEW(char,17);
	while(*fgets(temp_title,5000,stdin)==10);
	//scanf("%[^\n]",temp_title);
	temp_title[16] = '\0';
	int i;
	for(i=0;i<16 && temp_title[i]!='\0';i++)
	{
		if(temp_title[i]=='#')
		{
			char* return_title = NEW(char,i+1);
			strncpy(return_title,temp_title,i+2);
			if(CheckAN(return_title))
			{
				return return_title;
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
		return temp_title;
	}
	else
	{
		printf("Error! Only Alpha Numeric value\n");
		return ScanEventName();
	}
}
DAT* ScanStartDAT()
{
	char* temp_time = NEW(char,13);
	printf("Enter new event start time (mm/dd hh:mm):");
	fgets(temp_time,5000,stdin);
	DAT* dat = NEW(DAT,1);
	ConvertToDate(dat,temp_time);
	if(CheckDAT(dat)!=2)
	{
		printf("Error! Date and Time format wrong\n");
		return ScanStartDAT();
	}
	return dat;
}
DAT* ScanEndDAT()
{
	char* temp_time = NEW(char,13);
	printf("Enter new event end time (mm/dd hh:mm):");
	fgets(temp_time,5000,stdin);
	DAT* dat = NEW(DAT,1);
	ConvertToDate(dat,temp_time);
	if(CheckDAT(dat)!=2)
	{
		printf("Error! Date and Time format wrong\n");
		return ScanEndDAT();
	}
	return dat;
}
char* ScanEventDescription()
{
	printf("Enter new event description (no more than 256 characters):");
	char* temp_description = NEW(char,257);
	fgets(temp_description,5000,stdin);
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
	/*if(con1 && con2 && con3 && con4)
	{
		printf("Warning %s and %s have the same start time.\n",node1->event.name,node1->event.name);
	}*/
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
		printf("Warning %s and %s have the same start time.\n",node1->event.name,node1->event.name);
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

void PrintAll()
{
	//clear screen
	NODE* curr = calender.head;
	while(curr!=NULL)
	{
		printf("%s",curr->event.name);
		printf("%02d/%02d %02d:%02d\n",curr->event.start_DAT.month,curr->event.start_DAT.date,\
			curr->event.start_DAT.hour,curr->event.start_DAT.min);
		printf("%02d/%02d %02d:%02d\n",curr->event.end_DAT.month,curr->event.end_DAT.date,\
			curr->event.end_DAT.hour,curr->event.end_DAT.min);
		printf("%s\n\n",curr->event.description);	
		curr = curr->next;
	}
}

int NewEvent()
{
	NODE* temp_node = NEW(NODE,1);
	//scan event name
	strcpy(temp_node->event.name,ScanEventName());

	//scan event start time
	temp_node->event.start_DAT = *ScanStartDAT();

	//scan event end time
	temp_node->event.end_DAT = *ScanEndDAT();

	//scan event description
	strcpy(temp_node->event.description,ScanEventDescription());

	//add node to the link list
	NODE* curr = calender.head;
	NODE* prev = NULL;
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
			PrintAll();
			return 0;

		}
		prev = curr;
		curr = curr->next;
	}
	return 0;
}

void DeleteEvent()
{

}

void ModifyEvent()
{

}


void PrintTimeBlock()
{

}

void PrintConflicts()
{

}

void SearchName()
{

}

void SearchKeyword()
{

}

//User input of Main Menu
int OptionMainMenu()
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
		exit(0);
		break;

		default:
		printf("Error! Option between 1-9 is expected.\n");
		return 1;
	}
	return 0;
}
//Function to print Main Menu
void PrintMainMenu()
{
	//Add clear screen command
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

void init_Calender()
{
	calender.head=NULL;
	calender.tail=NULL;
	calender.number_of_nodes=0;
}


//This function assumes that input file is in correct format and would not check name or date and time.
void CalenderGenerator(int argc, char* argv[])
{
	init_Calender();
	FILE* fpr;
	switch(argc)
	{
		case 2:
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
        	strcpy(current_event->event.name,line);

        	//start date of the event
        	fgets(line, 15, fpr);
        	ConvertToDate(&current_event->event.start_DAT,line);

        	//end date of the event
        	fgets(line, 15, fpr);
        	ConvertToDate(&current_event->event.end_DAT,line);

        	//description of the event
        	fgets(line, 260, fpr);
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
	while(1)
	{
		PrintMainMenu();
		//ask gang qu about printing menu how many times
		while(OptionMainMenu());
	}
	return 0;
}