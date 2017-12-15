/**
 * @author: Joshua Standiford, Chris Sidell
 * @description:
 * Project 2 - LCS program
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <omp.h>

using namespace std;
/******************************
 *     Function Prototypes    *
 ******************************/

int mem_parallel_lcs(std::vector<char> X, std::vector<char> Y, int n, int m);
int parallel_lcs(std::vector<char> X, std::vector<char> Y, int n, int m);
int lcs(std::vector<char> X, std::vector<char> Y, int n, int m);
std::vector<char> read(std::string file, int len);


/******************************
 *        Main Function       *
 ******************************/
int main(int argc, char *argv[]) {
  
    //If the arguments don't match the argument signature, print guide.
    if(argc != 5){
        std::cout << "Program does not match testing signature." << std::endl;
        std::cout << "lcs arguments signature: - " << std::endl;
        std::cout << "<file 1> - .txt file containing first LCS string" << std::endl;
        std::cout << "<n> - number of characters to parse from file 1" << std::endl;
        std::cout << "<file 2> - .txt file containing second LCS string" << std::endl;
        std::cout << "<m> - number of characters to parse from file 2" << std::endl;
        return 0;
    }

    //Assign arguments to variables
    std::string file1 = argv[1];
    std::string file2 = argv[3];
    int n = atoi(argv[2]);
    int m = atoi(argv[4]);
    std::vector<char> X;
    std::vector<char> Y;


    //Read files in and parse them
    X = read(file1, n);
    Y = read(file2, m);
    
    //Call LCS
    std::cout << "\nSubmitting LCS with files " << file1 << " " << file2 << " of length " << n << " by " << m << std::endl;
    std::cout << std::endl;
    std::cout << "Serial LCS is " << lcs(X, Y, n, m) << std::endl;
    std::cout << "\n";
    std::cout << "Parallel LCS is " << parallel_lcs(X, Y, n, m) << std::endl;
    std::cout << "\n";
    std::cout << "Memory Efficient LCS is " << mem_parallel_lcs(X, Y, n, m) << std::endl;
    std::cout << "\n";
    return 0;
}

/******************************
 *      Helper Functions      *
 ******************************/

/**
 * Reads file and returns char vector
 * @param file - file to parse
 * @param len - length of the characters to read
 * @return - vector<char> of the parsed file
 */
std::vector<char> read(std::string file, int len){
    char c;
    int i = 0;
    std::fstream in;
    std::vector<char> tmp;

    in.open(file.c_str());

    while(in >> c){
        if(i >= len){  break; }
        tmp.push_back(c);
        i++;
    }

    in.close();
    return tmp;
}

/**
 * parallel-lcs
 * @param X - char array of LCS file 1
 * @param Y - char array of LCS file 2
 * @param n - length of LCS file 1
 * @param m - length of LCS file 2
 * @return - int - length of greatest LCS
 */
int parallel_lcs(std::vector<char> X, std::vector<char> Y, int n, int m){
    //Clear L[n + 1][m + 1] with 0's
    int L[n + 1][m + 1];

    double t0 = omp_get_wtime();
    
    //Parallel LCS implementation
    for (int i = 0; i <= (n + m - 1); i++){

	int col = std::max(0, i - n);
      	int size = std::min(i, std::min((m - col), n));

	#pragma omp parallel for
	for (int j = 0; j < size; j++){

	  int l = std::min(n, i);
	  int r = col + j;
	  int x = l - j - 1;
	  
	  //if letters are the same, propagate values down diagonally
	  if(X[x] == Y[r]){
	    if(x == 0 || r == 0){
	      L[x][r] = 1;
	    }
	    else{
	      L[x][r] =  L[x - 1][r - 1] + 1;
	    }
	  }
	  //propagate values from the max of left or top
	  else{
	    if(x == 0 && r == 0){
	      L[x][r] = 0;
	    }
	    else if(x == 0){
	      L[x][r] =  L[x][r - 1];
	    }
	    else if(r == 0){
	      L[x][r] =  L[x - 1][r];
	    }
	    else{
	      L[x][r] = std::max( L[x - 1][r],  L[x][r - 1]);
	    }
	  }

	}
    }
    
    
    double t = omp_get_wtime() - t0;

    printf("Total time: %f\n", t);

    return L[n - 1][m - 1];
}


/**
 * mem_parallel_lcs
 * @param X - char array of LCS file 1
 * @param Y - char array of LCS file 2
 * @param n - length of LCS file 1
 * @param m - length of LCS file 2
 * @return - int - length of greatest LCS
 * @desc
 * This version of the parallel LCS is a memory efficient version. 
 * instead of keeping a M * N 2d array, you have a two single 1d matrices
 * each of size M and N respectively.
 */
int mem_parallel_lcs(std::vector<char> X, std::vector<char> Y, int n, int m){
    //Largest diagonal is the max the smallest between m and n
    int max_arr = std::max(m,n);


    //Memory Efficient LCS
    int next[max_arr];
    int last[max_arr];
    
    double t0 = omp_get_wtime();
    
    //Parallel LCS implementation
    for (int i = 0; i <= (n + m - 1); i++){

    int col = std::max(0, i - n);
    int size = std::min(i, std::min((m - col), n));

    int tmp[max_arr];
    
    #pragma omp parallel for
    for (int j = 0; j < size; j++){

      int l = std::min(n, i);
      int r = col + j;
      int x = l - j - 1;
      
      //if letters are the same, propagate values down diagonally
      if(X[x] == Y[r]){
        if(x == 0 || r == 0){
          tmp[x] = 1;
        }
        else{
          tmp[x] = last[x - 1] + 1;
        }
      }
      //propagate values from the max of left or top
      else{
        if(x == 0 && r == 0){
          tmp[x] = 0;
        }
        else if(x == 0){
          tmp[x] = next[x];
        }
        else if(r == 0){
          tmp[x] = next[x - 1];
        }
        else{
          tmp[x] = std::max(next[x - 1], next[x]);
        }
      }
    }
    //copy over memory
    memcpy(last, next, sizeof last);
    memcpy(next, tmp, sizeof next);
  }
    
    
    double t = omp_get_wtime() - t0;

    printf("Total time: %f\n", t);

    return next[max_arr - 1];
}


/**
 * LCS
 * @param X - char array of LCS file 1
 * @param Y - char array of LCS file 2
 * @param n1 - length of LCS file 1
 * @param n2 - length of LCS file 2
 * @return - int - length of greatest LCS
 */
int lcs(std::vector<char> X, std::vector<char> Y, int n, int m){
  //Clear L[n + 1][m + 1] with 0's
  int L[n + 1][m + 1];
  
  double t0 = omp_get_wtime();

  //Compute LCS matrix
  for(int i = 0; i <= n; i++){
    for(int j = 0; j <= m; j++){
      if(i == 0 || j == 0){
	L[i][j] = 0;
      }
      else if(X[i - 1] == Y[j - 1]){
	L[i][j] = L[i - 1][j - 1] + 1;
      }
      else{
	L[i][j] = std::max(L[i - 1][j], L[i][j - 1]);
      }
    }
  }
  
  double t = omp_get_wtime() - t0;

  printf("Total time: %f\n", t);

  return L[n][m];
}
