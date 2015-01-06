#include <string>
#include <sstream>
#include <regex>
#include "Aggregation.h"
#include <set>

AggregationParam::AggregationParam(std::string value, AggregationParamType type)
{
	this->_type = type;
	std::stringstream ss;
	ss << "[";
	ss << typeAsChar();
	ss << value;
	ss << "]";
	this->_stringValue = ss.str();
}
char AggregationParam::typeAsChar()
{
	switch (this->_type){
	case AggregationParamType::DOUBLE:
		return 'D';
	case AggregationParamType::INTEGER:
		return 'I';
	case AggregationParamType::COUNT:
		return 'C';
	default:
		return 'X';
	}
}
AggregationParamType AggregationParam::getType()
{
	return this->_type;
}
std::string AggregationParam::getStringValue()
{
	return this->_stringValue;
}

std::ostream& operator<<(std::ostream &strm, AggregationParam &a) {
	return strm << a.getStringValue();
}

std::string AGGREGATE_DOUBLE_AVERAGE(std::vector<std::string> &data)
{
	double sum = 0.0;
	int count = 0;
	for (std::string paramValue : data)
	{
		double d = std::stod(paramValue.substr(1));
		sum += d;
		count += 1;
	}
	double average = sum / count;
	std::stringstream ss;
	ss << average;
	return ss.str();
}

std::string AGGREGATE_DOUBLE_MAX(std::vector<std::string> &data)
{
	double max = -200000;
	for (std::string paramValue : data)
	{
		double d = std::stod(paramValue.substr(1));
		if (d > max){
			max = d;
		}
	}
	std::stringstream ss;
	ss << max;
	return ss.str();
}

std::string AGGREGATE_DOUBLE_MIN(std::vector<std::string> &data)
{
	double min = 2000000;
	for (std::string paramValue : data)
	{
		double d = std::stod(paramValue.substr(1));
		if (d < min){
			min = d;
		}
	}
	std::stringstream ss;
	ss << min;
	return ss.str();
}

std::string AGGREGATE_DOUBLE_SUM(std::vector<std::string> &data)
{
	double sum = 0;
	for (std::string paramValue : data)
	{
		double d = std::stod(paramValue.substr(1));
		sum += d;
	}
	std::stringstream ss;
	ss << sum;
	return ss.str();
}

std::string AGGREGATE_INTEGER_AVERAGE(std::vector<std::string> &data)
{
	int sum = 0;
	int count = 0;
	for (std::string paramValue : data)
	{
		int d = std::stoi(paramValue.substr(1));
		sum += d;
		count += 1;
	}
	double average = sum / count;
	std::stringstream ss;
	ss << average;
	return ss.str();
}

std::string AGGREGATE_INTEGER_MAX(std::vector<std::string> &data)
{
	int max = -200000;
	for (std::string paramValue : data)
	{
		int d = std::stoi(paramValue.substr(1));
		if (d > max){
			max = d;
		}
	}
	std::stringstream ss;
	ss << max;
	return ss.str();
}

std::string AGGREGATE_INTEGER_MIN(std::vector<std::string> &data)
{
	int min = 2000000;
	for (std::string paramValue : data)
	{
		int d = std::stoi(paramValue.substr(1));
		if (d < min){
			min = d;
		}
	}
	std::stringstream ss;
	ss << min;
	return ss.str();
}

std::string AGGREGATE_INTEGER_SUM(std::vector<std::string> &data)
{
	int sum = 0;
	for (std::string paramValue : data)
	{
		int d = std::stoi(paramValue.substr(1));
		sum += d;
	}
	std::stringstream ss;
	ss << sum;
	return ss.str();
}

std::string AGGREGATE_COUNT(std::vector<std::string> &data)
{
	if (data[0].at(0)=='X')
	{
		throw "Can only count defined AggregationParamTypes";
	}
	int count = 0;
	for (std::string paramValue : data)
	{
		count++;
	}
	std::stringstream ss;
	ss << count;
	return ss.str();
}

std::string AGGREGATE_COUNT_DISTINCT(std::vector<std::string> &data)
{
	if (data[0].at(0) == 'X')
	{
		throw "Can only count defined AggregationParamTypes";
	}
	std::set<std::string> distinctValues;
	for (std::string paramValue : data)
	{
		distinctValues.insert(paramValue);
	}
	std::stringstream ss;
	ss << distinctValues.size();
	return ss.str();
}

std::string AGGREGATE_SELECT_DISTINCT(std::vector<std::string> &data)
{
	if (data[0].at(0) == 'X')
	{
		throw "Can only count defined AggregationParamTypes";
	}
	std::set<std::string> distinctValues;
	for (std::string paramValue : data)
	{
		distinctValues.insert(paramValue);
	}
	std::stringstream ss;
	bool first = true;
	for (std::string paramValue : data)
	{
		if (!first)
		{
			ss << ", ";
		}
		ss << paramValue.substr(1);
		first = false;
	}
	return ss.str();
}

std::string AGGREGATE_FILTER(bool(*filter)(std::string), std::vector<std::string> &data)
{
	if (data[0].at(0) == 'X')
	{
		throw "Can only filter defined AggregationParamTypes";
	}
	std::set<std::string> distinctValues;
	for (std::string paramValue : data)
	{
		distinctValues.insert(paramValue);
	}
	bool first = true;
	std::stringstream ss;
	for (std::string paramValue : data)
	{
		if (!filter(paramValue)) continue;
		if (!first)
		{
			ss << ", ";
		}
		ss << paramValue.substr(1);
		first = false;
	}
	return ss.str();
}


std::string aggregate(std::string msg, std::vector<std::vector<std::string>> &params, int paramNumber, std::string(*f)(std::vector<std::string>&))
{
	std::string temp = msg;
	std::string result = msg;
	std::regex param("^(.*)\\[([DICX])(.*)\\](.*)");
	//this formatter extracts param value from above regex
	std::string extract("$3");
	//this formatter uses above param regex to cut out the param and leave rest of text for futher processing
	std::string cutOut("$1$4");
	std::string typeLetter("$2");

	int counter = 0;
	//read params from "one" text into vector
	while (std::regex_match(temp, param)){
		if (counter == paramNumber)
		{
			std::string extracted = std::regex_replace(temp, param, extract, std::regex_constants::format_default);
			std::string typeLetterString = std::regex_replace(temp, param, typeLetter, std::regex_constants::format_default);
			result = std::regex_replace(result, param, "$1<$2$3>$4", std::regex_constants::format_default);
			temp = std::regex_replace(temp, param, cutOut, std::regex_constants::format_default);
			std::stringstream regexstring;
			regexstring << "<" << typeLetterString << extracted << ">";
			result = std::regex_replace(result, std::regex(regexstring.str()), f(params[paramNumber]), std::regex_constants::format_default);
			counter++;
			break;
		}
		else
		{
			result = result;
			counter++;
		}
	}

	return result;
}


std::string AGGREGATE_AVERAGE(std::vector<std::string> &data)
{
	char typeLetter = data[0].at(0);
	switch (typeLetter)
	{
	case 'D':
		return AGGREGATE_DOUBLE_AVERAGE(data);
		break;
	case 'I':
		return AGGREGATE_INTEGER_AVERAGE(data);
		break;
	default: 
		std::stringstream ss;
		ss << "Unrecognised aggregation type: " << typeLetter << " in entry: " << data[0];
		throw ss.str();
	}
}

std::string AGGREGATE_MAX(std::vector<std::string> &data)
{
	char typeLetter = data[0].at(0);
	switch (typeLetter)
	{
	case 'D':
		return AGGREGATE_DOUBLE_MAX(data);
		break;
	case 'I':
		return AGGREGATE_INTEGER_MAX(data);
		break;
	default:
		std::stringstream ss;
		ss << "Unrecognised aggregation type: " << typeLetter << " in entry: " << data[0];
		throw ss.str();
	}
}

std::string AGGREGATE_MIN(std::vector<std::string> &data)
{
	char typeLetter = data[0].at(0);
	switch (typeLetter)
	{
	case 'D':
		return AGGREGATE_DOUBLE_MIN(data);
		break;
	case 'I':
		return AGGREGATE_INTEGER_MIN(data);
		break;
	default:
		std::stringstream ss;
		ss << "Unrecognised aggregation type: " << typeLetter << " in entry: " << data[0];
		throw ss.str();
	}
}


std::string AGGREGATE_SUM(std::vector<std::string> &data)
{
	char typeLetter = data[0].at(0);
	switch (typeLetter)
	{
	case 'D':
		return AGGREGATE_DOUBLE_SUM(data);
		break;
	case 'I':
		return AGGREGATE_INTEGER_SUM(data);
		break;
	default:
		std::stringstream ss;
		ss << "Unrecognised aggregation type: " << typeLetter << " in entry: " << data[0];
		throw ss.str();
	}
}

void populateParams(std::string message, std::vector<std::vector<std::string>> &params)
{
	//param is everyting surrounded with "[" and "]"
	std::regex param("^(.*)\\[(.*)\\](.*)");
	//this formatter extracts param value from above regex
	std::string extract("$2");
	//this formatter uses above param regex to cut out the param and leave rest of text for futher processing
	std::string cutOut("$1$3");

	std::string temp = message;

	int paramNum = 0;

	//read params from "one" text into vector
	while (std::regex_match(temp, param)){
		std::string extracted = std::regex_replace(temp, param, extract, std::regex_constants::format_default);
		if (params.size() <= paramNum)
		{
			std::vector<std::string> paramRow;
			params.push_back(paramRow);
		}
		params[paramNum].push_back(extracted);
		temp = std::regex_replace(temp, param, cutOut, std::regex_constants::format_default);
		paramNum++;
	}
}