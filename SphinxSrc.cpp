#include <iostream>
#include <fstream> //Needed anytime a program performs file input/output
using namespace std;


int main()
{
	//Using pdftotext tool downloaded through xpdf to convert the pdf to textformat.
	

	//string textbook_name = "molecularcellbiology.pdf";
	int terminal_return_code;
	terminal_return_code = system("pdftotext -raw -nopgbrk textbook.pdf");

	return 0;
}