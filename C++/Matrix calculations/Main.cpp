#include <iostream>
#define WIDTH 3
#define HEIGHT 3
#include "matrix.h"

using namespace std;

int main() {
		int matrix [3][3];
		int n;
		int m;

  for (n=0; n<HEIGHT; n++)
    for (m=0; m<WIDTH; m++)
    {
      matrix[n][m]=(n+1)*(m+1);
    }

	for (n=0; n<HEIGHT; n++)
		for (m=0; m<WIDTH; m++){
		matrix[n][m] = matrix[n][m] + matrix[n][m];
		}
	return 0;
}