#include "C:\Users\Екатерина Иванова\source\repos\map_v4\map_v4\map.h"
#include "Huffman_coding.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	string string_for_coding, coded_string, decoded_string;
	cout << "ENTER TEXT TO BE ENCODED" << endl;
	getline(cin, string_for_coding);

	Huffaman_coding HufCode;
	HufCode.creating_symbol_and_code_table(string_for_coding);

	coded_string = HufCode.coding(string_for_coding);
	cout << endl << "The coded text: " << endl << coded_string << endl
		<< "The volume of the occupied memory: " << HufCode.size_CodedString(coded_string) << " bit." << endl;

	decoded_string = HufCode.decoding(coded_string);
	cout << endl << "The decoded text: " << endl << decoded_string << endl
		<< "The volume of the occupied memory: " << HufCode.size_DecodedString(decoded_string) << " bit." << endl;

	cout << endl << "Compression ratio = " << HufCode.size_CodedString(coded_string) / HufCode.size_DecodedString(decoded_string) << endl;

	system("pause");
	return 0;
}