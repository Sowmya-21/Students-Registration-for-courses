//first project.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

struct Subject
{
    char subId[10];
    char subName[20];
    int subCredits;
};

struct subjectList
{
    struct Subject subjectSub;
    struct subjectList* subjectList;
};

int validsem(int sem)
{
    if(sem<1 || sem>8)
    return 1;
    else
    return 0;
}

struct subjectList* createNode(struct Subject s)
{
    struct subjectList *nn=(struct subjectList *)malloc(sizeof(struct subjectList));
    nn->subjectSub=s;
    nn->subjectList=NULL;
    return nn;
}

void insert(struct subjectList **p,struct Subject s)
{
    struct subjectList *nn,*ptr;
    nn=createNode(s);
    ptr=*p;
    
    if(*p==NULL)
    {
        *p=nn;
    }
    else
    {
        while(ptr->subjectList!=NULL)
        {
            ptr=ptr->subjectList;
        }
        ptr->subjectList=nn;
    }
}

void display(struct subjectList *p)
{
    struct subjectList *temp;
    temp=p;
    if(temp==NULL)
    {
        printf("----Not Entered Yet----\n");
        return;
    }
    else
    {
        printf("Sub Id     Sub Name   Sub Credits\n");
        while(temp!=NULL)
      {
        printf("%-10s %-10s %-10d\n",temp->subjectSub.subId,temp->subjectSub.subName,temp->subjectSub.subCredits);
        temp=temp->subjectList;
      }
     
    }
}

int main()
{
    int sem,i;
    struct subjectList *b[8];
    char a;
    struct Subject s;
    for(i=0;i<8;i++)
    {
        b[i]=NULL;
    }
 do
  {
    do
     {
      printf("Enter the Semester for which you want to insert the subjects\n");
      scanf("%d",&sem);
      if(validsem(sem))
     {
        printf("Please Enter Sem No b/w 1 - 8\n");
     }
    }while(validsem(sem));
    for(i=0;i<7;i++)
    {
       printf("Enter the Subject %d Details\n",i+1);
       printf("Enter Subject Id,Name,Credits\n");
       scanf("%s %s %d",s.subId,s.subName,&s.subCredits);
       insert(&b[sem-1],s);
    }
    printf("Do you want to insert one more Sem subject details?(y/n)");
    scanf(" %c",&a);
   }while(a=='y');
   printf("Display the Entered Sem Details\n");
   for(i=0;i<8;i++)
   {
       printf("Semester %d Details\n",i+1);
       display(b[i]);
   }
    
}

//second project
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Subject
{
	char stdId[10];
	char stdName[20];
	int stdCredits;
};
struct subStack
{
	struct Subject sub[8];
	int totalCredits;
	int top;
};
struct Student
{
	char stName[20];
	char USN[20];
	int semNo;
	int scoredCredits;
	int pendingCredits;
	struct subStack subStack;
};
struct studentList
{
	struct Student student;
	struct studentList *next;
};

struct studentList *createNode(struct Student s)
{
	 struct studentList *nn=(struct studentList *)malloc(sizeof(struct studentList));
	 nn->student=s;
	 return nn;	
}

void insertStudentList(struct studentList **h,struct Student s)
{
    struct studentList *nn;
    struct studentList *temp=*h;
    nn=createNode(s);
    nn->next=NULL;
    if(*h==NULL)
    {
        *h=nn;
    }
    else
    {
	    while(temp->next!=NULL)
	    {
	        temp=temp->next;
	    }
	    temp->next=nn;
    }
}

void int_Stack(struct subStack *s,int pending_credits)
{
	s->top=-1;
	s->totalCredits=pending_credits;
}

void pushSubject(struct subStack *s,struct Subject sb)
{
    s->top++;
    s->totalCredits+=sb.stdCredits;
    s->sub[s->top]=sb;
}

void popSubject(struct subStack *s)
{
    s->top--;
}

void displaySubjectDetails(struct Subject s[])
{
	struct Subject *ptr;
	ptr=s;
	printf("%-10s %-10s %-s\n","Sub Id","Sub Name","Sub Credits");
	for(int i=0;i<8;i++)
	{
		printf("%-10s %-10s %d\n",ptr[i].stdId,ptr[i].stdName,ptr[i].stdCredits);
	}
}

int findSubject(struct Subject s[],char *sid)
{
    int i;
        for(i=0;i<8;i++)
		{
			if(!strcmp(sid,s[i].stdId))
			{
				return i;
			}
	        }
	return -1;
}

void displaySubject(struct subStack *ss)
{
	printf("%-10s %-10s %-s\n","Sub Id","Sub Name","Sub Credits");
	for(int i=0;i<=ss->top;i++)
		{
			printf("%-10s %-10s %-d\n",ss->sub[i].stdId,ss->sub[i].stdName,ss->sub[i].stdCredits);
		}
}

void displayStudent(struct studentList *sl)
{
    int i;
	struct studentList *temp;
	temp=sl;
	while(temp!=NULL)
	{
		printf("%-10s %-10s %-10s %-10s %-s\n","Stud Name","Stud USN","Semester","Sc credits","Pe credits");
		printf("%-10s %-12s %-10d %-10d %-d\n",temp->student.stName,temp->student.USN,temp->student.semNo,temp->student.scoredCredits,temp->student.pendingCredits);
	        printf("Selected Subjects are\n");
		printf("Sub Id     Sub Name   Sub Credits\n");
		for(i=0;i<=temp->student.subStack.top;i++)
		{
		    printf("%-10s %-10s %d\n",temp->student.subStack.sub[i].stdId,temp->student.subStack.sub[i].stdName,temp->student.subStack.sub[i].stdCredits);
		}
		printf("Total Credits after selection %d\n",temp->student.subStack.totalCredits);
		temp=temp->next;
	}
}

int validsem(int sem)
{
    if(sem>8)
    return 1;
    else
    return 0;
}

int main()
{
    char id[20],q[2],t[2],m[2];
    int a=0;
    struct subStack p;
    struct studentList *ptr=NULL;
    struct Student s;
    struct Subject b[8][8]={
	{{"MA1C01","MATHS1",5},{"PH1C01","PHYSICS",5},{"CV1C01","MECHANICS",5},{"ME1C01","MECHANICAL",5},{"EE1C01","ELECTRICAL",5},{"PH1L01","EPL",4},{"CM1L01","CHEMISTRY",4},{"ME1L01","GEP",4}},
    {{"MAC101","MATHS2",5},{"CH1C01","CHEMISTRY",5},{"CS","C-PROGRAMMING",5},{"EC1C01","ELECTRONICS",5},{"ME1C02","CAD",5},{"CH1L01","ECL",4},{"CS1L01","CCP",4},{"CV101","Digital Programming",5}},
	{{"MA3C01","MATHS3",5},{"CS3C03","DS",5},{"CS3C02","DE",5},{"CS3C03","CO",5},{"CS3C04","DMS",5},{"CS3C05","USP",5},{"CS3L01","DSL",4},{"CS3L02","DEL",4}},
	{{"MA4C03","MATHS4",5},{"CS4C01","ADA",5},{"CS02","SE",5},{"CS403","OOPS",5},{"CS4C04","FAFL",5},{"CS4C05","DCN",5},{"CS4L01","ADAL",4},{"CS4L02","OOPL",4}},
	{{"CS0407","SA",5},{"CS0413","OS",5},{"CS0414","DBMS",5},{"CS0512","SS",5},{"CS0424","ME",5},{"CS0425","MP",5},{"CS0106","MPL",4},{"CS0107","DBMS",4}},
	{{"CS0418","CN",5},{"CS0523","OOMD",5},{"CS0425","CD",5},{"CS0450","WTA",5},{"CS0426","DA",5},{"CS0427","ANDROID",5},{"CS0112","WTAL",4},{"CS0109","CNL",4}},
	{{"CS0445","DOS",5},{"CS0521","CNS",5},{"CS0422","PPAA",5},{"CS0522","E1",5},{"CS0523","E2",5},{"CS0524","E3",5},{"CS0524","E4",4},{"CS0524","E5",4}},
	{{"CS0501","CC",5},{"CS0502","E6",5},{"CS0503","E7",5},{"CS0110","SEMINAR",5},{"CS0602","PROJECT",5},{"CS0504","E8",4},{"CS0505","E9",4},{"CS0506","E10",4}}
  	  };
  	 do
        {
    	   s.scoredCredits=0,s.pendingCredits=0;
           printf("Enter the details to register for the Semester\n");
           printf("Student Name,USN,Semester\n");
           scanf("%s %s %d",s.stName,s.USN,&s.semNo);
           while(validsem(s.semNo))
		{
		    printf("Please Enter Sem No b/w 1-8\n");
	           scanf("%d",&s.semNo);
		}
		 if(s.semNo>1)
		 {
		 	printf("Enter the scored and pending credits\n");
        	       scanf("%d %d",&s.scoredCredits,&s.pendingCredits);
		 }
		int_Stack(&p,s.pendingCredits);
		printf("Select the required subjects for Semester %d from the below list\n",s.semNo);
		displaySubjectDetails(b[s.semNo-1]);
		do
            {
		 do
    	       {
                  a=0;
		  printf("Enter the Subject Id\n");
		  scanf("%s",id);
	          a=findSubject(b[s.semNo-1],id);
		   if(a==-1)
		   {
			  printf("Subject Not found, Plz Enter correct Sub Id!!\n");
		   }
	}while(a==-1);
	pushSubject(&p,b[s.semNo-1][a]);
	printf("Current total credits %d\n",p.totalCredits);
	printf("Confirm your selection!!(y/n)\n");
	scanf("%s",q);
	if(strcmp("y",q))
	{
		p.totalCredits-=b[s.semNo-1][a].stdCredits;
		popSubject(&p);
	}
	printf("Total credits after Confirmation %d\n",p.totalCredits);
	if(p.totalCredits>34)
	{
		printf("Crossed credits limits!!\n");
		printf(" Removed the recently added subject!!\n");
		p.totalCredits-=b[s.semNo-1][a].stdCredits;
		popSubject(&p);
		printf("Total credits after removing %d\n",p.totalCredits);
	}
	printf("Do you want stop the selection of subjects?(y/n)\n");
	scanf("%s",t);
	if(!strcmp(t,"y"))
	{
    	  if(p.totalCredits<20)
	  {
		printf("You didn't reach the credits target!!\n");
		printf("Please continue..\n");
		strcpy(t,"n");
	  }

       }
 
  }while(strcmp(t,"y"));
    printf("Selected Subjects are\n");
	displaySubject(&p);
	printf("Total Credits after selection %d\n",p.totalCredits);
	s.subStack=p;
	insertStudentList(&ptr,s);
	printf("Do you want to one more registration?(y/n)\n");
	scanf("%s",m);
}while(!strcmp(m,"y"));
printf("Student registration details:\n");
displayStudent(ptr);
return 0;
}

//third project
#include<stdio.h>
#include<stdlib.h>
struct Subject
{
	char stdId[10];
	char stdName[20];
	int stdCredits;
};
struct subQ
{
    struct Subject sub[8];
    int front;
    int rear;
};
struct subStatusQ
{
    char status[10];
    int front;
    int rear;
};
struct student
{
  char stName[15];
  char USN[15];
  int semNo;
  int scoredCredits;
  int scoredPending;
};
struct studentList
{
    struct student student;
    struct studentList *next;
};

int validsem(int sem)
{
    if(sem>8)
    return 1;
    else
    return 0;
}
int checksno(int k)
{
    if(k<1 || k>8)
    return 1;
    else
    return 0;
}

struct studentList *createNode(struct student s)
{
    return (struct studentList *)malloc(sizeof(struct studentList));
}

void insertStudentList(struct studentList **h,struct student s)
{
    struct studentList *nn;
    struct studentList *temp=*h;
    nn=createNode(s);
    nn->student=s;
    nn->next=NULL;
    if(*h==NULL)
    {
        *h=nn;
    }    
    else
    {
	    while(temp->next!=NULL)
	    {
	        temp=temp->next;
	    }     
	    temp->next=nn;
    }	
}
void displaySubjectDetails(struct Subject s[])
{
	struct Subject *ptr;
	ptr=s;
	printf("%-10s %-10s %-10s %-s\n","SNo","Sub Id","Sub Name","Sub Credits");
	for(int i=0;i<8;i++)
	{
		printf("%-10d %-10s %-10s %d\n",(i+1),ptr[i].stdId,ptr[i].stdName,ptr[i].stdCredits);
	}
}
void displayAttemptedSub(struct subQ *ss,struct subStatusQ *sq)
{
    printf("Sub Id     Sub Name   Sub Credits Sub Status\n");
    for(int i=ss->front;i<=ss->rear;i++)
    {
        printf("%-10s %-10s %-10d %c\n",ss->sub[i].stdId,ss->sub[i].stdName,ss->sub[i].stdCredits,sq->status[i]);
    }
}
void displayStudent(struct studentList *sl)
{
	struct studentList *temp;
	temp=sl;
	while(temp!=NULL)
	{
		printf("%-10s %-10s %-10s %-10s %-s\n","Stud Name","Stud USN","Semester","Sc credits","Pe credits");
		printf("%-10s %-10s %-10d %-10d %-d\n",temp->student.stName,temp->student.USN,temp->student.semNo,temp->student.scoredCredits,temp->student.scoredPending);
		temp=temp->next;
	}
}
void init_Q(struct subQ *s,struct subStatusQ *sq)
{
    s->front=s->rear=-1;
    sq->front=sq->rear=-1;
}
void insertStatusQ(struct subStatusQ *s,char c)
{
	if(s->front==-1)
	{
	    s->front=s->rear=0;
	}
	else
	{
	    s->rear++;
	}
    s->status[s->rear]=c;
}
struct Subject deleteSubjectQ(struct subQ *s)
{
  return s->sub[s->front++];  
}
char deleteStatusQ(struct subStatusQ *s)
{
   return s->status[s->front++]; 
}
void insertSubjectQ(struct subQ *s,struct Subject sb)
{
	if(s->front==-1)
	{
	    s->front=s->rear=0;
	}
	else
	{
	    s->rear++;
	}
    s->sub[s->rear]=sb;  
}

void creditCalculation(struct subQ *s,struct subStatusQ *sq,struct student *std)
{
    char g;
    struct Subject r;
    while(s->front<=s->rear)
   {
        r=deleteSubjectQ(s);
        g=deleteStatusQ(sq);
	   if(g=='P')
	   {
             std->scoredCredits+=r.stdCredits;
	   }
       else
       {
         std->scoredPending+=r.stdCredits;
       }
   }    
}


int main()
{
    char a,m;
    int k;
    struct subQ q;
    struct subStatusQ p;
    struct student s;
    struct studentList *ptr=NULL;
	struct Subject b[8][8]={
		{{"MA1C01","MATHS1",5},{"PH1C01","PHYSICS",5},{"CV1C01","MECHANICS",5},{"ME1C01","MECHANICAL",5},{"EE1C01","ELECTRICAL",5},{"PH1L01","EPL",4},{"CM1L01","CHEMISTRY",4},{"ME1L01","GEP",4}},
		{{"MAC101","MATHS2",5},{"CH1C01","CHEMISTRY",5},{"CS","C-PROGRAMMING",5},{"EC1C01","ELECTRONICS",5},{"ME1C02","CAD",5},{"CH1L01","ECL",4},{"CS1L01","CCP",4},{"CV101","Digital Programming",5}},
		{{"MA3C01","MATHS3",5},{"CS3C03","DS",5},{"CS3C02","DE",5},{"CS3C03","CO",5},{"CS3C04","DMS",5},{"CS3C05","USP",5},{"CS3L01","DSL",4},{"CS3L02","DEL",4}},
		{{"MA4C03","MATHS4",5},{"CS4C01","ADA",5},{"CS02","SE",5},{"CS403","OOPS",5},{"CS4C04","FAFL",5},{"CS4C05","DCN",5},{"CS4L01","ADAL",4},{"CS4L02","OOPL",4}},
		{{"CS0407","SA",5},{"CS0413","OS",5},{"CS0414","DBMS",5},{"CS0512","SS",5},{"CS0424","ME",5},{"CS0425","MP",5},{"CS0106","MPL",4},{"CS0107","DBMS",4}},
		{{"CS0418","CN",5},{"CS0523","OOMD",5},{"CS0425","CD",5},{"CS0450","WTA",5},{"CS0426","DA",5},{"CS0427","ANDROID",5},{"CS0112","WTAL",4},{"CS0109","CNL",4}},
		{{"CS0445","DOS",5},{"CS0521","CNS",5},{"CS0422","PPAA",5},{"CS0522","E1",5},{"CS0523","E2",5},{"CS0524","E3",5},{"CS0524","E4",4},{"CS0524","E5",4}},
		{{"CS0501","CC",5},{"CS0502","E6",5},{"CS0503","E7",5},{"CS0110","SEMINAR",5},{"CS0602","PROJECT",5},{"CS0504","E8",4},{"CS0505","E9",4},{"CS0506","E10",4}}
	};
	do
	{
		s.scoredCredits=0,s.scoredPending=0;
		init_Q(&q,&p);
		printf("Enter the details of Students\nStudent Name,USN,Semester\n");
		scanf("%s %s %d",s.stName,s.USN,&s.semNo);
		while(validsem(s.semNo))
		{
		    printf("Invalid Sem!! Enter b/w(1-8)\n"); 
	            scanf("%d",&s.semNo);
		}
		 if(s.semNo>1)
		 {
		 	printf("Enter the scored and pending credits\n");
        	        scanf("%d %d",&s.scoredCredits,&s.scoredPending);
		 }
		 printf("Select the attempted subjects of Semester %d from the below list\n",s.semNo);
		 displaySubjectDetails(b[s.semNo-1]);
	  do
	  {
		  do
		  {
		      printf("Enter the SNo\n");
		      scanf("%d",&k);
		      checksno(k);
		      if(checksno(k))
	       	      {
		         printf("Invalid SNo!! Enter b/w(1-8)\n");
		      }
		   }while(checksno(k));
		   printf("Enter the Subject Status(P/F)\n");
	            scanf(" %c",&a);
		   insertStatusQ(&p,a);
		   insertSubjectQ(&q,b[s.semNo-1][k-1]);
		   displayAttemptedSub(&q,&p);
		   printf("Do you want to stop the insertion of subject?(y/n)\n");
		   scanf(" %c",&a);
	 }while(a=='n');
	creditCalculation(&q,&p,&s);
	insertStudentList(&ptr,s);
	printf("Do you want to one more Calculation?(y/n)\n");
	scanf(" %c",&m);
	}while(m=='y');
	printf("Student Updated details after Sem Exam:\n");
	displayStudent(ptr);
	return 0;
}

//fourth project
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Student
{
	char stdName[20];
	char USN[20];
	int semNo;
	int scoredCredits;
	int pendingCredits;
};
struct studentBST
{
    struct Student student;
    struct studentBST *right;
    struct studentBST *left;
};
int validsem(int sem)
{
    if(sem>8)
    return 1;
    else
    return 0;
}

struct studentBST * createNode(struct Student s)
{
    struct studentBST *nn=(struct studentBST *)malloc(sizeof(struct studentBST));
    return nn;
}
void insertStudentBST(struct studentBST **h,struct Student s)
{
    struct studentBST *nn,*nodeptr,*parentptr;
    nn=createNode(s);
    nn->student=s;
    nn->left=NULL;
    nn->right=NULL;
    if((*h)==NULL)
    {
        (*h)=nn;
        (*h)->left=NULL;
        (*h)->right=NULL;
    }
    else
    {
        parentptr=NULL;
        nodeptr=(*h);
        while(nodeptr!=NULL)
        {
            parentptr=nodeptr;
            if(strcmp((s.USN),(nodeptr->student.USN))==0)
            {
                printf("Duplicate USN!! Can't Insert Data!!\n");
                return;
            }
            if(strcmp((s.USN),(nodeptr->student.USN))<1)
            {
                nodeptr=nodeptr->left;
            }
            else
            {
                nodeptr=nodeptr->right;
            }
        }
        if(strcmp((s.USN),(parentptr->student.USN))<1)
        {
            parentptr->left=nn;
        }
        else
        {
            parentptr->right=nn;
        }
    }
}
void displayStudent(struct Student std)
{
   printf("%-10s %-10s %-10d %-10d %-d\n",std.stdName,std.USN,std.semNo,std.scoredCredits,std.pendingCredits);
}

struct studentBST * searchStudent(struct studentBST * sl, char *usn)
{
    struct studentBST *temp=sl;
    if (temp == NULL)
    {
        //printf("%s",usn);
        return NULL;
    }
    if(strcmp((sl->student.USN),(usn))==0)
       return sl;
    if(strcmp((temp->student.USN),(usn))>1)
        return searchStudent(temp->left,usn);
    else
        return searchStudent(temp->right,usn);
}
void inorderBST(struct studentBST *s)
{
    if(s!=NULL)
    {
        inorderBST(s->left);
        printf("%-10s %-10s %-10d %-10d %-d\n",s->student.stdName,s->student.USN,s->student.semNo,s->student.scoredCredits,s->student.pendingCredits);
        inorderBST(s->right);
    }
}
void requiredCredits(struct Student s)
{
    int k;
    printf("%s's scored credits till sem %d is %d\n",s.stdName,s.semNo,s.scoredCredits);
    k=180-(s.scoredCredits);
    printf("Required to complete the graduation %d\n",k);
}

int main()
{
    char a;
    char usn[20];
    struct Student s;
    struct studentBST *ptr=NULL;
    struct studentBST *temp;
    do
    {
        s.scoredCredits=0,s.pendingCredits=0;
        printf("Enter the details of Students\n");
        printf("Student Name,USN,Semester\n");
        scanf("%s %s %d",s.stdName,s.USN,&s.semNo);
        while(validsem(s.semNo))
		{
		    printf("Invalid Sem!! Enter b/w(1-8)\n");
	          scanf("%d",&s.semNo);
		}
		if(s.semNo>1)
		{
		 	printf("Enter the scored and pending credits\n");
        	      scanf("%d %d",&s.scoredCredits,&s.pendingCredits);
		}
		insertStudentBST(&ptr,s);
        printf("Do you want to insert one more student data?(y/n)\n");
        scanf(" %c",&a);
    }while(a=='y');
    printf("Inserted Student Details!!\n");
    inorderBST(ptr);
    do
    {
    printf("Enter the Student USN to search\n");
    scanf("%s",usn);
    temp=searchStudent(ptr,usn);
    if(temp==NULL)
    {
        printf("Student Data Doesn't Exist!!\n");
    }
    else
    {
      displayStudent(temp->student);
      requiredCredits(temp->student);
    }
    printf("Do you want to search one more student data?(y/n)\n");
    scanf(" %c",&a);
    }while(a=='y');
    return 0;
}