
#ifndef EnhancedUtility_h__
#define EnhancedUtility_h__

#include <cctype>
#include <algorithm>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace EnhancedUtility
{
	namespace Internal
	{

		class StaticClass
		{
		private:

			StaticClass(void);

			StaticClass(const StaticClass&);

			StaticClass& operator=(const StaticClass&);
		};
	}

	class EnhancedConverter : public Internal::StaticClass
	{
	public:

		template<typename T>
		static inline std::string toStdString(T val) {
			return std::to_string(val);
		}

		static inline int toShort(const std::string& val) {
			return ((short)(std::stoi(val)));
		}

		static inline int toUnsignedShort(const std::string& val) {
			return ((unsigned short)(std::stoi(val)));
		}

		static inline int toInt(const std::string& val) {
			return std::stoi(val);
		}

		static inline int toUnsignedInt(const std::string& val) {
			return ((unsigned int)(std::stoi(val)));
		}

		static inline int toLong(const std::string& val) {
			return std::stol(val);
		}

		static inline int toUnsignedLong(const std::string& val) {
			return std::stoul(val);
		}

		static inline long long toLongLong(const std::string& val) {
			return std::stoll(val);
		}

		static inline unsigned long long toUnsignedLongLong(const std::string& val) {
			return std::stoull(val);
		}

		static inline float toFloat(const std::string& val) {
			return std::stof(val);
		}

		static inline double toDouble(const std::string& val) {
			return std::stod(val);
		}

		static inline long double tolongDouble(const std::string& val) {
			return std::stold(val);
		}
	};

	class EnhancedString : public Internal::StaticClass
	{
	public:

		static inline std::string& trimStart(std::string& str) {
			str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(&std::isspace))));
			return str;
		}

		static inline std::string& trimEnd(std::string& str) {
			str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(&std::isspace))).base(), str.end());
			return str;
		}

		static inline std::string& trim(std::string& str) {
			return trimStart(trimEnd(str));
		}

		static inline bool startsWith(const std::string& str, const std::string& start) {
			return (str.length() >= start.length()) && (str.compare(0, start.length(), start) == 0);
		}

		static inline bool endsWith(const std::string& str, const std::string& end) {
			return (str.length() >= end.length()) && (str.compare(str.length() - end.length(), end.length(), end) == 0);
		}

		static inline bool contains(const std::string& str, const std::string& content) {
			return (str.find(content) != std::string::npos);
		}

		static inline std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
			std::stringstream ss(s);
			std::string item;
			while (std::getline(ss, item, delim)) {
				elems.push_back(item);
			}
			return elems;
		}

		static inline std::string replaceAll(const std::string& str, const std::string& replaceWhat, const std::string& replaceWith) {
			if (replaceWhat == replaceWith)
				return str;
			std::string result = str;
			std::size_t foundAt = std::string::npos;
			while ((foundAt = result.find(replaceWhat)) != std::string::npos) {
				result.replace(foundAt, replaceWhat.length(), replaceWith);
			}
			return result;
		}

		static inline void toLower(std::string& str) {
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		}

		static inline void toUpper(std::string& str) {
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		}
	};

	class EnhancedIOStream : public Internal::StaticClass
	{
	public:

		static inline std::string readAllText(const std::string& path) {
			std::string result;
			std::ifstream infile(path, std::ifstream::binary);

			if (infile) {
				infile.seekg(0, infile.end);
				long size = infile.tellg();
				infile.seekg(0);

				char* buffer = new char[size];
				infile.read(buffer, size);
				result = std::string(buffer, size);
				delete[] buffer;

				infile.close();
			}
			return result;
		}

		static inline std::vector<std::string>& readAllLines(const std::string& path, std::vector<std::string>& result) {
			std::ifstream infile(path, std::ifstream::binary);

			if (infile) {
				std::string lineContent;
				while (std::getline(infile, lineContent)) {
					result.push_back(lineContent);
				}
				infile.close();
			}

			return result;
		}

		static inline void readAllBytes(const std::string& path, unsigned char* data, size_t& dataSize) {
			if (data == nullptr) {
				return;
			}

			std::ifstream infile(path, std::ifstream::binary);

			if (infile) {
				infile.seekg(0, infile.end);
				long size = infile.tellg();
				infile.seekg(0);

				char* buffer = new char[size];
				infile.read(buffer, size);
				data = (unsigned char*)buffer;
				dataSize = size;

				infile.close();
			}
		}

		static inline void writeAllText(const std::string& path, const std::string& content) {
			std::ofstream outfile(path, std::ofstream::binary);
			outfile.write(content.c_str(), content.size());
			outfile.close();
		}

		static inline void writeAllLines(const std::string& path, const std::vector<std::string>& content) {
			std::ofstream outfile(path, std::ofstream::binary);

			auto& currentPos = content.begin();
			auto endPos = --content.end();
			while (currentPos != endPos) {
				const std::string& line = *currentPos;
				outfile.write(line.c_str(), line.size());
				outfile.write("\n", 1);
				++currentPos;
			}
			const std::string& lastline = *currentPos;
			outfile.write(lastline.c_str(), lastline.size());

			outfile.close();
		}

		static inline void writeAllBytes(const std::string& path, unsigned char* mem, const size_t& size) {
			std::ofstream outfile(path, std::ofstream::binary);
			outfile.write((char*)mem, size);
			outfile.close();
		}

		static inline void appendAllText(const std::string& path, const std::string& content) {
			std::ofstream outfile(path, std::ofstream::binary | std::ofstream::app);
			outfile.write(content.c_str(), content.size());
			outfile.close();
		}
	};
}
#endif // EnhancedUtility_h__