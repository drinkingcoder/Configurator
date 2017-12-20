#pragma once

#include "JsonParser.h"

template<typename Parameters>
class Configurator {
public:
	Configurator():m_json_parser(new JsonParser()),
   					m_valid(false)	{
	}
	virtual ~Configurator() {
		delete m_json_parser;
	}

	bool IsValid(){
		return m_valid;
	}

	virtual void ParseParametersFromJsonFile(Parameters &parameters, const char *fname) = 0;
protected:
	JsonParser *m_json_parser;
	bool m_valid;
};
