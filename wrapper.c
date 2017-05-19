/* Copyright (c) 2017 EPCC, The University of Edinburgh. */

/* Licensed under the Apache License, Version 2.0 (the "License"); */
/* you may not use this file except in compliance with the License. */
/* You may obtain a copy of the License at */

/*     http://www.apache.org/licenses/LICENSE-2.0 */

/* Unless required by applicable law or agreed to in writing, software */
/* distributed under the License is distributed on an "AS IS" BASIS, */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/* See the License for the specific language governing permissions and */
/* limitations under the License. */


#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>


int main(int argc, char* argv[]){
  
  MPI_Init(NULL, NULL);
  int w_size = 0;
  int rank = -1;
  char buffer[100];
  MPI_Comm_size(MPI_COMM_WORLD, &w_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  char command[1000] = "";
  char* c_ptr = command;
  int i = 0;
  int rv = 0;

  if (rank==0){
    for (i = 1; i < argc; i++){
      strcat(c_ptr, argv[i]);
      strcat(c_ptr, " ");
    }
    printf("Running \"%s\" on %d processes.\n", command, w_size);
  }

  MPI_Bcast((void*)&command[0], 1000, MPI_CHAR, 0, MPI_COMM_WORLD);

  if (argc > 1){
    FILE* file = popen(command, "r");
    while (fgets(buffer, 100, file)!=NULL){
      printf(buffer);
    }
    pclose(file);
    rv = 0;
  }
  else{
    printf("Nothing specified.\nAborting.\n");
    rv = 1;
  }

  MPI_Finalize();  
  return rv;
}
