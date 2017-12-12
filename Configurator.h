#pragma once

#include "JsonParser.h"

struct Parameters {
	std::string ConfigrationName;
	std::string RGBFramePrefix, RGBFrameSufix, DepthFramePrefix, DepthFrameSufix;
	size_t FrameIndexHead, FrameIndexTail;
	size_t ICPIterationTimes;
};

class Configurator {
public:
	Configurator():m_json_parser(new JsonParser()),
   					m_valid(false)	{
	}
	virtual ~Configurator() {
		delete JsonParser();
	}

	bool IsValid(){
		return m_valid;
	}

	void ParseParametersFromJsonFile(Parameters &parameters, const char *fname) {
		m_valid = m_json_parser->ParseJson(fname);
		if (!m_valid) {
			return;
		}

		parameters.ConfigrationName = std::string(fname);
		parameters.RGBFramePrefix = m_json_parser->GetString("RGBFramePrefix");
		parameters.RGBFrameSufix = m_json_parser->GetString("RGBFrameSufix");
		parameters.DepthFramePrefix = m_json_parser->GetString("DepthFramePrefix");
		parameters.DepthFrameSufix = m_json_parser->GetString("DepthFrameSufix");
	}
protected:
	JsonParser *m_json_parser;
	bool m_valid;
};
