#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#define PORT 5033
#define SA struct sockaddr
char *buffer,mode[2],data[100],op[2],user[20],pass[20],men[5],f2[2];
int sockfd,connfd,len;
struct sockaddr_in servaddr, cli;
FILE *fp,*fp1,*fp5,*fp6,*fp7,*fp8;
void soc()
{
// socket create and verification
sockfd=socket(AF_INET, SOCK_STREAM, 0);
if(sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr, sizeof(servaddr));
// assign IP, PORT
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(PORT);
// Binding newly created socket to given IP and verification
if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr)))!=0)
{
printf("socket bind failed...\n");
exit(0);
}
else
printf("Socket successfully binded..\n");
// Now server is ready to listen and verification
if ((listen(sockfd, 5))!=0) 
{
  printf("Listen failed..."); 
  exit(0); 
}
  else 
    printf("Server listening.."); 
  len=sizeof(cli); 
  return; 
}
int login() 
{ 
  int t=0; 
  strcpy(user," "); 
  strcpy(pass," "); 
  read(connfd,user,sizeof(user)); 
  read(connfd,pass,sizeof(pass)); 
  printf("\n%s",user); 
  printf("\n%s",pass); 
  FILE *fp2; 
  if ((fp2=fopen("login","r"))==NULL) 
  {
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data)); 
    exit(0); 
  } 
  while(fgets(data,20,fp2)!=NULL) 
  { //fputs(data,stdout);
    t=0; 
    strcpy(op,"0"); 
    if(data[0]==user[0] && data[1]==user[1]) 
    { //printf("test user\n"); 
      t=1; strcpy(data," "); 
      fgets(data,20,fp2); 
      int m=0; 
      //printf("\na%ca\n",data[3]); 
      for(int i=0;i<strlen(data)-1;i++) 
      { 
        if(pass[i]==data[i]) 
          m=1; 
        else
        { 
          m=0; 
          break; 
        } 
      }
      if(m==1) 
      { 
        //printf("test pass\n"); 
        strcpy(data,"Welcome to our NFS"); 
        strcpy(op,"1"); 
        break; 
      }
      else 
      { 
        strcpy(op,"0"); 
        strcpy(data,"Invalid Password"); 
        break; 
      } 
    }
    else 
      fgets(data,30,fp2); 
  }
  if(t==0) 
  { 
    strcpy(data,"Invalid UserID"); 
    strcpy(op,"0"); 
  }
  write(connfd,data,sizeof(data)); 
  write(connfd,op,sizeof(op)); 
  fclose(fp2); 
  if(op[0]=='1') 
    return 1; 
  elsereturn 0; 
}
int reg() 
{ 
  char temp[20],temp1[20]; 
  int a=0; 
  FILE *fp3,*fp4; 
  if ((fp3=fopen("login","r"))==NULL) 
  {
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data)); exit(0); 
  }//To retrieve userid & password
while(fgets(temp,20,fp3)!=NULL) 
  fgets(temp1,20,fp3); 
  fclose(fp3); 
  a=(int)temp[1]; 
  a=a+1; 
  temp[1]=(char)a; 
  write(connfd,temp,sizeof(temp)); 
  //printf("%s",temp); 
  read(connfd,pass,sizeof(pass)); 
  //printf("%s",pass); 
  if ((fp4=fopen("login","a"))==NULL) 
  {
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data)); 
    exit(0); 
  }
  fputs(temp,fp4); 
  fputs(pass,fp4); 
  fputs("\n",fp4); 
  fclose(fp4); 
  a=login(); 
  return a; 
}
void dread() 
{ 
  int c=0; 
  char lim[2]; 
  if((fp1=fopen(buffer,mode))==NULL) 
  { 
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data)); 
    exit(0); 
  } 
  printf("\nThe file is now open.\n"); 
  while(fgets(data,100,fp)!=NULL) 
    c++; 
  lim[0]=(char)c; 
  write(connfd,lim,sizeof(lim)); 
  strcpy(data," "); 
  while(fgets(data,100,fp1)!=NULL) 
  { 
    write(connfd,data,100); 
    //printf("%s",data); 
    strcpy(data," "); 
  }
  int a=ftell(fp1); 
  char bit[5];
sprintf(bit,"%d",a); 
  //printf("a%sa",bit); 
  write(connfd,bit,sizeof(bit)); 
  fclose(fp1); 
  return; 
}
void store() 
{ 
  //write(connfd,op,sizeof(op)); 
  int i=0; 
  while(1) 
  { 
    if(i>0) 
    { 
      strcpy(data," "); 
      read(connfd,data,sizeof(data)); 
      //printf("\na%sa\n",data); 
      if(data[0]=='e' && strlen(data)==1) 
        return; 
      if(strlen(data)>0) 
      { 
        fputs(data,fp); 
        fputs("\n",fp); 
      }
      else 
        fputs("\n",fp); 
    }
    i++; 
  }
  return; 
}
void dwrite() 
{ 
  printf("\nFile Created.\n"); 
  store(); 
  strcpy(data,"File with data created."); 
  printf("File with data created.\n"); 
  return; 
}
void dappend() 
{ 
  printf("\nFile Opened.\n"); 
  store(); 
  return; 
}
void delete()
{ 
  if(remove(buffer)==0) 
  { 
    printf("%s Deleted successfully\n",buffer); 
    strcpy(data,"File deleted successfully"); 
  }
  else 
  { 
    printf("Unable to delete file %s\n",buffer); 
    strcpy(data,"Unable to delete file"); 
  }
  return; 
}
void temp(int l) 
{ int i;
 if ((fp5=fopen("temp1","w+"))==NULL) 
 {
   printf("\n%s file failed to open.\n",buffer); 
   strcpy(data,"Error 404"); 
   write(connfd,data,sizeof(data)); 
   exit(0); 
 }
 if ((fp6=fopen("temp2","w+"))==NULL) 
 {
   printf("\n%s file failed to open.\n",buffer); 
   strcpy(data,"Error 404"); 
   write(connfd,data,sizeof(data)); 
   exit(0); 
 }
 for(i=0;i<l-1;i++) 
 { 
   fgets(data,100,fp); 
   fputs(data,fp5); 
 }
 while(fgets(data,100,fp)!=NULL) 
   fputs(data,fp6); 
 rewind(fp5); 
 rewind(fp6); 
 return; 
}
void cop1() 
{ 
  if ((fp7=fopen(buffer,"w"))==NULL) 
  {
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data));
    exit(0); 
  }
  while(fgets(data,100,fp5)!=NULL) 
    fputs(data,fp7); 
  return; 
}
void delin() 
{ 
  dread(); 
  int l=0; 
  char lin[2]; 
  read(connfd,lin,sizeof(lin)); 
  l=(int)lin[0]; 
  rewind(fp); 
  temp(l); 
  fgets(data,100,fp6); 
  fclose(fp); 
  cop1(); 
  while(fgets(data,100,fp6)!=NULL) 
    fputs(data,fp7); 
  fclose(fp5); 
  fclose(fp6); 
  fclose(fp7); 
  printf("Line no %d deleted\n",l); 
  if ((fp=fopen(buffer,"r"))==NULL) 
  {
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data)); 
    exit(0); 
  }
  dread(); 
  strcpy(data,"line deleted"); 
  remove("temp1"); 
  remove("temp2"); 
  return; 
}
void line() {
dread(); 
  int l=0,i; 
  char lin[2]; 
  read(connfd,lin,sizeof(lin)); 
  l=(int)lin[0]; 
  rewind(fp); 
  temp(l); 
  fclose(fp); 
  cop1(); 
  fclose(fp7); 
  if ((fp=fopen(buffer,"a"))==NULL) 
  {
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data)); 
    exit(0); 
  }
  dappend(); 
  while(fgets(data,100,fp6)!=NULL) 
    fputs(data,fp); 
  fclose(fp5); 
  fclose(fp6); 
  fclose(fp); 
  printf("Edit Complete\n"); 
  if ((fp=fopen(buffer,"r"))==NULL) 
  {
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data)); 
    exit(0); 
  }
  dread(); 
  strcpy(data,"Edit Complete"); 
  remove("temp1"); 
  remove("temp2"); 
  return; 
}
void charact() 
{ 
  dread();
  int l=0,i,l1=0,j;
  char lin[2],dat[100],last,data1[100],data2[100]; 
  read(connfd,lin,sizeof(lin)); 
  l=(int)lin[0]; 
  rewind(fp); 
  temp(l); 
  fclose(fp); 
  cop1(); 
  strcpy(data1," "); 
  fgets(data,100,fp6); 
  write(connfd,data,sizeof(data)); 
  read(connfd,lin,sizeof(lin)); 
  l1=(int)lin[1]; 
  read(connfd,dat,sizeof(dat)); 
  //printf("\na%sa\n",dat); 
  //printf("\nc%sc\n",data); 
  strcpy(data1,""); 
  for(i=0;i<l1-1;i++) 
  { 
    data1[i]=data[i]; 
    //printf("\na%sa\n",data1); 
  }
  j=0; 
  for(i=l1-1;i<strlen(data);i++) 
  { 
    data2[j]=data[i]; 
    j++; 
  }
  //printf("\na%sa\n",data2); 
  strcpy(data,""); 
  strcat(data,data1); 
  strcat(data,dat); 
  strcat(data,data2); 
  //printf("\nb%sb\n",data); 
  fputs(data,fp7); 
  while(fgets(data,100,fp6)!=NULL) 
    fputs(data,fp7); 
  fclose(fp5); 
  fclose(fp6); 
  fclose(fp7); 
  printf("Line no %d Editted\n",l); 
  if ((fp=fopen(buffer,"r"))==NULL) 
  {
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data)); 
    exit(0); 
  }
  dread(); 
  strcpy(data,"Edit Complete"); 
  remove("temp1"); 
  remove("temp2"); 
  return; 
}
void dechar() 
{ 
  dread(); 
  int l=0,i,l1=0,j,l2=0; 
  char lin[2],last,data1[100],data2[100]; 
  read(connfd,lin,sizeof(lin)); 
  l=(int)lin[0]; 
  rewind(fp); 
  temp(l); 
  fclose(fp); 
  cop1(); 
  strcpy(data1," "); 
  fgets(data,100,fp6); 
  write(connfd,data,sizeof(data)); 
  read(connfd,lin,sizeof(lin)); 
  l1=(int)lin[0]; 
  l2=(int)lin[1]; 
  //printf("\na%sa\n",dat); 
  //printf("\nc%sc\n",data); 
  strcpy(data1,""); 
  for(i=0;i<l1;i++) 
  { 
    data1[i]=data[i]; 
    //printf("\na%sa\n",data1); 
  }
  j=0; 
  for(i=l2-1;i<strlen(data);i++) 
  { 
    data2[j]=data[i]; 
    j++; 
  }
  //printf("\na%sa\n",data2); 
  strcpy(data,""); 
  strcat(data,data1);
  strcat(data,data2); 
  //printf("\nb%sb\n",data); 
  fputs(data,fp7); 
  while(fgets(data,100,fp6)!=NULL) 
    fputs(data,fp7); 
  fclose(fp5); 
  fclose(fp6); 
  fclose(fp7); 
  printf("Line no %d Editted\n",l); 
  if ((fp=fopen(buffer,"r"))==NULL) 
  {
    printf("\n%s file failed to open.\n",buffer); 
    strcpy(data,"Error 404"); 
    write(connfd,data,sizeof(data)); 
    exit(0); 
  }
  dread(); 
  strcpy(data,"Edit Complete"); 
  remove("temp1"); 
  remove("temp2"); 
  return; 
}
void edit() 
{ 
  char f3[2]; 
  read(connfd,f3,sizeof(f3)); 
  if(f3[0]=='1') 
    line(); 
  else if(f3[0]=='2') 
    charact(); 
  else if(f3[0]=='3') 
    delin(); 
  else if(f3[0]=='4') 
    dechar(); 
  return; 
}
void ren() 
{ 
  char *new; 
  new=(char*)malloc(50*sizeof(char)); 
  read(connfd,new,sizeof(new)); 
  if(!rename(buffer,new))
  {
    printf("%s","\nFile name changed to %s successfully\n",new); 
    strcpy(data,"File name changed to successfully"); 
  }
  else 
  {
    printf("%s","\nFailed to change file name to %s\n",buffer); 
    strcpy(data,"Failed to change file name"); 
  }
  return; 
}
int main(int argc,char *argv[]) 
{ system("clear"); 
 buffer=(char*)malloc(50*sizeof(char)); 
 soc(); 
 while(1) 
 { // Accept the data packet from client and verification connfd = accept(sockfd, (SA*)&cli, &len); 
   if (connfd<0) 
   { 
     printf("\nserver acccept failed...\n"); 
     exit(0); 
   }
   else 
     printf("\nserver acccept the client...\n"); 
   int g=0; 
   read(connfd,men,sizeof(men)); 
   if(strcmp(men,"reg")==0) 
     g=reg(); 
   else 
     g=login(); 
   if(g==1) 
   { 
     strcpy(op,"0"); 
     strcpy(buffer," "); 
     read(connfd,buffer,sizeof(buffer)); 
     strcpy(f2," "); 
     read(connfd,f2,sizeof(f2)); 
     if(f2[0]=='1') 
       strcpy(mode,"r"); 
     else if(f2[0]=='2') 
       strcpy(mode,"w"); 
     else if(f2[0]=='3') 
       strcpy(mode,"r"); 
     else if(f2[0]=='4')
       strcpy(mode,"r");
     else if(f2[0]=='5')
       strcpy(mode,"r");
//printf("Msg received: %s",buffer);
if ((fp=fopen(buffer,mode))==NULL)
{
printf("\n%s file failed to open.\n",buffer);
strcpy(data,"Error 404");
write(connfd,data,sizeof(data));
exit(0);
}
else
{
strcpy(data,"succ");
write(connfd,data,sizeof(data));
if(f2[0]=='1')
{
dread();
strcpy(data,"File read complete.");
printf("File read complete.\n");
}
else if(f2[0]=='2')
dwrite();
else if(f2[0]=='3')
edit();
else if(f2[0]=='4')
delete();
else if(f2[0]=='5')
ren();
fclose(fp);
}
write(connfd,data,sizeof(data));
}
}
close(sockfd);
}
