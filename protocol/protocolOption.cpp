
#include "protocolOption.h"

#include <cmath>

ProtocolOption::ProtocolOption() {
	_control = 0b0;
	_maxSize = -1;
	_size_index = -1;
}


unsigned int ProtocolOption::maxSize() {
	return _maxSize;
}


bool ProtocolOption::append(unsigned int length, protocolType type, std::string description) {
	switch (type) {
	case SIZE: {
		_control[0] = 1;
		auto len = length * 8;
		_size_index = _optionList.size();
		_maxSize = pow(2, len) - 1;
	}
	default: {
		_Option one;
		one._description = description;
		one._length = length;
		one._type = type;
		_optionList.push_back(one);
	}
	}
	
	return true;
}


