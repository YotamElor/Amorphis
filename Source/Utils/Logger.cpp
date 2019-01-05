#include "Logger.hpp"
#include <BWAPI.h>

using namespace std;


namespace Amorphis {


	Logger* Logger::m_instance = NULL;


	Logger* Logger::getInstance()
	{
		if (m_instance == NULL) {
			m_instance = new Logger();
		}
		return m_instance;
	}


	void Logger::init()
	{
		m_ofs = ofstream("bwapi-data/log/Amorphis.txt");
	}


	void Logger::log(const std::string &s)
	{
		m_ofs << "[" << BWAPI::Broodwar->getFrameCount() << "] " << s.c_str() << "\n";
		m_ofs.flush();
	}

	void Logger::err(const std::string &s)
	{
		log(s);
		throw(0);
	}

	Logger::~Logger()
	{
		m_ofs.close();
	}

}