#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<cerrno>
#include<cstring>
#include<string>

bool isfdvalid(int fd){
  if(fd<0){
    std::cout << "Something went wring " << strerror(errno) << std::endl;
    return false;
  }
  return true;
}

int main(){
  const char *path = "testfile.txt";
  int fd = open(path,O_RDWR | O_CREAT | O_APPEND,0666);
  if(!isfdvalid(fd)){
    close(fd);
    return 1;
  }
  
  pid_t cp = fork();
  if(cp==-1){
    std::cout << "Failed to create Child Process: " << std::strerror(errno) << std::endl;
    return 1;
  }
  
  //Writing using Parent Process-----------------------------------------------------------
  if(cp!=0){
    const char *d1="Hi I'm sonu kumar mahto, student at IIITB, persuing my Mtech in CSE\n";
    
    if(write(fd,d1,strlen(d1))<0){
      std::cerr << "couldn't write using Parent Process " << strerror(errno) << std::endl;
      close(fd);
      return 1;
    }
  }
  //Writing using Child Process----------------------------------------------------------
  if(cp == 0){
    const char *d2="2nd,Hi I'm sonu kumar mahto, student at IIITB, persuing my Mtech in CSE\n";
    if(write(fd,d2,strlen(d2))<0){
      std::cerr << "couldn't write using child Process " << strerror(errno) << std::endl;
      close(fd);
      return 1;
    }
  }
  
  close(fd);
  return 0;
}

/*=============================================================================================
Output:
$ cat testfile.txt
Hi I'm sonu kumar mahto, student at IIITB, persuing my Mtech in CSE
2nd,Hi I'm sonu kumar mahto, student at IIITB, persuing my Mtech in CSE

*/
