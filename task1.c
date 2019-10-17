#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv){
	char buf[1] = {0};
	int fd1 = open (argv[1], O_RDONLY);
	int fd2 = open (argv[2], O_WRONLY|O_CREAT, 0777);
	int i = read (fd1, buf, 1);
	int a;
	int b = 0;
	int k = 1;
	int m = 0;
	while (i != 0) {
		while ((buf[0] != ' ') && (i != 0)){
			if (((buf[0] <= '9') && (buf[0] >= '0')) || (buf[0] == '-')){
				if (buf[0] == '-') {
					k = 2;
					}
				else{
					a = atoi(buf);
                                        b = b + a;
                                        k = k + 1;
					}
				}
			else{
				lseek(fd1, -(k), SEEK_CUR);
				m = m + 1;
				while ((buf[0] != ' ') && (i != 0)){
					i = read (fd1, buf, 1);
					write (fd2, buf, 1);
				}
				k = 1;
				b = 0;
				m = 0;
			}
			i = read(fd1, buf, 1);
		}
		if (((b % 3 == 0) && (a != 0) && (a != 5)) && (b != 0) && (m == 0))
			write(fd2, "bizz ", 5); 
		if (((a == 0) || (a == 5) && (b % 3 != 0)) && (b != 0) && (m == 0))
			write(fd2, "buzz ", 5);
		if (((a == 0) || (a == 5) && (b % 3 == 0)) && (b != 0) && (m == 0))
			write(fd2, "bizzbuzz ", 9);
		if (((a != 0) && (a != 5) && (b % 3 != 0)) && (b != 0) && (m == 0)){
			lseek(fd1, -(k), SEEK_CUR);
			for (int j = 0; j < k; j++){
				read(fd1, buf, 1);
				write(fd2, buf, 1);
				}
			}
		i = read(fd1, buf, 1);
		k = 1;
		b = 0;
		m = 0;
		}
	close(fd1);
	close(fd2);
}
