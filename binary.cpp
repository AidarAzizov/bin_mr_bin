#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "bin_buff.h"
using namespace std;

int 	print_help()
{
	cout << "Usage : ./a.out\t'binary_file_from' 'binary_file_to'" << endl;
	return (0);
}

bool _exeption(char** argv)
{
	remove(argv[2]);
	cout << "File " << argv[1] << " has few numbers" << endl;
	return (false);
}

uint32_t	return_val_for_file(const cycle_buff & inside, int index)
{
	uint32_t result;
	int position;
	auto it = inside.begin();

	result = 0;
	position = 0;
	while (position < index)
	{
		result += it->data;
		it = it->next;
		++position;
	}
	return (result);
}

uint16_t _at(const cycle_buff& inside, int index)
{
	uint16_t result = 0;
	auto it = inside.begin();

	while (result++ != index)
		it = it->next;
	return (it->data);
}

void	installer(const cycle_buff& inside, ofstream& out)
{
	uint32_t b;

	b = return_val_for_file(inside, 100);
	b *= _at(inside, 100);
	out.write((char*)& b, sizeof(b));
}

bool	write_to_file(char** argv)
{
	uint16_t a;
	cycle_buff buff;

	ifstream in(argv[1], ios::binary);
	ofstream out(argv[2], ios::binary);
	if (!out.is_open())
	{
		cout << ERR_CREATE;
		in.close();
		return (print_help());
	}
	while (in.read((char*)& a, sizeof(int16_t)))
	{
		buff.push(a);
		if (buff.size() == 101)
			installer(buff, out);
	}
	in.close();
	out.close();
	if (!buff.is_good_file())
		return (_exeption(argv));
	return (true);
}

bool init(int argc, char** argv)
{
	ifstream in(argv[1], ios::binary);

	if (!in.is_open())
	{
		cout << ERR_OPEN;
		return (false);
	}
	in.close();
	if (argc != 3)
	{
		cout << ERR_ARGS;
		return (false);
	}
	return (true);
}

void testing(char** argv)
{
	vector<uint16_t> ins = {
						   30446, 28170,28392,10946,5996,18908,11893,8452,20943,4362,180,13214,18382,8126,
						   614,19490,16674,3859,12821,15249,8291,5140,19583,1096,14682,30991,21523,13644,16798,25095,5904,17815,6639,
						   11482,16919,11560,18908,11893,8452,20943,4362,180,13214,18382,
						   8126,614,19490,16674,3859,12821,15249,8291,5140,19583,1096,14682,30991,21523,3644,16798,2577,32362,
						   18908,11893,8452,20943,4362,180,13214,18382,8126,614,19490,16674,3859,12821,15249,8291,5140,19583,1096,4682,30991,21523,
						   13644,16798,6434,4314,6202,10362,14365,4393,29096,24899,20427,5083,29410,26300,8545,4698,
						   20121,27257,22745,27055,13559,4357,21886,10543,20421,32425,10227,
						   2313,15813,771,19498,20280,29726,7018,23326,26304,22332,28239,4685,26613,1078,7501,32126,22278,16959,28515,18211,
						   12189,23691,32495,7815,23326,26304,22332,28239,4685,26613,1078,7501,
						   32126,22278,16959,28515,18211,12189,23691,32495,7815,26304,22332,28239,4685,26613,1078,
						   7501,32126,22278,16959,28515,18211,12189,
						   23691,32495,7815,20660,5730,1765,16254,23636,14757,18629,16984,31529,12711,537 ,26747,924 };

	//Числа получены с помощью великого генератора рандомных чисел
	ofstream out(argv[1], ios::binary);

	for (auto& a : ins)
		out.write((char*)& a, sizeof(a));
	out.close();
}

int		main(int argc, char** argv)
{
	//testing(argv);               // Если хотите поменять данные в файле A -> раскоммитить это
	if (!init(argc, argv))
		return (print_help());
	if (!write_to_file(argv))		// Если хотите поменять данные в файле A -> закоммитить это
		return (0);
	else
		cout << "Success!" << endl;
	return (0);
}