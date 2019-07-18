#include <iostream>
#include <fstream>

struct File_Reader
{
	std::fstream fread;
	std::fstream fread_1;
	const char* file_name;
	const char* file_name_1;
	File_Reader(const char* file, const char* file_1) 
	{
		file_name = file;
		file_name_1 = file_1;
		fread.open(file, std::ios::in | std::ios::out);
		fread_1.open(file_1, std::ios::in | std::ios::out);
		if(!fread.is_open())
		{
			std::cout << "Reading Error" ; 
		}			
     		else
		{
			std::cout << "Keep working\n";
		}
		if(!fread_1.is_open())
		{
			std::cout << "Reading Error";
		}	
		else
		{
			std::cout << "Keep working\n";
		}
	}
	bool read_digit(int& digit) 
	{
		return (fread >> digit ? true : false);
	}
	bool read_digit_1(int& digit_1) 
	{
		return (fread_1 >> digit_1 ? true : false);
	}
	~File_Reader() 
	{
		fread.close();
	}
};

void parameters(unsigned int& R, unsigned int& C, unsigned int& Q) 
{
	std::cout << "Enter the Matrix parameters for compare" << std::endl;
       	std::cout << "Rows = ";  	 
       	std::cin >> R;	
     	std::cout << "Columns = ";
	std::cin >> C;
	std::cout << "Enter the quantity of Matrices in each file" << std::endl;
	std::cout << "Quantity = ";
	std::cin >> Q;
}

struct Matrix_Compare
{
	int* array;
	unsigned int rows;
	unsigned int columns;
	Matrix_Compare(const unsigned int R_rows, const unsigned int C_columns) 
	{
		rows = R_rows;
		columns = C_columns;
		array = new int [rows * columns];
	}
	int get_Rows() 
	{
		return rows;
	}
	int get_Columns() 
	{
		return columns;
	}
	int& operator() (const unsigned int i, const unsigned int j) 
	{
		return array[i * j];
	}
	~Matrix_Compare() 
	{
		delete [] array;
	}
};

bool file_Compare(Matrix_Compare& a, Matrix_Compare& b, File_Reader& read_f) 
{
	int i, j, digit = 0, digit_1 = 0, count = 0;
	for(i = 0; i < a.get_Rows(); ++i) 
	{
		for(j = 0; j < a.get_Columns(); ++j) 
		{
			read_f.read_digit(digit);
			read_f.read_digit_1(digit_1);
			a(i, j) = digit;
			b(i, j) = digit_1;
			if(a(i, j) != b(i, j)) 
			{
				char colred[] = { 0x1b, '[', '1', ';','3', '1', 'm', 0 };
				char colblue[] = { 0x1b, '[', '1', ';','3', '4', 'm', 0 };
				char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
				std::cout << colblue << "\t" <<"In those Matrices the matrix("<< i 
						  << ", " << j << ") elements  " << normal << colred << a(i, j) 
						  << " != " << b(i, j) << normal << colblue << " are different"
						  << normal << std::endl;
				++count;
			}
		       	else
		       	{
				count;
			}
		}
	}
	std::cout << "\nfound " << count << " difference\n" << std::endl;
	return true;
}

int main() 
{
	unsigned int R = 0, C = 0, Q = 0;
	File_Reader read_x("My_file.txt", "base_file.txt");
	parameters(R, C, Q);
	Matrix_Compare a(R, C), b(R, C);
	for(int i = 0; i < Q; ++i) 
	{
		file_Compare(a, b, read_x);
	}

	return 0;
}
