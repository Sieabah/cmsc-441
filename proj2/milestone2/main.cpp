/**
 * @author: Joshua Standiford
 * @description:
 * Project 2 - LCS program
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;
/******************************
 *     Function Prototypes    *
 ******************************/


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
    std::cout << "LCS is " << lcs(X, Y, n, m) << std::endl;
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
    std::vector<char> LCS;


    for(int b = 0; b <= n; b++){
	for(int d = 0; d <= m; d++){
	  L[b][d] = 0;
	}
      }


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

    // Print table

    std::cout << std::endl;

    std::cout << " Matrix Visualization " << std::endl;
    std::cout << "  ";
    for(int k = 0; k < n; k++){
        std::cout << X[k] << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i <= m; i++){
        std::cout << Y[i] << " ";
        for(int j = 0; j <= n; j++){
            std::cout << L[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    //print matrix diagonally
    for (int line=1; line<=(m + n); line++){

        int start_col =  std::max(0, line-n);


        int count = std::min(line, std::min((n-start_col), n));


        for (int j=0; j<count; j++)
            printf("%5d ", L[std::min(n, line)-j-1][start_col+j]);


        printf("\n");
    }
     
    std::cout << std::endl;
    return L[n][m];
}
