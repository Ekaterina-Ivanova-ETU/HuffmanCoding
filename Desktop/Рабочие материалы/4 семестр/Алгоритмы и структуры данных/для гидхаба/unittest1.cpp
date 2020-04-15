#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Huffman_coding/Huffman_binTree.h"
#include "../Huffman_coding/QuickSort.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		Huffaman_binTree test_HufCoding;
		string decoded_string_for_testing = "it is test string", 
			coded_string_for_testing = "110011111100011101100000011110001100111010111010", empty_string = "";
		float size1 = 136, size2 = 48;

	public:
		TEST_METHOD_INITIALIZE(init)
		{
			test_HufCoding.creating_symbol_and_code_table(decoded_string_for_testing);
		}

		TEST_METHOD(exception_create_table_of_symbols_and_their_codes)
		{
			try
			{
				test_HufCoding.creating_symbol_and_code_table(empty_string);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("The entered string is empty.", ex.what());
			}
		}
		TEST_METHOD(_coding)
		{
			Assert::AreEqual(test_HufCoding.coding(decoded_string_for_testing), coded_string_for_testing);
		}

		TEST_METHOD(exception_coding)
		{
			try
			{
				test_HufCoding.coding(empty_string);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("No symbol and code table created or the entered string is empty.", ex.what());
			}
		}

		TEST_METHOD(_decoding)
		{
			Assert::AreEqual(test_HufCoding.decoding(coded_string_for_testing), decoded_string_for_testing);
		}

		TEST_METHOD(exception_decoding)
		{
			try
			{
				test_HufCoding.decoding(empty_string);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("No symbol and code table created or the entered string is empty.", ex.what());
			}
		}

		TEST_METHOD(_size_CodedString)
		{
			Assert::AreEqual(test_HufCoding.size_CodedString(coded_string_for_testing), (float)48);
			Assert::AreEqual(test_HufCoding.size_CodedString(empty_string), (float)0);
		}

		TEST_METHOD(_size_DecodedString)
		{
			Assert::AreEqual(test_HufCoding.size_DecodedString(decoded_string_for_testing), (float)136);
			Assert::AreEqual(test_HufCoding.size_DecodedString(empty_string), (float)0);
		}
	};
}