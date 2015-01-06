#pragma once
#include <iostream>
enum AggregationParamType {
	DOUBLE, INTEGER, COUNT
};

class AggregationParam {
public:
	AggregationParam(std::string value, AggregationParamType type);
	AggregationParamType getType();
	std::string getStringValue();
	char typeAsChar();
private:
	AggregationParamType _type;
	std::string _stringValue;

};

std::ostream& operator<<(std::ostream &strm, AggregationParam &a);

void populateParams(std::string message, std::vector<std::vector<std::string>> &params);

std::string aggregate(std::string msg, std::vector<std::vector<std::string>> &params, int paramNumber, std::string(*f)(std::vector<std::string>&));

std::string AGGREGATE_AVERAGE(std::vector<std::string> &data);

std::string AGGREGATE_MAX(std::vector<std::string> &data);

std::string AGGREGATE_MIN(std::vector<std::string> &data);

std::string AGGREGATE_COUNT(std::vector<std::string> &data);

std::string AGGREGATE_COUNT_DISTINCT(std::vector<std::string> &data);

std::string AGGREGATE_FILTER(bool(*filter)(std::string), std::vector<std::string> &data);

std::string AGGREGATE_SELECT_DISTINCT(std::vector<std::string> &data);

std::string AGGREGATE_SUM(std::vector<std::string> &data);
