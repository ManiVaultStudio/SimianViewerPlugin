#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <QFile>
#include <QTextStream>
class FetchMetaData
{


public:
	FetchMetaData();

	void  getData(std::vector<std::vector<std::string>>* simianData);

};