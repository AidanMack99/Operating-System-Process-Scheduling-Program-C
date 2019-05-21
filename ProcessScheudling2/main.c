
#include <stdlib.h>

#include <stdio.h>
// Prototypes

int showmenu(void);

int getChoice(void);

int selection(void);


int main()

{

int choice;

choice =showmenu();

printf("You have chosen Menu #%d\n", choice);

if(choice == 1)
{
     FCFS();
}

if (choice == 2)
{
    SJF();
}

if (choice == 3)
{

    RR();
}



printf("\n");



}


int showmenu()

{

printf("\n");

printf("1 First Come First Served (FCFS)\n");

printf("2 Shortest Job First (SJF)\n");

printf("3 Round Robin (RR)\n");

printf("4 Exit\n");

printf("\n");

return getChoice();

}


int getChoice()

{

int selection;

scanf("%d", &selection);

return selection;


}

int FCFS()
{
     int n,i,BT[50],WT[50],TAT[50],AT[50],CT[50];
    float AVWT=0, AVTAT=0;

    //entering processes
    printf("\nEnter the total number of process :");
    scanf("%d",&n);

    //entering burst times
    printf("\nEnter every process burst time :");
    for(i=0;i<n;i++)
    {
        printf("P[%d] :",i+1);
        scanf("%d",&BT[i]);
    }


    //entering arrival times
     printf("\nEnter every process arrival time :");
     for(i=0;i<n;i++)
    {
         printf("P[%d] :",i+1);
         scanf("%d",&AT[i]);
    }

    //first wait time always 0
     WT[0]=0;

     //first completion time = first burst time + first arrival time
     CT[0]=BT[0]+AT[0];

    //calculating completion time
     for(i=1;i<n;i++){
        CT[i]=CT[i-1]+BT[i];
     }

    //calculating results from data and printing
    printf("\nP#\tAT\tBT\tCT\tTAT\tWT");
    for(i=0;i<n;i++)
    {
        TAT[i]=CT[i]-AT[i];
        WT[i]=TAT[i]-BT[i];
        AVWT=AVWT+WT[i];
        AVTAT=AVTAT+TAT[i];
     printf("\nP[%d]\t%d\t%d\t%d\t%d\t%d",i+1,AT[i],BT[i],CT[i],TAT[i],WT[i]);
    }
    AVWT=AVWT/n;
    AVTAT=AVTAT/n;
    printf("\nAverage Waiting Time: %f",AVWT);
    printf("\nAverage Turnaround Time: %f", AVTAT);

    return 0;

    }



int SJF()
{
  int n, i, j, pc=0, temp, tn=0 ,c; //pc =processes completed //tn = current time
  int AT[10],BT[10],CT[10],WT[10],TAT[10],ta[10];
  float AVWT=0, AVTAT=0;

    //entering processes
    printf("\nEnter the total number of process :");
    scanf("%d",&n);

    //entering burst times
    printf("\nEnter every process burst time :");
    for(i=0;i<n;i++)
    {
        printf("P[%d] :",i+1);
        scanf("%d",&BT[i]);
    }

    //entering arrival times
     printf("\nEnter every process arrival time :");
     for(i=0;i<n;i++)
    {
         printf("P[%d] :",i+1);
         scanf("%d",&AT[i]);
    }


    // set all initial completion times to -1 //used to check if process has been completed
    // bt = ta
    for(i=0; i<n; i++)
   {
     CT[i] = -1;
     ta[i] = BT[i];
   }

   while(pc!=n)
   {
       c=0;
       for(i=0;i<n;i++)
       {
            if(CT[i]<0 && AT[i]<=tn) //checks if process has arrived
            {
                c++;
            }
       }

    if(c==0)
        tn++;
    else
    {
        temp = 0;
        while(CT[temp]>0) // checks if process has been completed
        {
            temp++;
        }

        for(j=temp+1; j<n;j++)
        {
            if(AT[j]<=tn && CT[j]<0 && BT[temp]>BT[j])//checks if process is shorter than the current shortest
                temp = j;

        }
        if(CT[temp]<0)
        {

            tn=tn+BT[temp]; //Current time + Burst time of process =  new current time
            BT[temp] = 0;
            CT[temp] =tn; //completion time of current process = current time
            TAT[temp] = CT[temp] - AT[temp];
            WT[temp] = TAT[temp]- ta[temp];
            AVWT=AVWT+WT[temp];
            AVTAT=AVTAT+TAT[temp];
            pc++; //next process
        }
    }

   }

   //Printing results
    printf("\nP#\tAT\tBT\tCT\tTAT\tWT");
    for(i=0;i<n;i++)
    {
     printf("\nP[%d]\t%d\t%d\t%d\t%d\t%d",i+1,AT[i],ta[i],CT[i],TAT[i],WT[i]);
    }
    AVWT=AVWT/n;
    AVTAT=AVTAT/n;
    printf("\nAverage Waiting Time: %f",AVWT);
    printf("\nAverage Turnaround Time: %f", AVTAT);

    return 0;


}


int RR(){
    int i,n,j,TQ,c,tn=0,flag = 0,pc=0;  //TQ = time quantum //tn = current time
    int AT[10],BT[10],CT[10],TAT[10],WT[10],rem_BT[10]; //rem_BT = temp array to keep track of remaining burst times
    float AVWT=0,AVTAT=0;

    //entering processes
    printf("\nEnter the total number of process :");
    scanf("%d",&n);

    //entering burst times
    printf("\nEnter every process burst time :");
    for(i=0;i<n;i++)
    {
        printf("P[%d] :",i+1);
        scanf("%d",&BT[i]);
    }

    //entering arrival times
     printf("\nEnter every process arrival time :");
     for(i=0;i<n;i++)
    {
         printf("P[%d] :",i+1);
         scanf("%d",&AT[i]);
    }

    //entering time quantum
    printf("\nEnter the Time Quantum :");
    scanf("&d",&TQ);


    for (int i = 0 ; i < n ; i++)
    {
        rem_BT[i] =  BT[i];
    }


    while(pc!=n)
    {
        flag = 1;

        for(i=0;i<n;i++)
        {
            if(rem_BT[i]>0)//checks if process has been completed
            {
                flag = 0;//process needs to be completed

                if(rem_BT[i]>TQ)
                {
                   tn= tn+TQ; // add time Quantum to current time

                   rem_BT[i]= rem_BT[i]-TQ;// subtract TQ from current process

                }
                else
                {
                    tn =tn+rem_BT[i]; // adds burst time of process to current time
                    CT[i]=CT[i]+rem_BT[i]; //sets completion time to remaining burst time
                    WT[i]=tn-BT[i]; //wait time calculation
                    rem_BT[i]=0; // process is completed

                    pc++; //next process
                }

            }
        }
        if(flag==1)
            break;
    }

    //calculating results from data and printing
    printf("\nP#\tAT\tBT\tCT\tTAT\tWT");
    for(i=0;i<n;i++)
    {
        TAT[i]=BT[i]+WT[i];
        AVWT=AVWT+WT[i];
        AVTAT=AVTAT+TAT[i];
     printf("\nP[%d]\t%d\t%d\t%d\t%d\t%d",i+1,AT[i],BT[i],CT[i],TAT[i],WT[i]);
    }
    AVWT=AVWT/n;
    AVTAT=AVTAT/n;
    printf("\nAverage Waiting Time: %f",AVWT);
    printf("\nAverage Turnaround Time: %f", AVTAT);


}




