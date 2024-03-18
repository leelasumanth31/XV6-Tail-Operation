#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"


#define size 100
#define sizes 10000

void tail(int start,int noOfLines,int argc,char *argv[argc]){
	for(int i=start;i<argc;i++){
		if(argc!=start+1){
			printf("==> %s <==\n",argv[i]);
		}
		char tempLines[sizes];
		int lines=0;
		int counter=0;
		int file=open(argv[i],0);
		if(file<0){
			printf("tail: cannot open '%s' for reading: No such file or directory",argv[i]);
			exit(0);
		}
		int n=read(file,tempLines,sizeof(tempLines));
		if(n!=0){
			for(int i=0;i<n;i++){
				if(tempLines[i]=='\n'){
					lines++;
				}
			}
			if(lines<=noOfLines){
				for(int i=0;i<n;i++){
					printf("%c",tempLines[i]);
				}
			}else{
				for(int i=0;i<n;i++){
					if(tempLines[i]=='\n'){
						counter++;
						if(counter>(lines-noOfLines)){
							printf("\n");
						}
					}else if(counter>=(lines-noOfLines)){
						printf("%c",tempLines[i]);
					}
				}
			}
		}
		if(i!=argc-1){
			printf("\n");
		}
	}
	exit(0);
}

int main(int argc,char *argv[]) {
	if(argc<=1){
		char *data[size];
		int totalLines=0;
		do{
			data[totalLines]=malloc(size);
			gets(data[totalLines],size);
		}while(strcmp(data[totalLines++],"")!=0);
		if(totalLines<10){
			for(int i=0;i<totalLines;i++){
				printf("%s",data[i]);
			}
		}else{
			int temp=totalLines-11;
			for(int i=temp;i<totalLines;i++){
				printf("%s",data[i]);
			}
		}
		
	}
	if(argc>1){
		if(( strcmp(argv[1],"-n")) == 0){
			tail(3,atoi(argv[2]),argc,argv);
		}else{
			tail(1,10,argc,argv);
		}
	}
	exit(0);
}