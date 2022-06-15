#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define MAX 80
#define PORT 5033
#define SA struct sockaddr
char *buff,data[100],op[2],lim[2],user[20],pass[20],men[5];
int sockfd,connfd,f1=0,f3=0;
struct sockaddr_in servaddr,cli;
void soc()
{
// socket create and varification
sockfd=socket(AF_INET, SOCK_STREAM, 0);
if (sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr, sizeof(servaddr));
// assign IP, PORT
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
servaddr.sin_port = htons(PORT);
// connect the client socket to server socket
if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!=0)
{
  printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");
return;
}
int login()
{
system("clear");
strcpy(user," ");
strcpy(pass," ");
printf("Enter Login Credentials - \n");
printf("\nUserID - ");
scanf("%s",user);
//printf("%s",user);
printf("Password - ");
scanf("%s",pass);
//printf("%s%s",user,pass);
write(sockfd,user,sizeof(user));
write(sockfd,pass,sizeof(pass));
read(sockfd,data,sizeof(data));
read(sockfd,op,sizeof(op));
printf("\n%s\n",data);
//fputs(data,stdout);
if(op[0]=='1')
return 1;
else
return 0;
}
int reg()
{
system("clear");
strcpy(user," ");
read(sockfd,user,sizeof(user));
  printf("UserID: %s",user);
printf("Enter your password: ");
scanf("%s",pass);
write(sockfd,pass,sizeof(pass));
int a=login();
return a;
}
void fmenue()
{
char f2[2];
system("clear");
printf("Welecome to our NFS\n");
printf("\n1.To Read a file.\n2.To Create a new file.\n3.To Edit a file.\n4.To delete afile.\n5.To rename a file.\n");
scanf("%d",&f1);
if(f1==1)
strcpy(f2,"1");
else if(f1==2)
strcpy(f2,"2");
else if(f1==3)
strcpy(f2,"3");
else if(f1==4)
strcpy(f2,"4");
else if(f1==5)
strcpy(f2,"5");
else
{
printf("Invalid Entry");
exit(0);
}
printf("Enter file name: ");
//fgets(buff,sizeof(buff)+1,stdin);
scanf("%s",buff);
//fputs(buff,stdout);
write(sockfd,buff,sizeof(buff));
write(sockfd,f2,sizeof(f2));
read(sockfd,data,sizeof(data));
//if(strcmp(data,"succ")!=0)
//printf("%s",data);
  return;
}
void dread()
{
char bit[5];
int a;
system("clear");
read(sockfd,lim,sizeof(lim));
int n=(int)lim[0];
for(int i=0;i<n;i++)
{
strcpy(data," ");
read(sockfd,data,100);
printf("%d. %s",i+1,data);
}
read(sockfd,bit,sizeof(bit));
a=atoi(bit);
//abs(a);
printf("\nTotal no. of characters - %d",a);
return;
}
void dwrite()
{
system("clear");
//read(sockfd,op,sizeof(op));
printf("Enter data to be written: \n");
int i=0;
while(1)
{
strcpy(data,"");
gets(data);
if(i>0)
write(sockfd,data,sizeof(data));
//printf("\naa%saa\n",data);
if(data[0]=='e' && strlen(data)==1)
break;
//printf("\n1%s1\n",data);
  i++;
}
return;
}
void delin()
{
int l=0;
char lin[2];
dread();
printf("\nEnter Line no. to be deleted: ");
scanf("%d",&l);
lin[0]=(char)l;
write(sockfd,lin,sizeof(lin));
printf("\nAfter deleting - \n");
dread();
return;
}
void fmenue1()
{
char f2[2];
system("clear");
printf("\n1.To add a new line of data.\n2.To add data to an existing line.\n3.To delete aparticular line\n4.To delete data in a line\n");
scanf("%d",&f3);
if(f3==1)
strcpy(f2,"1");
else if(f3==2)
strcpy(f2,"2");
else if(f3==3)
strcpy(f2,"3");
else if(f3==4)
strcpy(f2,"4");
else
{
printf("Invalid Entry");
exit(0);
}
  write(sockfd,f2,sizeof(f2));
return;
}
void line()
{
int l=0;
char lin[2];
dread();
printf("\nEnter Line no. before which you want to enter data: ");
scanf("%d",&l);
lin[0]=(char)l;
write(sockfd,lin,sizeof(lin));
dwrite();
dread();
return;
}
void dread1()
{
int i;
read(sockfd,data,sizeof(data));
printf("\n");
for(i=0;i<strlen(data)-1;i++)
printf("%c-%d ",data[i],i+1);
printf("\n");
return;
}
void charact()
{
int l=0,l1=0;
char lin[2];
dread();
printf("\nEnter Line no. in which you want to enter data: ");
scanf("%d",&l);
lin[0]=(char)l;
write(sockfd,lin,sizeof(lin));
dread1();
  printf("Enter Char no. before which you want to enter data: ");
scanf("%d",&l1);
lin[1]=(char)l1;
write(sockfd,lin,sizeof(lin));
printf("Enter data to be written: ");
strcpy(data," ");
scanf("%s",data);
//gets(data);
write(sockfd,data,sizeof(data));
dread();
return;
}
void dechar()
{
int l=0,l1=0,l2=0;
char lin[2];
dread();
printf("\nEnter Line no. whose data you want to delete: ");
scanf("%d",&l);
lin[0]=(char)l;
write(sockfd,lin,sizeof(lin));
dread1();
printf("Enter Char no.s between which you want to delete data: ");
scanf("%d",&l1);
scanf("%d",&l2);
lin[0]=(char)l1;
lin[1]=(char)l2;
write(sockfd,lin,sizeof(lin));
dread();
return;
}
void edit()
{
fmenue1();
if(f3==1)
line();
else if(f3==2)
charact();
  else if(f3==3) 
    delin(); 
  else if(f3==4) 
    dechar(); 
  return; 
}
void ren() 
{
  char *new; 
  new=(char*)malloc(50*sizeof(char)); 
  printf("Enter new file name: "); 
  scanf("%s",new); 
  write(sockfd,new,sizeof(new)); 
  return; 
}
int main(int argc,char *argv[]) 
{
  system("clear"); 
  buff=(char*)malloc(50*sizeof(char)); 
  int a=0,g=0; 
  soc(); 
  printf("\n1.Register\n2.Login\n"); 
  scanf("%d",&a); 
  if(a==1) 
  { 
    strcpy(men,"reg"); 
    write(sockfd,men,sizeof(men)); 
    g=reg(); 
  }
  else if(a==2) 
  { 
    strcpy(men,"log"); 
    write(sockfd,men,sizeof(men)); 
    g=login(); 
  }
  else 
  {
    printf("Invalid Entry"); 
    exit(0);
    }
if(g==1)
{
fmenue();
strcpy(buff," ");
if(f1==1)
dread();
else if(f1==2)
dwrite();
else if(f1==3)
edit();
else if(f1==5)
ren();
read(sockfd,data,sizeof(data));
printf("\n%s\n",data);
}
close(sockfd);
free(buff);
return 0;
}
