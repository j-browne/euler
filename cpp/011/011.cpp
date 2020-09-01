#include <iostream>
#include <fstream>
using namespace std;

int main ()
{
	int nums[20][20];
	ifstream infile;
	long biggest = 0;
	
	// Read in the file.
	infile.open ("data");
	for (int i = 0; i < 20; i++)
	  {
		for (int j = 0; j < 20; j++)
		  {
			infile >> nums[i][j];
		  }
	  }
	infile.close ();

	// Horizontal
	for (int i = 0; i < 20; i++)
	  {
		for (int j = 0; j < 17; j++)
		  {
			long prod = 1;
			for (int k = 0; k < 4; k++)
			  {
				prod *= nums[i][j+k];
			  }
			if (prod > biggest)
			  {
				biggest = prod;
			  }
		  }
	  }

	// Vertical
	for (int i = 0; i < 17; i++)
	  {
		for (int j = 0; j < 20; j++)
		  {
			long prod = 1;
			for (int k = 0; k < 4; k++)
			  {
				prod *= nums[i+k][j];
			  }
			if (prod > biggest)
			  {
				biggest = prod;
			  }
		  }
	  }

	// Right-Down
	for (int i = 0; i < 17; i++)
	  {
		for (int j = 0; j < 17; j++)
		  {
			long prod = 1;
			for (int k = 0; k < 4; k++)
			  {
				prod *= nums[i+k][j+k];
			  }
			if (prod > biggest)
			  {
				biggest = prod;
			  }
		  }
	  }

	// Left-Down
	for (int i = 0; i < 17; i++)
	  {
		for (int j = 3; j < 20; j++)
		  {
			long prod = 1;
			for (int k = 0; k < 4; k++)
			  {
				prod *= nums[i+k][j-k];
			  }
			if (prod > biggest)
			  {
				biggest = prod;
			  }
		  }
	  }

	cout << biggest << endl;
	return 0;
}
