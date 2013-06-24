#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;

int main(int argc, char **argv)
{
#ifdef __APPLE__
	const string filename = "/Users/Steven/Documents/code/json/presearch.txt";
#else
    const string filename = "presearch.txt";
#endif
	ifstream search_file(filename);
	string line = "";
	array<string, 4672> search_contents;
	int counter = 0;
	if (search_file.is_open())
	{
		while (search_file.good())
		{
			getline(search_file, line);
			if (line != "")
			{
				search_contents[counter] = line;
				counter++;
			}
		}
	}
	search_file.close();
	
	counter = 0;
	array<const string, 6> feature_strings = {"CR", "LO", "PF", "SH", "ST", "WN"};
	array<string, 4672> five_or_more;
	five_or_more.fill("");
	int feat_symbol_count = 0;
	int cnt = 0;
	array<int, 4762> less_than_positions;
    less_than_positions.fill(0);
	
	for (auto it = search_contents.begin(); it != search_contents.end(); it++)
	{
		auto comp = feature_strings.begin();
		for (;comp != feature_strings.end(); comp++)
		{
			if (string::npos != (*it).find((*comp)))
			{
				feat_symbol_count++;
			}
		}
		
		if (feat_symbol_count >= 3)
		{
			five_or_more[counter] = *it;
			cnt++;
		}
		else
		{
			less_than_positions[counter]++;
		}
		feat_symbol_count = 0;
		counter++;
	}
    
#ifdef __APPLE__
    const string output_file = "/Users/Steven/Documents/code/json/outcomes.h";
#else
   const string output_file = "outcomes.h";
#endif

	ofstream output(output_file);
    for (auto s = search_contents.begin(); s != search_contents.end(); s++)
    {
        auto comp = feature_strings.begin();
		for (;comp != feature_strings.end(); comp++)
		{
			if (string::npos != (*s).find((*comp)))
			{
				feat_symbol_count++;
			}
		}
		
		if (feat_symbol_count < 3)
		{
            auto num = random() % 2 + 1;
			if (num == 2)
            {
                *s = five_or_more[random() % five_or_more.size()-1];
                cnt++;
                output << *s << endl;
            }
		}
        feat_symbol_count = 0;
    }
    output.close();
	//for (auto it =

	return 0;
}