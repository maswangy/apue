#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd = -1;
	fd = mydup2(0,10);
	if(fd < 0) {
		perror("mydup2");
		return -1;
	}

	printf("fd = %d\n",fd);
	return 0;
}

int mydup2(int oldfd, int newfd) {
	//判断fd和newfd的范围是否正确
	if(oldfd < 0 || oldfd > 256){
		printf("fd is wrong.\n");
		return -1;
	}

	if(newfd <0 || newfd > 256){
		printf("newfd is wrong.\n");
		return -1;
	}

	int index = 0;
	int fdarray[newfd];

	//获取所要的newfd
	int newfdindex;
	for ( index=0; index<newfd; index++ ) {
		fdarray[index] = dup(oldfd);
		if(fdarray[index] == -1) {
			printf("error while dup.\n");
			return -1;
		} else {
			if(fdarray[index] == newfd) {
				newfdindex = index;
				break;
			}
		}
	}
	//将之前打开的fd都关闭
	for(index=0; index<newfdindex; index++){
		close(fdarray[index]);
	}

	return fdarray[newfdindex];
}
