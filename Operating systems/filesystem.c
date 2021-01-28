//Walter Mkpanam

#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE  255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 5     // Mav shell only supports five arguments
#define NUM_BLOCKS        4226
#define BLOCK_SIZE        8192
#define NUM_FILES         128
#define HIDDEN            0x1
#define READONLY          0x2
#define MAX_FILE_SIZE     10240000

uint8_t blocks[NUM_BLOCKS][BLOCK_SIZE];

struct Directory_Entry
{
    uint8_t valid;
    char name[32];
    uint32_t inode;
    
};

struct Inode
{
    uint8_t valid;
    uint8_t attributes;
    uint32_t size;
    uint32_t blocks[1250];
};

struct Directory_Entry * dir;
uint8_t*  freeBlockList;
uint8_t*  freeInodeList;
struct Inode* inodeList;

FILE* fptr;
FILE* newfp; // for get <filename> <newfilename>

int status;
struct stat buf;

void initializeDirectory()
{
    int i;
    for(i = 0; i < 128; i++)
    {
        dir[i].valid = 0;
        memset(dir[i].name, 0, 255);
        dir[i].inode = -1;
    }
}

void initializeFreeBlockList()
{
    int i;
    for(i = 0; i < NUM_BLOCKS; i++)
    {
        freeBlockList[i] = 1;
    }
    
}

void initializeInodeList()
{
    int i;
    for(i = 0; i < NUM_FILES; i++)
    {
        freeInodeList[i] = 0;
    }
}

void initializeInodes()
{
    int i;
    for(i = 0; i < NUM_FILES; i++)
    {
        inodeList[i].attributes = 0;
        inodeList[i].size       = 0;
        inodeList[i].valid      = 0;
        
        int j;
        for(j = 0; i < 1250; i++)
        {
            inodeList[i].blocks[j] = -1;
        }
    }
}

int findFreeInode()
{
    int ret = -1;
    int i;
    for(i = 0; i < NUM_FILES; i++)
    {
        
        if(freeInodeList[i] == 1)
        {
            ret = i;
            freeInodeList[i] = 0;
            break;
        }
    }
    return ret;
}

int findFreeBlock()
{
    int ret = -1;
    int i;
    for(i = 10; i < NUM_BLOCKS; i++)
    {
        
        if(freeBlockList[i] == 0)
        {
            ret = i;
            freeBlockList[i] = 1;
            break;
        }
    }
    return ret;
}

int findFreeDirectory()
{
    int ret = -1;
    int i;
    for(i = 0; i < 128; i++)
    {
      if(dir[i].valid == 0)
      {
            ret = i;
            dir[i].valid = 1;
            break;
     }
    }
    return ret;
}

void createfs(char* fileName)
{
    if(fileName == NULL)
    {
        printf("%s\n","createfs: file not found");
    }
    else
    {
       
        fptr = fopen(fileName,"w");
        memset(&blocks[0], 0, NUM_BLOCKS * BLOCK_SIZE);
        fwrite(&blocks[0],NUM_BLOCKS, BLOCK_SIZE,fptr);
        fclose(fptr);
    }
   
}

void openFile(char* fileName)
{

    status = stat(fileName,&buf);
    fptr = NULL;
    if(status == -1)
    {
        printf("open: File not found\n");
    }
    else
    {
        fptr = fopen(fileName, "r");
        fread(&blocks[0],NUM_BLOCKS, BLOCK_SIZE,fptr);
        fclose(fptr);
        
    }
  
}

void closeFile(char* fileName) // user has to enter filename for close
{
    if(fptr == NULL)
    {
        printf("File not open\n");
    }
    else
    {
        fptr = fopen(fileName, "w");
        if(fileName == NULL)
        {
            printf("%s\n","close: File not open.");
        }
        else
        {
            fwrite(&blocks[0], NUM_BLOCKS, BLOCK_SIZE, fptr);
            fclose(fptr);
            fptr = NULL;
        }
    }
    
    
}

void attrib(char* filename, char* cmd)
{
    status = stat(filename,&buf);
    
    if(status == -1)
    {
        printf("%s\n","attrib: File not found");
    }
    else
    {
        int found = -1;
        int j;
        for (j = 0; j < NUM_FILES; j++)
        {
            if (strcmp(filename, dir[j].name) == 0)
            {
                found = j;
                
            }
            
        }
        if(strcmp(cmd, "+h") == 0)
        {
            inodeList[found].attributes|= HIDDEN;
        }
        else if (strcmp(cmd, "-h") == 0)
        {
            inodeList[found].attributes &=HIDDEN;
        }
        else if (strcmp(cmd, "+r") == 0)
        {
            inodeList[found].attributes |= READONLY;
        }
        else if (strcmp(cmd, "-r") == 0)
        {
            inodeList[found].attributes &=READONLY;
        }
        else
        {
            printf("%s\n","use +/- h or r");
        }
        
        
    }
    
}

int df()
{
     int result = 0;
    if (fptr != NULL)
    {
        int i = 0;
           for(i = 10; i < NUM_BLOCKS; i++)
           {
               if(freeBlockList[i] == 0)
               {
                   result++;
               }
           }
           result = result * BLOCK_SIZE;
           
           return result;
    }
    else
    {
        return 0;
    }
   
    
}

void list(char* cmd)
{
    
    int i;
    if(cmd == NULL)
    {
        for(i = 0; i < NUM_FILES; i++)
        {
            stat(dir[i].name,&buf);
            int size = (int)buf.st_size;
            char time[25];
            strftime(time, 25, "%b %d %H:%M", localtime(&buf.st_atime));

                if(dir[i].valid && inodeList[i].attributes != HIDDEN)
                {
                    printf("%-5d %s %s",size,time,dir[i].name);
                    printf("\n");
                }
                else
                {
                    // do nothing
                }
        }
    }
    else
    {
        for(i = 0; i < NUM_FILES; i++)
        {
            stat(dir[i].name,&buf);
            int size = (int)buf.st_size;
            char time[25];
            strftime(time, 25, "%b %d %H:%M", localtime(&buf.st_atime));

                if(dir[i].valid)
                {
                  
                    printf("%-5d %s %s",size,time,dir[i].name);
                    printf("\n");
                }
                else
                {
                    // do nothing
                }
        }
    }
        
}

int main()
{
    
    dir           = (struct Directory_Entry*)&blocks[0][0];
  
    freeInodeList = (uint8_t*)&blocks[7][0];
    freeBlockList = (uint8_t*)&blocks[8][0];
    inodeList     = (struct Inode*)&blocks[9][0];

    initializeDirectory();
    initializeInodeList();
    initializeFreeBlockList();
    initializeInodes();
    

  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );

  while( 1 )
  {
    // Print out the mfs prompt
    printf ("mfs> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];
    memset(&token, '\0', sizeof(token));

    int   token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *arg_ptr;                                         
                                                           
    char *working_str  = strdup( cmd_str );                

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input stringswith whitespace used as the delimiter
    while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
      if(strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }
      
      if(token[0] == NULL) continue; // continue if user presses enter
      
      if(strcmp(token[0], "exit") == 0 || strcmp(token[0], "quit") == 0 )
      {
          break;
      }
    
      if(strcmp(token[0], "open") == 0)
      {
          openFile(token[1]);
      }
      else if (strcmp(token[0], "close") == 0)
      {
          closeFile(token[1]);
      }
      else if (strcmp(token[0], "put") == 0)
      {
          // similar to block copy up to 129
          if(strlen(token[1]) > 32)
          {
              printf("%s\n","put error: File name too long.");
          }
		  else
		  {
			  status = stat(token[1], &buf);

			  // If stat did not return -1 then we know the input file exists and we can use it.
			  if (status != -1)
			  {
                  if(buf.st_size < MAX_FILE_SIZE && buf.st_size < df())
                  {
                      FILE* ifp = fopen(token[1], "r");
                      printf("Reading %d bytes from %s\n", (int)buf.st_size, token[1]);
                      int found = findFreeDirectory();
                      strcpy(dir[found].name,token[1]);
                      

                      int copy_size = (int)buf.st_size;
                      int offset = 0;
                      int block_index = findFreeBlock();
                      int freeInode = findFreeInode();
                      
                      while (copy_size > 0)
                      {
                          inodeList[freeInode].blocks[0] = block_index;
                          inodeList[freeInode].valid = 1;
                          inodeList[freeInode].size = (int)buf.st_size;
                          
                          fseek(ifp, offset, SEEK_SET);

                          int bytes = (int)fread(blocks[block_index], BLOCK_SIZE, 1, ifp);

                          if (bytes == 0 && !feof(ifp))
                          {
                              printf("An error occured reading from the input file.\n");
                              return -1;
                          }

                          clearerr(ifp);

                          copy_size -= BLOCK_SIZE;

                          offset += BLOCK_SIZE;
                      }
                      fclose(ifp);
                  }
				  
			  }
              else
              {
                  printf("File not found.\n");
              }

          }
      }
      else if (strcmp(token[0], "get") == 0)
      {
		  int found = -1, i;
		  for (i = 0; i < 128; i++)
		  {
			  if (strcmp(token[1], dir[i].name) == 0)
			  {
				  found = i;
				  break;
			  }
		  }

		  int inode_idx = dir[found].inode;
			
			//open file
				if (token_count < 3) //get <filename>
				{
					fptr = fopen(token[1], "w");
					if (fptr == NULL)
					{
						printf("Could not open output file: %s\n", token[1]); //not sure on token num
						perror("Opening output file returned");
						return -1;
					}
				}
				else //get <filename> <newfilename>
				{
					fptr = fopen(token[2], "w");
					if (fptr == NULL)
					{
						printf("Could not open output file: %s\n", token[2]); //not sure on token num
						perror("Opening output file returned");
						return -1;
					}
				}

			
			//copy from block ex
			int copy_size = inodeList[inode_idx].size;
			int count = 0;
			int block_index = 0;
			/*while(copy_size >8192)
			  {
				fwrite(inode[inode_idx].blocks[count++],8192,1,fd);
				copy_size = copy_size=8192;
			  }*/

          // similar to block copy from 129
          // find free block

			while (copy_size > 0)
			{

				int num_bytes;

				// If the remaining number of bytes we need to copy is less than BLOCK_SIZE then
				// only copy the amount that remains. If we copied BLOCK_SIZE number of bytes we'd
				// end up with garbage at the end of the file.

				//handles short copy handles last block.
				if (copy_size < BLOCK_SIZE)
				{
					num_bytes = copy_size;
				}
				else
				{
					num_bytes = BLOCK_SIZE;
				}

				// Write num_bytes number of bytes from our data array into our output file.
				fwrite(blocks[block_index], num_bytes, 1, fptr);
				//(blockdatastruct[inode[inode_inx].blocks[counts++]], 
				// Reduce the amount of bytes remaining to copy, increase the offset into the file
				// and increment the block_index to move us to the next data block.
				copy_size -= BLOCK_SIZE;
				count += BLOCK_SIZE;
                block_index = findFreeBlock();

				fseek(newfp, count, SEEK_SET);
			}

			fclose(newfp);
          
      }
      else if (strcmp(token[0], "del") == 0)
      {
		  
          status = stat(token[1],&buf);
          
          if(status == -1)
          {
              printf("%s\n","del error: File not found.");
          }
          else
          {
              int i = 0, found = -1;
              for(i = 0; i < NUM_FILES; i++)
              {
                  if(strcmp(dir[i].name, token[1]) == 0)
                  {
                      found = i;
                  }
                  if(inodeList[i].attributes == READONLY)
                  {
                      printf("Cannot delete file - in Read only mode\n");
                  }
                  else
                  {
                      dir[found].valid = 0;
                      freeBlockList[found] = 0;
                      dir[found].inode = 0;
                      freeInodeList[found] = 1;
                  }
              }
              // mark as no longer in use
              // free directory entry
          }
      }
      else if (strcmp(token[0], "list") == 0)
      {
          list(token[1]);
      }
      else if (strcmp(token[0], "createfs") == 0)
      {
          createfs(token[1]);
      }
      else if (strcmp(token[0], "df") == 0)
      {
          int count = df();
          printf("%d bytes free.\n",count);
          
      }
      else if (strcmp(token[0], "attrib") == 0)
      {
          attrib(token[2], token[1]);
      }
      else
      {
          printf(" %s: Command not found.\n", token[0]);
          continue;
      }
      
    free( working_root );

  }
    
  return 0;
}
