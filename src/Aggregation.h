#pragma once
#include <iostream>
enum AggregationParamType {
	DOUBLE, INTEGER, COUNT
};

class AggregationParam {
public:
	AggregationParam(std::string value, AggregationParamType type);
	AggregationParam(double value);
	AggregationParam(int value);
	AggregationParam(std::string value);
	AggregationParamType getType();
	std::string getStringValue();
	char typeAsChar();
private:
	AggregationParamType _type;
	std::string _stringValue;
	void init(std::string value, AggregationParamType type);

};

std::ostream& operator<<(std::ostream &strm, AggregationParam &a);

class Aggregate {
public:
	static std::string AVERAGE(std::vector<std::string> &data);
	static std::string MAX(std::vector<std::string> &data);
	static std::string MIN(std::vector<std::string> &data);
	static std::string COUNT(std::vector<std::string> &data);
	static std::string COUNT_DISTINCT(std::vector<std::string> &data);
	static std::string FILTER(bool(*filter)(std::string), std::vector<std::string> &data);
	static std::string SELECT_DISTINCT(std::vector<std::string> &data);
	static std::string SUM(std::vector<std::string> &data);
	static void populateParams(std::string message, std::vector<std::vector<std::string>> &params);
	static std::string aggregate(std::string msg, std::vector<std::vector<std::string>> &params, int paramNumber, std::string(*f)(std::vector<std::string>&));
private:
	static std::string DOUBLE_MAX(std::vector<std::string> &data);
	static std::string DOUBLE_MIN(std::vector<std::string> &data);
	static std::string DOUBLE_AVERAGE(std::vector<std::string> &data);
	static std::string DOUBLE_SUM(std::vector<std::string> &data);
	static std::string INTEGER_MAX(std::vector<std::string> &data);
	static std::string INTEGER_MIN(std::vector<std::string> &data);
	static std::string INTEGER_AVERAGE(std::vector<std::string> &data);
	static std::string INTEGER_SUM(std::vector<std::string> &data);
};
