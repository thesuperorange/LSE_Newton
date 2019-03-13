# include "systemfunction.h"

long countLine(string filename) {
	//readfile
	fstream file;
	string line;

	file.open(filename);
	long line_count;
	for (line_count = 0; getline(file, line); ++line_count)
		;

	file.close();
	return line_count;
}


void readFile(string filename, long line_count, float* x, float** y) {

	fstream file;
	string line;
	file.open(filename);
	int idx = 0;
	while (getline(file, line, '\n'))  //newline
	{
		istringstream templine(line); // string to stream
		string data;
		int xy_idx = 0;
		while (getline(templine, data, ',')) //comma as delimiter
		{

			if (xy_idx == 0) {
				x[idx] = atof(data.c_str());
				//cout << "##" << idx << " " << xy_idx << " : " << atof(data.c_str());
			}
			else if (xy_idx == 1) y[idx][0] = atof(data.c_str());

			xy_idx++;
		}
		idx++;
	}
	file.close();
}