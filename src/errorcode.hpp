#ifndef DXNA_ERRORCODE_HPP
#define DXNA_ERRORCODE_HPP

namespace dxna {

	//LE - Less than or Equal to
	//GE - Greater than or Equal to

	enum class ErrorCode {
		NONE,
		ARGUMENT_IS_NULL,
		ARGUMENT_IS_SMALLER,
		ARGUMENT_OUT_OF_RANGE,	

		ARGUMENT_LESS_OR_EQUAL_ZERO,
		ARGUMENT_LE_ZERO_OR_GE_PI,
		ARGUMENT_GREATER_OR_EQUAL_OTHER,

		CS_STREAM_IS_NULL,
	};
}

#endif