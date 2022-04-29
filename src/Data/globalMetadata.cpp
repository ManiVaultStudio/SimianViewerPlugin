#include "globalMetadata.h"

FetchMetaData::FetchMetaData()
{

}

void FetchMetaData::getData(std::vector<std::vector<std::string>>* simianData)
{

	std::vector<std::string> row;
	std::string  word;
	std::string fname = ":/fullDataSimian.csv";
	QFile file(QString(fname.c_str()));

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		std::cout << "Could not open the file\n";
		return;
	}

	QTextStream in(&file);
	QString line = in.readLine();
	while (!line.isNull()) {
		line = in.readLine();
		if (line.isEmpty()) 
		{ 
			continue; 
		}
		row.clear();
		std::stringstream str(line.toStdString());
		while (getline(str, word, ','))
		{
			row.push_back(word);
		}

		simianData->push_back(row);
		
	}
}


