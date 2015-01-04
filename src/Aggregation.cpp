#include <string>
#include <sstream>
#include <regex>
std::string AVERAGE_DOUBLE(std::string msg, std::vector<std::vector<std::string>> &params, int paramNumber)
{
	std::string temp = msg;
	std::string result = msg;
	std::regex param("^(.*)\\[(.*)\\](.*)");
	//this formatter extracts param value from above regex
	std::string extract("$2");
	//this formatter uses above param regex to cut out the param and leave rest of text for futher processing
	std::string cutOut("$1$3");

	int counter = 0;
	//read params from "one" text into vector
	while (std::regex_match(temp, param)){
		if (counter == paramNumber)
		{
			std::string extracted = std::regex_replace(temp, param, extract, std::regex_constants::format_default);
			result = std::regex_replace(result, param, "$1<$2>$3", std::regex_constants::format_default);
			double sum = 0.0;
			int count = 0;
			for (std::vector<std::string> paramsRow : params)
			{
				//we average first param (0), but the order is reversed, so we grab the last
				double d = std::stod(paramsRow[counter]);
				sum += d;
				count += 1;
			}
			double average = sum / count;
			std::stringstream ss;
			ss << average;
			temp = std::regex_replace(temp, param, cutOut, std::regex_constants::format_default);
			std::stringstream regexstring;
			regexstring << "<" << extracted << ">";

			result = std::regex_replace(result, std::regex(regexstring.str()), ss.str(), std::regex_constants::format_default);
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

std::string AGGREGATION_PARAM(std::string input)
{
	std::stringstream ss;
	ss << "[" << input << "]";
	return ss.str();
}
std::string MAX_DOUBLE(std::string msg, std::vector<std::vector<std::string>> &params, int paramNumber)
{
	std::string temp = msg;
	std::string result = msg;
	std::regex param("^(.*)\\[(.*)\\](.*)");
	//this formatter extracts param value from above regex
	std::string extract("$2");
	//this formatter uses above param regex to cut out the param and leave rest of text for futher processing
	std::string cutOut("$1$3");


	int counter = 0;
	//read params from "one" text into vector
	while (std::regex_match(temp, param)){
		if (counter == paramNumber)
		{
			std::string extracted = std::regex_replace(temp, param, extract, std::regex_constants::format_default);
			result = std::regex_replace(result, param, "$1<$2>$3", std::regex_constants::format_default);
			std::regex_search(temp, param);
			double max = -2000000.0;
			for (std::vector<std::string> paramsRow : params)
			{
				//we average first param (0), but the order is reversed, so we grab the last
				double d = std::stod(paramsRow[counter]);
				if (d > max) max = d;
			}
			std::stringstream ss;
			ss << max;
			temp = std::regex_replace(temp, param, cutOut, std::regex_constants::format_default);
			std::stringstream regexstring;
			regexstring << "<" << extracted << ">";

			result = std::regex_replace(result, std::regex(regexstring.str()), ss.str(), std::regex_constants::format_default);
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
std::string MIN_DOUBLE(std::string msg, std::vector<std::vector<std::string>> &params, int paramNumber)
{
	std::string temp = msg;
	std::string result = msg;
	std::regex param("^(.*)\\[(.*)\\](.*)");
	//this formatter extracts param value from above regex
	std::string extract("$2");
	//this formatter uses above param regex to cut out the param and leave rest of text for futher processing
	std::string cutOut("$1$3");


	int counter = 0;
	//read params from "one" text into vector
	while (std::regex_match(temp, param)){
		if (counter == paramNumber)
		{
			std::string extracted = std::regex_replace(temp, param, extract, std::regex_constants::format_default);
			result = std::regex_replace(result, param, "$1<$2>$3", std::regex_constants::format_default);
			double min = 2000000;
			for (std::vector<std::string> paramsRow : params)
			{
				//we average first param (0), but the order is reversed, so we grab the last
				double d = std::stod(paramsRow[counter]);
				if (d < min) min = d;
			}
			std::stringstream ss;
			ss << min;
			temp = std::regex_replace(temp, param, cutOut, std::regex_constants::format_default);

			std::stringstream regexstring;
			regexstring << "<" << extracted << ">";

			result = std::regex_replace(result, std::regex(regexstring.str()), ss.str(), std::regex_constants::format_default);
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
std::string SUM_DOUBLE(std::string msg, std::vector<std::vector<std::string>> &params, int paramNumber)
{
	std::string temp = msg;
	std::string result = msg;
	std::regex param("^(.*)\\[(.*)\\](.*)");
	//this formatter extracts param value from above regex
	std::string extract("$2");
	//this formatter uses above param regex to cut out the param and leave rest of text for futher processing
	std::string cutOut("$1$3");


	int counter = 0;
	//read params from "one" text into vector
	while (std::regex_match(temp, param)){
		if (counter == paramNumber)
		{
			std::string extracted = std::regex_replace(temp, param, extract, std::regex_constants::format_default);
			result = std::regex_replace(result, param, "$1<$2>$3", std::regex_constants::format_default);
			double sum = 0;
			for (std::vector<std::string> paramsRow : params)
			{
				//we average first param (0), but the order is reversed, so we grab the last
				double d = std::stod(paramsRow[counter]);
				sum += d;
			}
			std::stringstream ss;
			ss << sum;
			temp = std::regex_replace(temp, param, cutOut, std::regex_constants::format_default);

			std::stringstream regexstring;
			regexstring << "<" << extracted << ">";

			result = std::regex_replace(result, std::regex(regexstring.str()), ss.str(), std::regex_constants::format_default);
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