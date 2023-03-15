#include "globalMetadata.h"
#include <QDebug>
#include<qjsondocument.h>
#include<qjsonobject.h>
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

void FetchMetaData::getGeneExpressionData(QVariantMap* geneExpressionFinalData)
{

std::string fname = ":/GeneExpression.json";


// step 1
QFile file_obj(QString::fromStdString(fname));
if (!file_obj.open(QIODevice::ReadOnly)) {
	std::cout << "Could not open the file\n";
	return;
}

// step 2
QTextStream file_text(&file_obj);
QString json_string;
json_string = file_text.readAll();
file_obj.close();

QByteArray json_bytes = json_string.toLocal8Bit();

// step 3
QJsonParseError jsonerror;

auto json_doc = QJsonDocument::fromJson(json_bytes, &jsonerror);
//qDebug() << jsonerror.errorString();

if (json_doc.isNull()) {
	std::cout << "Failed to create JSON doc." << std::endl;
	return;
}
if (!json_doc.isObject()) {
	std::cout << "JSON is not an object." << std::endl;
	return;
}

QJsonObject json_obj = json_doc.object();

if (json_obj.isEmpty()) {
	std::cout << "JSON object is empty." << std::endl;
	return;
}

// step 4
*geneExpressionFinalData = json_obj.toVariantMap();

}


