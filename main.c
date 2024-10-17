/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mostafa Alaa Abedelhamid Yonis
 * @brief          : Clinic Management System
 ******************************************************************************
 */

/* ********************** Includes Section Start ********************** */
#include <stdio.h>
#include <stdlib.h>
#include "STD_Types.h"
#define True            0
#define False           1

/* ********************** Includes Section End   ********************** */

/* ********************** Macro Section Start ************************* */
typedef struct Patient_Type Patient;
struct Patient_Type{
	u8 name[40];
	u8 age;
	u8 gender[6];
	u16 ID;
	u8 res;
	Patient *Next;
};
Patient* head = NULL;
/* ********************** Macro Section End   ************************* */

/* ********************** Global Variables Section Start ************** */
const u8 AdminPasswordDefault= 1234;
u8 FlagOut=False;
u8 flagPassword=False;
u8 password ,counter;
u16 ListLength = 0;
u8* AvailableSlots[6] = {"2pm to 2:30pm","2:30pm to 3pm","3pm to 3:30pm","4pm to 4:30pm","4:30pm to 5pm","Not Reserved"};
u8 ReservedSlots [6] = {0};
/* ********************** Global Variables  Section End   ************* */

/* ********************** Global Decleration Section Start ************* */

/* ********************** Global Decleration  Section End   ************ */

/* ********************** Sub-Program(Function) Declerations Section Start ******* */
void AddNewPatient();
void EditPatient();
void ReserveSlotDoctor();
void Cancelreservation();
void ViewPatientRecord();
void ViewReservations();

/* ********************** Sub-Program(Function) Declerations Section End ******* */


int main()
{

    /* ********************** Local Variables Section Start ************** */
    u8 TheMode,AM,YM;
    u8 ChoiceAdmin, ChoiceUser;
    /* ********************** Local Variables  Section End   ************* */
    printf("\n\n");

    printf("                                         Welcome To Clinic Management System\n");
    while(FlagOut == False)
    {

        printf("\n\n\n");
        printf("1-For Admin Mode\n");
        printf("2-For User Mode \n");
        printf("3-Exit \n");
        printf("              Enter Your Choice: ");
        scanf("%i",&TheMode);
        switch(TheMode)
        {
        case 1:
            printf("\n\n\n                                 Welcome MY Admin                         \n");

            while(flagPassword == False)
            {
                printf("\n\nplease enter your secret Number : ");
                scanf("%i", &password);

                if(password == AdminPasswordDefault)
                {
                    flagPassword = True;
                    break;
                }
                counter++;
                if(counter == 3)
                {
                    break;
                }

                printf("Wrong Password, Try Again.\n");

            }
            if(flagPassword == True)
            {
                flagPassword = False;
                while(1)
                {
                printf("\n\n");
                printf("1-Add new patient record\n");
                printf("2-Edit patient record\n");
                printf("3-Reserve a slot with the doctor\n");
                printf("4-Cancel reservation\n");
                printf("                  Enter Your Choice: ");
                scanf("%i",&ChoiceAdmin);
                switch(ChoiceAdmin)
                {
                    case 1: AddNewPatient(); break;
                    case 2: EditPatient(); break;
                    case 3: ReserveSlotDoctor(); break;
                    case 4:Cancelreservation(); break;
                    default: printf("Wrong Entry.\n\n"); break;
                }
                printf("Continue in Admin mode?");
                printf("\n1-Yas or 2-No\n");fflush(stdout);
                scanf("%d",&AM);
                if(AM == 1){
                    continue;
                }

                else{
                    break;
                }

                }
                }
            else
            {
               printf("ERROR\n\n");
            }
        break;
        case 2:
            printf("\n\n\n                                 Welcome In the user mode                         \n");
            while(1){
                printf("\n\n");
                printf("1-View patient record.\n");
                printf("2-View today's reservations.\n");
                printf("                  Enter Your Choice: ");
                scanf("%d",&ChoiceUser);
                switch(ChoiceUser)
                {
                    case 1:ViewPatientRecord(); break;
                    case 2:ViewReservations(); break;
                }
                printf("Continue in User mode?");
                printf("\n1-Yas or 2-No\n");
                scanf("%d",&YM);
                if(YM == 1){
                    continue;
                }

                else{
                    break;
                }
            }
        break;
        case 3 :
            printf("Thank you for using my  Clinic Management System");
            FlagOut=True;
        break;
        default:
            printf("ERORR,TRY AGAIN...........");
        }
        }

    return 0;
}
/* ********************** Sub-Program(Function) Section Start ************* */
void AddNewPatient()
{
    u16 id;
    u8 flag = 0;
    printf("                                   Add New Patient                              ");
    printf("\nplease enter Patient ID:  ");
    scanf("%d", &id);
    if (ListLength == 0)
	{
		Patient* temp = (Patient*) malloc(sizeof(Patient));
		printf("\n\nEnter Patient's Name: ");
		scanf(" %[^\n]s",temp -> name);
		printf("\nEnter Patient's age: ");
		scanf("%d",&temp -> age);
		printf("\nEnter Patient's Gender \n(Male or Female)\n");
		scanf("%s",temp -> gender);
		temp -> ID = id;
		temp -> res = 5;
		temp -> Next = head;
		head = temp;

		printf("Added successfully.\n\n");
	}
	else{
		Patient* temp = (Patient*) malloc(sizeof(Patient));
		Patient* Add = head;
		while( Add != NULL)
		{
			if(Add -> ID == id)
			{
				flag = 1;
				break;
			}
			Add = Add -> Next;
		}

		if(flag == 1)
		{
			printf("ID already exists.\n\n");
		}
		else{
		    printf("Enter Patient's Name: ");
		    scanf("%s",temp -> name);
		    printf("Enter Patient's Age: ");
		    scanf("%d",&temp -> age);
		    printf("Enter Patient's Gender \n(Male or Female)\n");
		    scanf("%s",temp -> gender);
			temp -> ID = id;
			temp -> res = 5;
			temp -> Next = NULL;
			Add = head;
			while((Add->Next) != NULL)
			{
				Add = Add->Next;
			}
			Add->Next = temp;
			printf("Added successfully.\n\n");
		}
	}
	ListLength++;
}
void EditPatient()
{
    u8 flag = 0;
	u16 id;
    printf("                                   Edit Patient                              ");

    printf("\nenter Patient ID: ");
    scanf("%d",&id);
    if (ListLength == 0)
    {
        printf("NO Patients");
    }else
    {
        Patient* Edit = head;
		while(Edit != NULL)
		{
			if(Edit -> ID == id)
			{
				flag = 1;
				break;
			}
			Edit = Edit -> Next;
		}
				if(flag == 1)
		{
			printf("Update Data\n");
		    printf("Enter Patient's Name: ");
		    scanf("%s",Edit -> name);
		    printf("Enter Patient's Age: ");
		    scanf("%d",&Edit -> age);
		    printf("Enter Patient's Gender \n(Male or Female)\n");
		    scanf("%s",Edit -> gender);
			printf("Editing done successfully.\n\n");
		}else{
			printf("TRY AGAIN\n\n");
		}
    }

}

void ReserveSlotDoctor()
{
    u16 id;
	Patient * ptr = head;
	u16 position=0;
	u8 check=0;
	u8 reserver=0;
    printf("\n\n                                   Reserve a slot with the doctor                              ");
	printf("\n\nEnter The ID : ");
	scanf("%d",&id);
	while ( ptr != NULL)
	{

		if ( ptr->ID == id )
		{
			position++;
			break;
		}

		ptr=ptr->Next;
	}

	if( position > 0)
	{
		for (u8 x=0 ; x < 5 ; x++ )
	{
		if(ReservedSlots[x]==0)
			printf("%d- %s\n",x+1,AvailableSlots[x]);
		else
		{
			check++;
		}
	}
		if(check>=5)
		{
			printf("\n No Availble Reservetions !");
			return;
		}
		else
		{
			printf("\nYour Choice = ");
			scanf("%d",&reserver);
		}
		if( reserver > 0 && reserver <= 5)
		{
		ptr->res = reserver-1;
		ReservedSlots[reserver-1]=1;
		}
		else
			printf("Wrong Choice !");
	}
	else
		printf("TRY AGAIN");

}

void Cancelreservation()
{
    u16 id;
	Patient * ptr = head;
	u16 position=0;

    printf("\n\n                                   Cancel reservation                              ");
	printf("\n\nEnter The ID  : ");
	scanf("%d",&id);
	while ( ptr != NULL)
	{

		if ( ptr->ID == id )
		{
			position++;
			break;
		}

		ptr=ptr->Next;
	}

	if( position > 0)
	{

		if(ReservedSlots[ptr->res]==1)
		{
			printf("( %s ) cancelled \n",AvailableSlots[ptr->res]);
			ReservedSlots[ptr->res]=0;
			ptr->res = 5;

		}

		else
		{
			printf("NO reseverd ....");
		}

	}
	else
    {
        printf("TRY AGAIN");
    }

}

void ViewPatientRecord()
{
    u8 flag = 0;
	u16 id;
    printf("\n\n                                   View Patient Record                              ");
	printf("\n\nEnter The ID  : ");
	scanf("%d",&id);
	if (ListLength == 0)
	{
        printf("TRY AGAIN,Incorrect ID..!!!");
	}
	else
    {
        Patient* Record = head;
		while(Record != NULL)
		{
			if(Record -> ID == id)
			{
				flag = 1;
				break;
			}
			Record = Record -> Next;
		}
		if(flag==1)
        {
            printf("Patient ID is %d\n",Record -> ID);
            printf("Patient's Name is %s\n",Record -> name);
            printf("Patient's age is %d\n",Record -> age);
            printf("Patient Patient's Gender %s\n",Record -> gender);
        }
        	else
    {
        printf("TRY AGAIN");
    }
    }
}
void ViewReservations()
{
    printf("\n\n                                    View today's reservations.                              \n");
    Patient* View = head;
	if(ListLength == 0)
	{
		printf("Not found today's reservations \n\n");
	}else{
		while(View != NULL)
		{
			if(View->res == 5)
			{
				printf("(%s) not reserved yet. \n\n",View->name);
			}
			else
			{
				printf("(%s) has reservation at (%s) \n\n",View->name,AvailableSlots[View->res]);
			}
			View = View->Next;
		}
	}
}

/* ********************** Sub-Program(Function) Section End ************* */

/**
 ******************************************************************************
 User          Date                 Brief
 ******************************************************************************

*/
