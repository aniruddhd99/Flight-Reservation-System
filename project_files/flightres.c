#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

int mainmenu();
void booktickets(char usracc[]);
int viewaccout(int n, char acc[]);
void viewflights(int n, char acc[]);
void viewtickets(char usracc[]);
void view_tickets(char usracc[]);
void manageflights(char admacc[]);
void addflight(char admacc[]);
void removeflight(char admacc[]);
void modifyflight(char admacc[]);
void login();
void signup();
int userpage(char usracc[]);
int adminpage(char admacc[]);
void titlebar();
int checkcancel(char readline[]);
char *omitlinebreak(char readline[]);
char *strdata(char *s,int n);
char *Replace_tilde_by_space(char *original);
char *Replace_space_by_tilde(char *original);
int string_to_integer(char *arr);
void viewbill(char bookingref[],int n1,int n2,int n3,int cost);


void main()
{
	int choice;
	while(true)
	{
		choice=mainmenu();
		if(choice==3)
			break;
	}
}

int mainmenu()
{
	int choice,invalid=1;
	titlebar();
	printf("\n\t\t\t\t                      |  Main Menu  |\n\n");
	printf("\n\t\t\t\t                        1. Login\n");
	printf("\n\t\t\t\t                        2. Sign up\n");
	printf("\n\t\t\t\t                        3. Exit\n");
	while(invalid)	
	{
		printf("\t\tEnter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 3:	printf("\n\t\tThank you for using Book My Trip! Hope to see you soon!\n\n");
					invalid=0;
					break;
			
			case 1: login();
					invalid=0;
					break;
					
			case 2: signup();
					invalid=0;
					break;
					
			default: printf("\n\t\t**Please enter a valid option**\n");
					break;
		}
		//if(choice==3)
			//break;
	}
	return choice;
}

void login()
{
	char userid[50],passwd[50],readline[200],str[50];
	str[0]='Y';
	int valid=0;
	FILE *fadm = fopen("project_files/Admin_data.txt", "r") ;
	FILE *fusr = fopen("project_files/User_data.txt", "r") ;
		
	while(str[0]=='Y')
	{
		FILE *fadm = fopen("project_files/Admin_data.txt", "r") ;
		FILE *fusr = fopen("project_files/User_data.txt", "r") ;
		titlebar();
		printf("\n\t\t\t\t                        |  Login  |\n\n");
		printf("\n\t\t\t\t              Enter Username: ");
		scanf(" %[^\n]%*c", &userid);
		printf("\n\t\t\t\t              Enter Password: ");
		scanf(" %[^\n]%*c", &passwd);
		valid=0;
		
		while(!feof(fadm)) 
		{ 
			fgets(readline, sizeof(readline), fadm); 
			if(str==NULL)
			{}
			else
			{
			if(strcmp(strdata(readline,0),userid)==0 && strcmp(strdata(readline,1),passwd)==0)
			{
				printf("\t\t    successful login\n\n");
				int logout=0;
				while(logout==0)
					logout=adminpage(readline);
				valid=1;
				break;
			}
			}

		} 
		while(!feof(fusr)) 
		{ 
			fgets(readline, sizeof(readline), fusr); 
			if(str==NULL)
			{}
			else
			{
			if(strcmp(strdata(readline,0),userid)==0 && strcmp(strdata(readline,1),passwd)==0)
			{
				printf("\t\t    successful login\n\n");
				int logout=0;
				while(logout==0)
					logout=userpage(readline);
				valid=1;
				break;
			}
			}
		} 
		if(valid==0)
			printf("\t\t    invalid login details\n\n");
		
		printf("\n\t\tEnter 'Y' to log in again. Press any other key to return to main menu.\n\t\t");
		scanf("%s",str);
	}	
	fclose(fadm);
	fclose(fusr);
}

void signup()
{
	titlebar();
	printf("\n\t\t\t\t                      |  Sign Up  |\n\n");
	char usrname[50],passwd[30],name[70],gender[3],contact[15],c[5],readline[100];
	printf("\t\tEnter username: ");
	scanf(" %[^\n]%*c",usrname);
	FILE *fp1,*fp2;
	fp1=fopen("project_files/User_data.txt","r");
	fp2=fopen("project_files/Admin_data.txt","r");
	int avaiable=1;
	while(fgets(readline, sizeof(readline), fp1)!=NULL)
	{
		if(strcmp(usrname,strdata(readline,0))==0)
		{
			avaiable=0;
			break;
		}
	}
	while(fgets(readline, sizeof(readline), fp1)!=NULL)
	{
		if(strcmp(usrname,strdata(readline,0))==0)
		{
			avaiable=0;
			break;
		}
	}
	if(avaiable==1)
	{
		
		printf("\t\tEnter password: ");
		scanf(" %[^\n]%*c",passwd);
		
		printf("\t\tEnter Name: ");
		scanf(" %[^\n]%*c",name);
		strcpy(name,Replace_space_by_tilde(name));
		
		printf("\t\tEnter Contact no.: ");
		scanf(" %[^\n]%*c",contact);
		
		printf("\t\tEnter gender: ");
		scanf(" %[^\n]%*c",gender);
		
		fp1=fopen("project_files/User_datatemp.txt","w");
		fp2=fopen("project_files/User_data.txt","r");
		while(fgets(readline, sizeof(readline), fp2)!=NULL)
		{
			fprintf(fp1,"%s",readline);
		}
		fclose(fp1);
		fclose(fp2);
		fp2=fopen("project_files/User_datatemp.txt","r");
		fp1=fopen("project_files/User_data.txt","w");
		while(fgets(readline, sizeof(readline), fp2)!=NULL)
		{
			fprintf(fp1,"%s",readline);
		}
		fprintf(fp1,"\n%s %s %s %s %s",usrname,passwd,name,contact,gender);
		
		printf("\n\t\t   Account set-up successful\n");
		
	}
	else
	{
		printf("\t\t   Username taken\n");
	}
	fclose(fp1);
	fclose(fp2);
	printf("\n\t\tEnter anything to return to main menu\n\t\t");
	scanf(" %s",&c);
}







int userpage(char usracc[])
{
	titlebar();
	char uname[50];
	int logout=0;
	printf("\n\t\t\t\t                    |  User Home Page  |\n\n");
	strcpy(uname,strdata(usracc,2));
	strcpy(uname,Replace_tilde_by_space(uname));
	//printf("%s\n",strdata(usracc,0));
	printf("\n\t\t\t\t        Hello %s ! Welcome to your User Account\n\n",uname);
	
	int choice,invalid=1;
	//titlebar();
	printf("\n\t\t\t\t                           Menu \n\n");
	printf("\n\t\t\t\t                1. Account Info and settings (coming soon)\n");
	printf("\n\t\t\t\t                  2. View Available Flights\n");
	printf("\n\t\t\t\t                      3. Book Tickets\n");
	printf("\n\t\t\t\t                      4. View Tickets\n");
	printf("\n\t\t\t\t                        5. Log out\n\n");
	while(invalid)	
	{
		printf("\t\tEnter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: //viewaccout(1,usracc);   //function is buggy
					invalid=0;
					break;
					
			case 2: viewflights(1,usracc);
					invalid=0;
					break;
			case 3: booktickets(usracc);
					invalid=0;
					break;
			
			case 4: view_tickets(usracc);
					invalid=0;
					break;
			
			case 5: //signup();
					logout=1;
					invalid=0;
					titlebar();
					printf("\n\t\t\t\tSee you again %s ! You have now logged out of your User Account\n\n",uname);
	
					break;
			default: printf("\n\t\t**Please enter a valid option**\n");
					break;
		}
		//if(choice==3)
			//break;
	}
	return logout;
	
}



int adminpage(char admacc[])
{
	titlebar();
	char aname[50];
	int logout=0;
	printf("\n\t\t\t\t                    |  Admin Home Page  |\n\n");
	strcpy(aname,strdata(admacc,2));
	strcpy(aname,Replace_tilde_by_space(aname));
	//printf("%s\n",strdata(usracc,0));
	printf("\n\t\t\t\t       Hello %s ! Welcome to your Admin Account\n\n",aname);
	
	int choice,invalid=1;
	//titlebar();
	printf("\n\t\t\t\t                           Menu \n\n");
	printf("\n\t\t\t\t                1. Account Info and settings (coming soon)\n");
	printf("\n\t\t\t\t                 2. View Available Flights\n");
	printf("\n\t\t\t\t                     3. Manage Flights\n");
	printf("\n\t\t\t\t                        4. Log out\n\n");
	while(invalid)	
	{
		printf("\t\tEnter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: //viewaccout(0,admacc);  //function is buggy
					invalid=0;
					break;
					
			case 2: viewflights(0,admacc);
					invalid=0;
					break;
			case 3: manageflights(admacc);
					invalid=0;
					break;
			
			case 4: //signup();
					logout=1;
					invalid=0;
					titlebar();
					printf("\n\t\t\t\tSee you again %s ! You have now logged out of your Admin Account\n\n",aname);
	
					break;
			default: printf("\n\t\t**Please enter a valid option**\n");
					break;
		}
		//if(choice==3)
			//break;
	}
	return logout;
	
}


int viewaccout(int n, char acc[])
{
	titlebar();
	char readline[100],username[50],name[70],gender[3],contactno[15],str[10];;
	strcpy(username,strdata(acc,0));
	FILE *fp1;
	if(n==1)  //user
	{
		printf("\n\t\t\t\t                  |  Your User Account  |\n\n");
		printf("\n\t\t__________________________________________________________________________________________\n");
		fp1=fopen("project_files/User_data.txt","r");
		while(fgets(readline, sizeof(readline), fp1)!=NULL)
		{
			if(strcmp(username,strdata(readline,0))==0)
			{
				strcpy(name,strdata(readline,2));
				strcpy(name,Replace_tilde_by_space(name));
				strcpy(contactno,strdata(readline,3));
				strcpy(gender,strdata(readline,4));
				break;
			}			
		}
		
		printf("\n\n\t\t   Name: %s",name);
		printf("\n\n\t\t   Contact Number: %s",contactno);
		printf("\n\n\t\t   Gender: %s",gender);
		printf("\n\n\t\t__________________________________________________________________________________________\n");
		fclose(fp1);
		printf("\t\tEnter anything to return to User Home Page\n\t\t");
	}
	else      //admin
	{
		printf("\n\t\t\t\t                 |  Your Admin Account  |\n\n");
		printf("\n\t\t__________________________________________________________________________________________\n");
		fp1=fopen("project_files/Admin_data.txt","r");
		while(fgets(readline, sizeof(readline), fp1)!=NULL)
		{
			if(strcmp(username,strdata(readline,0))==0)
			{
				strcpy(name,strdata(readline,2));
				strcpy(name,Replace_tilde_by_space(name));
				strcpy(contactno,strdata(readline,3));
				strcpy(gender,strdata(readline,4));
				break;
			}			
		}
		
		printf("\n\n\t\t   Name: %s",name);
		printf("\n\n\t\t   Contact Number: %s",contactno);
		printf("\n\n\t\t   Gender: %s",gender);
		printf("\n\n\t\t__________________________________________________________________________________________\n");
		
		fclose(fp1);
		printf("\t\tEnter anything to return to Admin Home Page\n\t\t");
	}
	
	scanf(" %[^\n]%*c",&str);
	return 0;
}




void viewflights(int n, char acc[])
{
	titlebar();
	char sourceinp[15],destninp[15],readline[100],tempstr[100];
	int num=0;
	printf("\t\t\t\t  Please enter the following details to view avaiable flights:\n");
	printf("\n\t\t\t\t                      Source:");
	scanf(" %[^\n]%*c", &sourceinp);
	printf("\n\t\t\t\t                    Destination:");
	scanf(" %[^\n]%*c", &destninp);
		
	printf("\n\t\t\t\t                List of available flights:\n\t");
	FILE *fp2=fopen("project_files/flightdata.txt","r") ;
	while( !feof(fp2)) 
	{
		fgets(readline, sizeof(readline), fp2);
		strcpy(tempstr,readline);
		if( strcmp(strdata(tempstr,0),sourceinp)==0 && strcmp(strdata(tempstr,1),destninp)==0 ) 
		{
			num++;
			printf("\n");
			strcpy(tempstr,strdata(readline,2));
			strcpy(tempstr,Replace_tilde_by_space(tempstr));
			printf("\t %d. %s",num,tempstr);
			strcpy(tempstr,strdata(readline,3));
			printf(" Flight No. %s",tempstr);
			strcpy(tempstr,strdata(readline,0));
			printf("   Source: %s",tempstr);
			strcpy(tempstr,strdata(readline,1));
			printf("  Destination: %s",tempstr);
			strcpy(tempstr,strdata(readline,4));
			printf("   Departure Time: %s",tempstr);
			strcpy(tempstr,strdata(readline,5));
			printf("   Arrival Time: %s\n",tempstr);
			strcpy(tempstr,strdata(readline,6));
			printf("\t\t\t\t  Economy: \u20B9 %s",tempstr);
			strcpy(tempstr,strdata(readline,7));
			printf("  Business: \u20B9 %s\n",tempstr);
			
		}
	}		
	if(num==0)
	{
		printf("\t\t\t\t                 There are no matching flights");
		if(n==1)
		{
			printf("\n\t\t\t\t        Enter anything to return to User Home Page");
			scanf(" %[^\n]%*c", &tempstr);
			//if(tempstr[0]=='Y')
				//booktickets(acc);
		}
		else
		{
			printf("\n\t\t\t\t         Enter anything to return to Admin Home Page: ");
			scanf(" %[^\n]%*c", &tempstr);
		}
	}
	else
	{
		
		if(n==1)
		{
			printf("\n\t\t\t\t Enter 'Y' to proceed to booking page, anything else to return to User Home Page");
			scanf(" %[^\n]%*c", &tempstr);
			if(tempstr[0]=='Y')
				booktickets(acc);
		}
		else
		{
			printf("\n\t\t\t\t         Enter anything to return to Admin Home Page: ");
			scanf(" %[^\n]%*c", &tempstr);
		}
	}
		//break;
	
}



void booktickets(char usracc[])
{
	while(true)
	{
		FILE *fp1 ;
		//FILE *fp2=fopen("project_files/flightdata.txt","r") ;
		titlebar();
		char sourceinp[15],destninp[15],flnoinp[6],readline[100],src[15],dstn[15],flno[6],artime[5],deptime[5],airline[15],tempstr[100],datestr[6];
		int avlbl=0,num=0,date,day,month,year;
		
		printf("\n\t\t\t\t                    |  Flight Booking  |\n\n");
		printf("\t\t      We now take bookings to and from the following locations(not all connections):\n");
		printf("\t\t\t\t                      1. Kolkata\n");
		printf("\t\t\t\t                      2. Delhi\n");
		printf("\t\t\t\t                      3. Pune\n");
		printf("\t\t\t\t                      4. Mumbai\n");
		printf("\t\t\t\t                      5. Chennai\n\n");
		printf("\t\t\t  Please enter the following details to proceed with your booking:\n");
		printf("\n\t\t\t\t                      Source:");
		scanf(" %[^\n]%*c", &sourceinp);
		printf("\n\t\t\t\t                    Destination:");
		scanf(" %[^\n]%*c", &destninp);
		while(true)
		{
			int valid=0;
			printf("\n\t\t\t\t            Date (Use the format DDMMYY):");
			scanf("%d",&date);
			day=date/10000;
			month=(date/100)%100;
			year=date%100;
			if(year>=21) //to check if date is valid or not
			{
				switch(month)
				{
					case 1:
					if(day<=31)
						valid=1;
					break;
					case 2:
					if(day<=28)
						valid=1;
					break;
					case 3:
					if(day<=31)
						valid=1;
					break;
					case 4:
					if(day<=30)
						valid=1;
					break;
					case 5:
					if(day<=31)
						valid=1;
					break;
					case 6:
					if(day<=30)
						valid=1;
					break;
					case 7:
					if(day<=31)
						valid=1;
					break;
					case 8:
					if(day<=31)
						valid=1;
					break;
					case 9:
					if(day<=30)
						valid=1;
					break;
					case 10:
					if(day<=31)
						valid=1;
					break;
					case 11:
					if(day<=30)
						valid=1;
					break;
					case 12:
					if(day<=31)
						valid=1;
					break;
					
				}
			}
			
			if(valid==1)
			{
				break;
			}
			else
			{
				printf("\n\n\t\t\t\t         Invalid date. Please enter a valid date.");
			}
		}
		sprintf(datestr, "%d", date);
		//printf("\nyou selected the date: %s .\n",datestr);
		
		printf("\n\t\t\t\t                List of available flights:\n\t");
		FILE *fp2=fopen("project_files/flightdata.txt","r") ;
		while( !feof(fp2)) 
		{
			fgets(readline, sizeof(readline), fp2);
			strcpy(tempstr,readline);
			if( strcmp(strdata(tempstr,0),sourceinp)==0 && strcmp(strdata(tempstr,1),destninp)==0 ) 
			{
				num++;
				printf("\n");
				strcpy(tempstr,strdata(readline,2));
				strcpy(tempstr,Replace_tilde_by_space(tempstr));
				printf("\t %d. %s",num,tempstr);
				strcpy(tempstr,strdata(readline,3));
				printf(" Flight No. %s",tempstr);
				strcpy(tempstr,strdata(readline,0));
				printf("   Source: %s",tempstr);
				strcpy(tempstr,strdata(readline,1));
				printf("  Destination: %s",tempstr);
				strcpy(tempstr,strdata(readline,4));
				printf("   Departure Time: %s",tempstr);
				strcpy(tempstr,strdata(readline,5));
				printf("   Arrival Time: %s\n",tempstr);
				avlbl=1;
			}	 
			//break;
		}
		FILE *fp3=fopen("project_files/flightdata.txt","r") ;
		if(avlbl==1)
		{
			avlbl=0;
			printf("\n\n\t\t\t\t               Choose the Flight No.: ");
			scanf(" %[^\n]%*c",&flnoinp);
			while(!feof(fp3))
			{
				fgets(readline, sizeof(readline), fp3);
				strcpy(tempstr,readline);
				if(strcmp(flnoinp,strdata(readline,3))==0)
				{
					char class[5];
					avlbl=1;  //valid flight no
					printf("\n\n\t\t\t\t             Enter 'E' for economy class seats\n\t\t\t\t             Enter 'B' for business class seats\n\n\t\t\t\t                 Enter: ");
					scanf("%[^\n]%*c",&class);
					class[1]='\0';
					if(class[0]!='E' && class[0]!='B')
					{
						printf("\n\n\t\t\t\t            Invalid entry");
					}
					else
					{
						int n1,n2,n3,n_taken=0,seats;
						char ticketprice[6];
						strcpy(ticketprice,((class[0]=='B')?strdata(readline,7):strdata(readline,6)));
						seats=(class[0]=='B')?50:150;
						fp1=fopen("project_files/bookings.txt","r") ;
						while(!feof(fp1)) //checks number of seats already taken
						{
							fgets(readline, sizeof(readline), fp1);
							strcpy(tempstr,readline);
							if(strcmp(flnoinp,strdata(tempstr,0))==0 && strcmp(datestr,strdata(tempstr,1))==0&& strcmp(class,strdata(tempstr,2))==0)
							{
								n_taken++;
							}
						}
						fclose(fp1);
						printf("\n\t\t\t\t          Available seats: %d / %d",(seats-n_taken),seats);
						printf("\n\n\t\t\t\t             Enter number of infants: ");
						scanf("%d",&n1);
						printf("\n\t\t\t\t             Enter number of children: ");
						scanf("%d",&n2);
						printf("\n\t\t\t\t             Enter number of adults: ");
						scanf("%d",&n3);
						
						if(n1+n2+n3+n_taken>seats)
						{
							printf("\n\n\t\t\t\t           Not enough seats!");
						}
						else
						{
							char name[70],gender[5],age[9],bookingref[20];
							int cost,totalamt;
							cost=string_to_integer(ticketprice);
							//printf("\n\n\t\t\t\t           cost of tckt %d -%s-\n",cost,ticketprice);
							printf("\n\n\t\t\t\t           Enter passenger details below\n");
							sprintf(tempstr, "%d", n_taken);
							strcpy(bookingref,flnoinp);
							strcat(bookingref,datestr);
							strcat(bookingref,tempstr);
							for(int i=0;i<n1;i++) //making the booking of infants
							{
								//char name[70],gender[5],age[9];
								printf("\n\n\t\t\t\t         Name of infant %d: ",(i+1));
								scanf(" %[^\n]%*c",&name);								
								strcpy(name,Replace_space_by_tilde(name));
								printf("\n\t\t\t\t         Gender(m/f/nb) of infant %d: ",(i+1));
								scanf(" %[^\n]%*c",&gender);
								printf("\n\t\t\t\t         Age of infant %d: ",(i+1));
								scanf("%[^\n]%*c",&age);
								fp1=fopen("project_files/bookings.txt","r") ;
								FILE *fp4=fopen("project_files/bookingbackup.txt","w") ;
								
								while(!feof(fp1))
								{
									fgets(readline, sizeof(readline), fp1);
									fprintf(fp4,"%s",readline);
								}
								//fprintf(fp4,"\n%s","does this work");
								fclose(fp1);
								fclose(fp4);
								
								fp1=fopen("project_files/bookings.txt","w") ;
								fp4=fopen("project_files/bookingbackup.txt","r") ;
								while(!feof(fp4))
								{
									fgets(readline, sizeof(readline), fp4);
									fprintf(fp1,"%s",readline);
								}
								
								fprintf(fp1,"\n%s %s %s %s i %s %s %s %s ",flnoinp,datestr,class,strdata(usracc,0),name,gender,age,bookingref);
								fclose(fp1);
								fclose(fp4);
							}
							
							for(int i=0;i<n2;i++) //making the booking of children
							{
								//char name[70],gender[5],age[9];
								printf("\n\n\t\t\t\t         Name of child %d: ",(i+1));
								scanf(" %[^\n]%*c",&name);
								strcpy(name,Replace_space_by_tilde(name));
								printf("\n\t\t\t\t         Gender(m/f/nb) of child %d: ",(i+1));
								scanf(" %[^\n]%*c",&gender);
								printf("\n\t\t\t\t         Age of child %d: ",(i+1));
								scanf("%[^\n]%*c",&age);
								fp1=fopen("project_files/bookings.txt","r") ;
								FILE *fp4=fopen("project_files/bookingbackup.txt","w") ;
								
								while(!feof(fp1))
								{
									fgets(readline, sizeof(readline), fp1);
									fprintf(fp4,"%s",readline);
								}
								//fprintf(fp4,"\n%s","does this work");
								fclose(fp1);
								fclose(fp4);
								
								fp1=fopen("project_files/bookings.txt","w") ;
								fp4=fopen("project_files/bookingbackup.txt","r") ;
								while(!feof(fp4))
								{
									fgets(readline, sizeof(readline), fp4);
									fprintf(fp1,"%s",readline);
								}
								
								fprintf(fp1,"\n%s %s %s %s c %s %s %s %s ",flnoinp,datestr,class,strdata(usracc,0),name,gender,age,bookingref);
								fclose(fp1);
								fclose(fp4);
							}
							
							for(int i=0;i<n3;i++) //making the booking of adults
							{
								//char name[70],gender[5],age[9];
								printf("\n\n\t\t\t\t         Name of adult %d: ",(i+1));
								scanf(" %[^\n]%*c",&name);
								strcpy(name,Replace_space_by_tilde(name));
								printf("\n\t\t\t\t         Gender(m/f/nb) of adult %d: ",(i+1));
								scanf(" %[^\n]%*c",&gender);
								printf("\n\t\t\t\t         Age of adult %d: ",(i+1));
								scanf("%[^\n]%*c",&age);
								fp1=fopen("project_files/bookings.txt","r") ;
								FILE *fp4=fopen("project_files/bookingbackup.txt","w") ;
								
								while(!feof(fp1))
								{
									fgets(readline, sizeof(readline), fp1);
									fprintf(fp4,"%s",readline);
								}
								//fprintf(fp4,"\n%s","does this work");
								fclose(fp1);
								fclose(fp4);
								
								fp1=fopen("project_files/bookings.txt","w") ;
								fp4=fopen("project_files/bookingbackup.txt","r") ;
								while(!feof(fp4))
								{
									fgets(readline, sizeof(readline), fp4);
									fprintf(fp1,"%s",readline);
								}
								
								fprintf(fp1,"\n%s %s %s %s a %s %s %s %s ",flnoinp,datestr,class,strdata(usracc,0),name,gender,age,bookingref);
								fclose(fp1);
								fclose(fp4);
							}
							totalamt= n1*((cost*50)/100) + n2*((cost*75)/100) + cost*n3;
							printf("\n\n\t\t\t\t           Flight booked successfully!");
							printf("\n\t\t\t\t   Your booking reference is: %s",bookingref);
							printf("\n\t\t\t\t         Total amount to pay: \u20B9 %d",totalamt);
							printf("\n\n\t\t\t\t           Enter 'Y' to see the bill. Enter anything else to complete booking.");
							char ch[5];
							scanf("%s",&ch);
							if(ch[0]=='Y')
								viewbill(bookingref,n1,n2,n3,cost);
						}
					}
					
				}
			}
			if(avlbl==0)
			{
				printf("\n\n\t\t\t\t           Invalid Flight Number");
			}
		}
		else
		{
			printf("\t\t\t\t         There are no matching flights");
		}
		char ch[5];
		printf("\n\n\t\t   Do you wish to book again? Enter Y, or enter anything else to return to the User Home Page: ");
		scanf("%s",&ch);
		if(ch[0]!='Y')
			break;
		//fclose(fp1);
		fclose(fp2);
		fclose(fp3);
	}
	
}



void view_tickets(char usracc[])
{
	titlebar();
	printf("\n\t\t\t\t                    |  View Tickets  |\n\n");
	char bookingref[20],class[20],date[9],readline[200],str[200],flno[6],usrname[50],bookings[200],temp1[20],temp2[20];
	strcpy(usrname,strdata(usracc,0));
	FILE *fp1=fopen("project_files/bookings.txt","r");
	int i=0,tickets=0;
	while(fgets(readline, sizeof(readline), fp1)!=NULL)
	{
		if(strcmp(usrname,strdata(readline,3))==0)
		{
			tickets++;
			strcpy(temp1,strdata(readline,8));
			strcat(bookings,temp1);
			strcat(bookings," ");
			//if(i>0 && strcmp(strdata(readline,8),strdata(bookings,i-1))==0)
		}
	}
	bookings[0]=' ';
	if(tickets>0)
	{
		printf("\n\n\t\t\t\t      Your avaiable booking reference codes: ");
		strcpy(temp1,strdata(bookings,1));
		printf("\n\n\t\t\t\t                %s",temp1);
		for(i=1;i<tickets;i++)
		{
			strcpy(temp1,strdata(bookings,i+1));
			strcpy(temp2,strdata(bookings,i));
			if(strcmp(temp1,temp2)!=0)
				printf("\n\t\t\t\t                %s",temp1);
		}
		
		//printf("\n%s",bookings);
		
		printf("\n\n\t\t\t\t      Enter the Booking Reference Code: ");
		scanf(" %[^\n]%*c",&bookingref);
		
		//FILE *fp1=fopen("project_files/bookings.txt","r");
		int valid=0;
		//printf("testing2");
		fp1=fopen("project_files/bookings.txt","r");
		while(!feof(fp1))
		{
			fgets(readline, sizeof(readline), fp1);
			//printf("testing2\n");
			if(strcmp(bookingref,strdata(readline,8))==0 && strcmp(usrname,strdata(readline,3))==0)
			{
				//printf("good\n");
				strcpy(str,readline);
				valid=1;
				break;
			}
		}
		fclose(fp1);
		//printf("testing");
		//scanf(" %[^\n]%*c",&date);
		if(valid==1)
		{
			if(checkcancel(str))
			{
				titlebar();
				printf("\n\t\t\t\t                    |  Your Ticket  |\n\n");
				strcpy(date,strdata(str,1));
				char day[3]={date[0],date[1]},month[3]={date[2],date[3]},year[3]={date[4],date[5]};
				char name[50],gender[4],age[5],deptime[6],arrtime[6],readline1[200],str1[100],flno[9],source[30],destn[30],airln[30];
				
				strcpy(class,strdata(str,2));
				strcpy(flno,strdata(str,0));
				strcpy(usrname,strdata(str,3));
				
				FILE *fp2=fopen("project_files/flightdata.txt","r");
				while(fgets(readline1, sizeof(readline1), fp2)!=NULL)
				{
					if(strcmp(flno,strdata(readline1,3))==0)
					{
						strcpy(str1,readline1);
						break;
					}
				}
				fclose(fp2);
				strcpy(deptime,strdata(str1,4));
				strcpy(arrtime,strdata(str1,5));
				strcpy(source,strdata(str1,0));
				strcpy(destn,strdata(str1,1));
				strcpy(airln,strdata(str1,2));
				strcpy(airln,Replace_tilde_by_space(airln));
				
				strcpy(class,(class[0]=='E')?"Economy":"Business");
				//printf(" %s\n",bookingref);
				printf("\t\t%s    Dep: %s   Arr: %s   Booking Reference: %s",airln,source,destn,bookingref);
				printf("\n\t\tFlying: %s   Date: %s/%s/%s    Dep. time: %s    Arr. time: %s \n",class,day,month,year,deptime,arrtime);
				printf("\t\t__________________________________________________________________________________________\n");
				printf("\n\t\tPassenger type      Name of passenger              Gender             Age       \n");
				
				FILE *fp5=fopen("project_files/bookings.txt","r");
				while(fgets(readline, sizeof(readline), fp5)!=NULL)
				{
					
					if(strcmp(bookingref,strdata(readline,8))==0)
					{
						strcpy(str1,readline);
						char type[8];
						strcpy(name,strdata(str1,5));
						strcpy(name,Replace_tilde_by_space(name));
						strcpy(gender,strdata(str1,6));
						strcpy(age,strdata(str1,7));
						//printf("this works?\n");
						strcpy(type,(strcmp(strdata(readline,4),"i")==0?"Infant":((strcmp(strdata(readline,4),"c")==0)?"Child ":"Adult ")));
						//if()
						//{}
						printf("\t\t %s              %-20s             %-2s                %s \n",type,name,gender,age);
					}
				}
				fclose(fp5);
				printf("\n\t\t__________________________________________________________________________________________\n");
				
				
			}
			else
			{
				printf("\n\t\t\t\t  Your flight has been cancelled. Please contact the airline to process your refund");
			}
		}
		else
		{
			printf("\n\t\t\t\t                      Invalid reference code");
		}
	}
	else
	{
		printf("\n\t\t\t\t   You do not have any bookings currently");
	}
	printf("\n\n\t\t\t\t   Enter anything to return to the User Home Page: ");
	scanf(" %[^\n]%*c",&str);
}

void manageflights(char admacc[])
{
	while(true)
	{
		titlebar();
		int choice,valid=0;
		printf("\n\t\t\t\t                    |  Manage Flights  |\n\n");
		printf("\t\t\t\t                         Admin Actions\n");
		printf("\t\t\t\t                      1. Add a new Flight\n");
		printf("\t\t\t\t                      2. Remove a Flight\n");
		printf("\t\t\t\t                      3. Modify Flight Details\n");
		while(valid==0)
		{
			printf("\n\t\t\t\t                         Enter your choice:");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1: addflight(admacc);
					valid=1;
					break;
				
				case 2: removeflight(admacc);
					valid=1;
					break;
				
				case 3: modifyflight(admacc);
					valid=1;
					break;
				
				default:
					printf("\n\t\t\t\t                         Invalid input");
					break;
			}
		}
		char ch[5];
		printf("\n\n\t\t   Do you wish to perform more actions?\n\n\t\t    Enter Y, or enter anything else to return to the Admin Home Page: ");
		scanf("%s",&ch);
		if(ch[0]!='Y')
			break;
	}
}


void viewbill(char bookingref[],int n1,int n2,int n3,int cost)
{
	titlebar();
	printf("\n\t\t\t\t                         |  Bill  |\n\n");
	printf("\t\tBooking Reference: %s\n",bookingref);
	printf("\t\t__________________________________________________________________________________________\n");
	printf("\n\t\tPassenger type         No. of passengers          Cost per seat         Total cost\n");
	if(n1>0)
	{
		printf("\n\t\tInfant                        %d                      \u20B9 %d               \u20B9 %d",n1,((cost*50)/100),n1*((cost*50)/100));
	}
	if(n2>0)
	{
		printf("\n\t\t Child                        %d                      \u20B9 %d               \u20B9 %d",n2,((cost*75)/100),n2*((cost*75)/100));
	}
	if(n3>0)
	{
		printf("\n\t\t Adult                        %d                      \u20B9 %d               \u20B9 %d",n3,cost,n3*cost);
	}
	printf("\n\t\t__________________________________________________________________________________________\n");
	printf("\n\t\t                                                      Total amount to pay: \u20B9 %d",(n1*((cost*50)/100) + n2*((cost*75)/100) + cost*n3));
}

void titlebar()
{
	system("cls");
	//printf("\e[1;1H\e[2J");
	printf("\t\t==========================================================================================\n");
	printf("\n\t\t\t\t                       BOOK MY TRIP\n");
	printf("\n\t\t\t\t              The Flight Reservation System!\n");
	printf("\t\t==========================================================================================\n\n");
}


void addflight(char admacc[])
{
	char input[70],str[200],readline[100];
	
	printf("\n\t\t\t\t                         Enter Source:");
	scanf(" %[^\n]%*c",&input);
	strcpy(str,input);
	strcat(str," ");
	
	printf("\n\t\t\t\t                         Enter Destination:");
	scanf(" %[^\n]%*c",&input);
	strcat(str,input);
	strcat(str," ");
	
	printf("\n\t\t\t\t                         Enter Airline Name:");
	scanf(" %[^\n]%*c",&input);
	strcat(str,input);
	strcpy(str,Replace_space_by_tilde(str));
	strcat(str," ");
	
	printf("\n\t\t\t\t                         Enter Flight No.:");
	scanf(" %[^\n]%*c",&input);
	strcat(str,input);
	strcat(str," ");
	
	printf("\n\t\t\t\t                         Enter Departure Time:");
	scanf(" %[^\n]%*c",&input);
	strcat(str,input);
	strcat(str," ");
	
	printf("\n\t\t\t\t                         Enter Arrival Time:");
	scanf(" %[^\n]%*c",&input);
	strcat(str,input);
	strcat(str," ");
	
	printf("\n\t\t\t\t                         Enter Economy class ticket price:");
	scanf(" %[^\n]%*c",&input);
	strcat(str,input);
	strcat(str," ");
	
	printf("\n\t\t\t\t                         Enter Business class ticket price:");
	scanf(" %[^\n]%*c",&input);
	strcat(str,input);
	strcat(str," ");
	
	
	FILE *fp1=fopen("project_files/flightdata.txt","r") ;
	FILE *fp4=fopen("project_files/flightdatatemp.txt","w") ;
	
	while(!feof(fp1))
	{
		fgets(readline, sizeof(readline), fp1);
		fprintf(fp4,"%s",readline);
	}
	//fprintf(fp4,"\n%s","does this work");
	fclose(fp1);
	fclose(fp4);
	
	fp1=fopen("project_files/flightdata.txt","w") ;
	fp4=fopen("project_files/flightdatatemp.txt","r") ;
	while(!feof(fp4))
	{
		fgets(readline, sizeof(readline), fp4);
		fprintf(fp1,"%s",readline);
	}
	
	fprintf(fp1,"\n%s",str);
	fclose(fp1);
	fclose(fp4);
	
}



void removeflight(char admacc[])
{
	char sourceinp[15],destninp[15],flnoinp[6],readline[100],tempstr[100];
	int avlbl=0,num=0;
	printf("\n\t\t\t\t                      Source:");
	scanf(" %[^\n]%*c", &sourceinp);
	printf("\n\t\t\t\t                    Destination:");
	scanf(" %[^\n]%*c", &destninp);
	printf("\n\t\t\t\t                  Scheduled flights:\n\t");
	FILE *fp2=fopen("project_files/flightdata.txt","r") ;
	while( !feof(fp2)) 
	{
		fgets(readline, sizeof(readline), fp2);
		strcpy(tempstr,readline);
		if( strcmp(strdata(tempstr,0),sourceinp)==0 && strcmp(strdata(tempstr,1),destninp)==0 ) 
		{
			num++;
			printf("\n");
			strcpy(tempstr,strdata(readline,2));
			strcpy(tempstr,Replace_tilde_by_space(tempstr));
			printf("\t %d. %s",num,tempstr);
			strcpy(tempstr,strdata(readline,3));
			printf(" Flight No. %s",tempstr);
			strcpy(tempstr,strdata(readline,0));
			printf("   Source: %s",tempstr);
			strcpy(tempstr,strdata(readline,1));
			printf("  Destination: %s",tempstr);
			strcpy(tempstr,strdata(readline,4));
			printf("   Departure Time: %s",tempstr);
			strcpy(tempstr,strdata(readline,5));
			printf("   Arrival Time: %s\n",tempstr);
			avlbl=1;
		}
	}
	fp2=fopen("project_files/flightdata.txt","r") ;
	if(avlbl==1)
	{
		avlbl=0;
		printf("\n\n\t\t\t\t               Choose the Flight No.: ");
		scanf(" %[^\n]%*c",&flnoinp);
		while(!feof(fp2))
		{
			fgets(readline, sizeof(readline), fp2);
			strcpy(tempstr,readline);
			if(strcmp(flnoinp,strdata(readline,3))==0)
			{
				avlbl=1;
				break;
			}
		}
		fclose(fp2);
		if(avlbl==1)
		{
			FILE *fp1=fopen("project_files/flightdata.txt","r") ;
			FILE *fp4=fopen("project_files/flightdatatemp.txt","w") ;
			
			while(!feof(fp1))
			{
				fgets(readline, sizeof(readline), fp1);
				if(strcmp(flnoinp,strdata(readline,3))!=0 && strcmp(readline,"")!=0)
					fprintf(fp4,"%s",readline);
			}
			//fprintf(fp4,"\n%s","does this work");
			fclose(fp1);
			fclose(fp4);
			
			fp1=fopen("project_files/flightdata.txt","w") ;
			fp4=fopen("project_files/flightdatatemp.txt","r") ;
			while(fgets(readline, sizeof(readline), fp4)!=NULL)
			{
				//fgets(readline, sizeof(readline), fp5);
				//printf("%s\n",readline);
				if(strcmp(readline,"")!=0)
					fprintf(fp1,"%s",readline);
			}
			
			fclose(fp1);
			fclose(fp4);
			//flight removed from flight database
			
			
			fp1=fopen("project_files/bookings.txt","r");
			fp2=fopen("project_files/bookingbackup.txt","w");
			while(fgets(readline, sizeof(readline), fp1)!=NULL)
			{
				//fgets(readline, sizeof(readline), fp1);
				fprintf(fp2,"%s",readline);
			}
			fclose(fp1);
			fclose(fp2);
			
			fp1=fopen("project_files/bookings.txt","w");
			fp2=fopen("project_files/bookingbackup.txt","r");
			while(fgets(readline, sizeof(readline), fp2)!=NULL)
			{
				strcpy(tempstr,readline);
				if(strcmp(flnoinp,strdata(readline,0))==0)
				{
					char temp[100]="*";
					strcat(temp,tempstr);
					//tempstr[sizeof(tempstr)/sizeof(char) - 2]='*';
					//printf("%d",sizeof(tempstr)/sizeof(char) - 2);
					//strcat(tempstr," * \n");					//flagging all the existing bookings of this cancelled flight.
					//strcpy(tempstr,omitlinebreak(tempstr));	
					fprintf(fp1,"%s",temp);
				}
				else
				{
					fprintf(fp1,"%s",readline);
				}
			}
			fclose(fp1);
			fclose(fp2);
			
			printf("\t\t\t\t                  Flight removed\n");
		}
		else
		{
			printf("\t\t\t\t         There are no matching flights");
		}
	}
	else
	{
		printf("\t\t\t\t         There are no matching flights");
	}
	
		
		//break;
	
}



void modifyflight(char admacc[])
{
	char sourceinp[15],destninp[15],flnoinp[6],readline[100],tempstr[100];
	int avlbl=0,num=0,valid=0,choice;
	printf("\n\t\t\t\t                      Source:");
	scanf(" %[^\n]%*c", &sourceinp);
	printf("\n\t\t\t\t                    Destination:");
	scanf(" %[^\n]%*c", &destninp);
	printf("\n\t\t\t\t                  Scheduled flights:\n\t");
	FILE *fp2=fopen("project_files/flightdata.txt","r") ;
	while( !feof(fp2)) 
	{
		fgets(readline, sizeof(readline), fp2);
		strcpy(tempstr,readline);
		if( strcmp(strdata(tempstr,0),sourceinp)==0 && strcmp(strdata(tempstr,1),destninp)==0 ) 
		{
			num++;
			printf("\n");
			strcpy(tempstr,strdata(readline,2));
			strcpy(tempstr,Replace_tilde_by_space(tempstr));
			printf("\t %d. %s",num,tempstr);
			strcpy(tempstr,strdata(readline,3));
			printf(" Flight No. %s",tempstr);
			strcpy(tempstr,strdata(readline,0));
			printf("   Source: %s",tempstr);
			strcpy(tempstr,strdata(readline,1));
			printf("  Destination: %s",tempstr);
			strcpy(tempstr,strdata(readline,4));
			printf("   Departure Time: %s",tempstr);
			strcpy(tempstr,strdata(readline,5));
			printf("   Arrival Time: %s\n",tempstr);
			avlbl=1;
		}
	}
	fp2=fopen("project_files/flightdata.txt","r") ;
	if(avlbl==1)
	{
		avlbl=0;
		printf("\n\n\t\t\t\t               Choose the Flight No.: ");
		scanf(" %[^\n]%*c",&flnoinp);
		while(!feof(fp2))
		{
			fgets(readline, sizeof(readline), fp2);
			strcpy(tempstr,readline);
			if(strcmp(flnoinp,strdata(readline,3))==0)
			{
				avlbl=1;
				break;
			}
		}
		fclose(fp2);
		if(avlbl==1)
		{
			printf("\t\t\t\t           Choose the field you wish to modify\n");
			printf("\t\t\t\t                      1. Dep. time\n");
			printf("\t\t\t\t                      2. Arr. time\n");
			printf("\t\t\t\t                      3  Ticket price: Economy\n");
			printf("\t\t\t\t                      4. Ticket price: Business\n");
			
			printf("\n\t\t\t\t                         Enter your choice:");
			scanf("%d",&choice);
			
			switch(choice)
			{
				case 1: valid=1;
						printf("\n\t\t\t\t               Enter the new Dep. time:");
						break;
				
				case 2: valid=1;
						printf("\n\t\t\t\t               Enter the new Arr. time:");
						break;
				
				case 3: valid=1;
						printf("\n\t\t\t\t               Enter the new Ticket price (Economy):");
						break;
				
				case 4: valid=1;
						printf("\n\t\t\t\t               Enter the new Ticket price (Business):");
						break;
			}
			if(valid==1)
			{
				char str[10];
				char deptime[6],arrtime[6],flno[9],source[30],destn[30],airln[30],econ_cost[10],busi_cost[10];
				scanf(" %[^\n]%*c",&str); //input
				
				FILE *fp1=fopen("project_files/flightdata.txt","r") ;
				FILE *fp4=fopen("project_files/flightdatatemp.txt","w") ;
				
				while(!feof(fp1))
				{
					fgets(readline, sizeof(readline), fp1);
					if(strcmp(flnoinp,strdata(readline,3))!=0 && strcmp(readline,"")!=0)
						fprintf(fp4,"%s",readline);
					else
					{
						strcpy(source,strdata(readline,0));
						strcpy(destn,strdata(readline,1));
						strcpy(airln,strdata(readline,2));
						strcpy(flno,strdata(readline,3));
						strcpy(deptime,strdata(readline,4));
						strcpy(arrtime,strdata(readline,5));
						strcpy(econ_cost,strdata(readline,6));
						strcpy(busi_cost,strdata(readline,7));
						//fprintf(fp4,"%s %s %s %s %s %s %s \n",source,destn,airln,flno,str,arrtime,econ_cost,busi_cost);
						switch(choice)
						{
							case 1: fprintf(fp4,"%s %s %s %s %s %s %s \n",source,destn,airln,flno,str,arrtime,econ_cost,busi_cost);
									break;
							
							case 2: fprintf(fp4,"%s %s %s %s %s %s %s \n",source,destn,airln,flno,deptime,str,econ_cost,busi_cost);
									break;
							
							case 3: fprintf(fp4,"%s %s %s %s %s %s %s \n",source,destn,airln,flno,deptime,arrtime,str,busi_cost);
									break;
							
							case 4: fprintf(fp4,"%s %s %s %s %s %s %s \n",source,destn,airln,flno,deptime,arrtime,econ_cost,str);
									break;
						}
					}
				}
				//fprintf(fp4,"\n%s","does this work");
				fclose(fp1);
				fclose(fp4);
				
				fp1=fopen("project_files/flightdata.txt","w") ;
				fp4=fopen("project_files/flightdatatemp.txt","r") ;
				while(!feof(fp4))
				{
					fgets(readline, sizeof(readline), fp4);
					if(readline!="")
						fprintf(fp1,"%s",readline);
				}
				
				fclose(fp1);
				fclose(fp4);
				printf("\n\t\t\t\t                  Flight details successfully modified\n");
			}
		}
		else
		{
			printf("\t\t\t\t         There are no matching flights");
		}
	}
	else
	{
		printf("\t\t\t\t         There are no matching flights");
	}
}




int checkcancel(char readline[])
{
	//int i=0;
	//while(readline[i]!='\0')
	//{
		//i++;
	//}
	//i--;
	if(readline[0]=='*')
		return 0;
	return 1;
}




char *strdata(char *s,int n)
{
	//printf("hello?");
	int spaces = 0, i,k=0;
	char *str;
    for(i = 0; s[i] != '\0'; ++i) 
	{
		//printf("%d",spaces);
		if(spaces==n)
		{
			while(s[i] != '\0'&&s[i] != ' ')
			{
				str[k++]=s[i++];
				//printf("%d\n",i);
			}
			str[k]='\0';
			break;
		}
		else
		{
			if(s[i] == ' ')
				++spaces;
		}
    }
	if(k==0)
	{
		printf("%d",spaces);
		return NULL;
	}
	return str;
}



char *omitlinebreak(char readline[])
{
	char *str;
	int i=0,k=0;
	while(readline[i]!='\0')
	{
		if(readline[i]!='\n')
		{
			str[k++]=readline[i];
		}
		i++;
	}
	str[k++]='\n';
	str[k]='\0';
	return str;
}




char *Replace_space_by_tilde(char *original) 
{

    int i, n = 1;
    for (i = 0; original[i] != '\0'; i++) {
        ++n;
    }

    char *s = (char *)malloc(n*sizeof(char));
    i = 0;
    do {
        if (original[i] != ' ')
            s[i] = original[i];
        else
            s[i] = '~';
        ++i;
    } while(i < n);

    return s;
}

char *Replace_tilde_by_space(char *original) 
{

    int i, n = 1;
    for (i = 0; original[i] != '\0'; i++) {
        ++n;
    }

    char *s = (char *)malloc(n*sizeof(char));
    i = 0;
    do {
        if (original[i] != '~')
            s[i] = original[i];
        else
            s[i] = ' ';
        ++i;
    } while(i < n);

    return s;
}

int string_to_integer(char *arr) 
{

    int i, j = 0, count = 0;
    for (i = 0; arr[i] != '\0'; i++) {
        count *= 10;
        j = arr[i]-'0';
        count += j;
    }
    return count;

}

/*
cd ..\..\msys64\usr\bin
gcc -o flightres flightres.c
flightres
1
Susmita
b
4
GL52651202220

*/