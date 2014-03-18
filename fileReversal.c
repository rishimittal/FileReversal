         /*
	   Name : RISHI MITTAL
	   ROLL NO : 201305543
   	   Branch : M.TECH CSE
         */

#include "OS_HEADER.h"
#define BUF_SIZE 4096

	/* The below function reverseFile contains the main logic for the reversal for the file contents ,
	   logic behind is that it reads the file from the last Buffer_Size and then reverses the buffer 
	   contents and writes those contents onto the another file created and opened and named as the 
	   reverse_(oldFileName). For the last iteration the file , the pointer is seeked to the begin-
           ing of the file and read to the buffer the content into the buffer when they are less than the
           Buffer_Size
         */

int reverseFile(int args , char *argv[]) {

	int inputFile ,outputFile;
	int readVal,writeVal;
	char *buffer;
	int fileNameSize;
	char *newFileName;

	/* Produces error ,if input is wrong. */
	if(args != 2) {
		write(2, "usage like: ./reverse_tool text_file\n", 37);
		exit(-1);
	}

	/*  Check for the inputFile being opened or not  */
	if((inputFile = open(argv[1],O_RDONLY)) < 0) {
		write(2 , "Can't Open Input_file.\n" ,24);
		exit(-1);
	}

	/*  Dynamically allocate memory of 4KB to the  buffer. */
	buffer =(char*) malloc(BUF_SIZE * sizeof(char));

	if(buffer == 0) {
		write(2,"Out Of Memory,cannot Allocate..! \n",15);
		exit(-1);
	}
	/*  Count of the inputFileName characters , Calls string_length method defineed below which
            returns the number of characters from the file.
	*/
	fileNameSize = string_length(argv[1]);
	

	/* Dynamically allocates the fileName size plus size of reverse_ that is 8 */
	newFileName = (char*)malloc((fileNameSize + 9) * sizeof(char));

	/* Code to generate the fileName as reverse_(inputFileName)*/
	concatenate(newFileName , "reverse_");
	concatenate(newFileName , argv[1]);

	/*  Creates and open a outputFile */
	outputFile = open(newFileName,O_CREAT | O_WRONLY | O_TRUNC,0600);

	/*  Check for the output file descriptor */
	if(outputFile < 0) {
		write(2, "Failed to create a file\n" , 25);
		exit(-1);
	}

	int my_pos,trace;
	int last_pos = BUF_SIZE;
	int i = 1;
	
	/* Loop to read the file and write the new file*/
	while(1){
		/* Seeks to the last buffer_size from the end , returns my_pos > 0  i.e the bytes traversed
                   when it seeks successfully the asked bytes but return -1 when it does not that the last case 
		   when remaining bytes are less than the buffer_size.
		*/
		my_pos = lseek(inputFile, -(off_t)BUF_SIZE * i  ,SEEK_END);

		if(my_pos == -1) {           /*Boundary case for the last read, executed only once.*/
			trace =lseek(inputFile ,(off_t) 0,SEEK_SET);/* Seeks to the beginning of the file.*/
			readVal = read(inputFile,buffer,last_pos); /* reads from the begining to the last postion, or reads when 
								      file contents are less than buffer size.*/
			if(readVal == 0) {
				write(2,"read Complete\n",15);
				break;                          /*Breaks out of loop when read return 0.*/
			}

			/*Method Calling*/
			reverse_buffer(buffer , readVal);     /*Method dedicated to reverse the buffer contents.*/

			writeVal = write(outputFile,buffer,readVal); /*Writes the buffer content to the outputfile.*/
			
			if(writeVal == 0)break;

			break;  /*Computlsory break out of loop .*/
		}else {
			last_pos = my_pos;
			readVal = read(inputFile , buffer ,BUF_SIZE); /*Read the file content into the buffer.*/

			if(readVal <= 0){
				write(2,"read Complete\n",15);
				break;
			}

			/* Method Calling*/
			reverse_buffer(buffer, readVal);  /* Reverses the buffer content.*/

			writeVal = write(outputFile,buffer,readVal); /* Write the buffer content to the output file*/
			if(writeVal == 0)break;
			i++;        /*incrementing i for every traversal.*/
		}

	}
	/*Free the buffer content*/
	free(buffer);
	/* Free the memery allocated .*/
	free(newFileName);
	//Files Closing
	close(inputFile);
	close(outputFile);

	return 0;
}

      /*      reverse_buffer() method is used to reverse the charater content stored in the
	buffer memory (dynamically allocated) and reverses it's content using pointers.

	*/
void reverse_buffer(char *buffer ,int n){

	char *ct;
	int c ,d;

        /*Allocates memory dynamically*/
	ct = (char*)malloc(n * sizeof(char));

	if(ct == 0){
		write(2,"Failed to allocate Memory\n",27);
		exit(-1);
	}
	/*Copies the buffer to s in reverse direction*/
	for(c = n -1, d = 0 ;c >= 0; c--,d++){
		*(ct + d) = *(buffer + c);
	}
	/*Copies the s to buffer in reverse direction , finally making buffer reversed.*/
	for(c = 0 ; c < n ; c++){
		*(buffer + c) = *(ct + c);
	}
	//free the allocated memory in ct.
	free(ct);
}

		/* Function Which Counts the Number of the characters 
			in the inputFileName and returns the same. 
									*/
int string_length(char *fileName){
	int count = 0;
	/* Increases the count variable*/
        while(*fileName != '\0'){
		count++;
		fileName++;
	}
	return count;
}

		/*Function to concatenates two strings*/

void concatenate(char *oFileName ,char *toAdd) {
	while(*oFileName)
		oFileName++; /* Gets to the end of the oFileName.*/

	while(*toAdd) {
		*oFileName = *toAdd; /*Adds the new String */
		toAdd++;
		oFileName++;
	}
	*oFileName = '\0'; /*Ends by adding \0 in the end of the oFileName.*/
}
