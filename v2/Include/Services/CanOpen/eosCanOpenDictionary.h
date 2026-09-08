#pragma once
#ifndef __eosCanOpenDictionary__
#define __eosCanOpenDictionary__


#include "eos.h"


#define VAR_RW_BOOL(index, subIndex, data) \
	{index, subIndex, eos::CoType::boolean, eos::CoAccess::rwVariable, (uint32_t)(& data)}
#define VAR_RW_U8(index, subIndex, data) \
	{index, subIndex, eos::CoType::unsigned8, eos::CoAccess::rwVariable, (uint32_t)(& data)}
#define VAR_RW_U16(index, subIndex, data) \
	{index, subIndex, eos::CoType::unsigned16, eos::CoAccess::rwVariable, (uint32_t)(& data)}
#define VAR_RW_U32(index, subIndex, data) \
	{index, subIndex, eos::CoType::unsigned32, eos::CoAccess::rwVariable, (uint32_t)(& data)}

#define VAR_RO_BOOL(index, subIndex, data) \
	{index, subIndex, eos::CoType::boolean, eos::CoAccess::roVariable, (uint32_t)(& data)}
#define VAR_RO_U8(index, subIndex, data) \
	{index, subIndex, eos::CoType::unsigned8, eos::CoAccess::roVariable, (uint32_t)(& data)}
#define VAR_RO_U16(index, subIndex, data) \
	{index, subIndex, eos::CoType::unsigned16, eos::CoAccess::roVariable, (uint32_t)(& data)}
#define VAR_RO_U32(index, subIndex, data) \
	{index, subIndex, eos::CoType::unsigned32, eos::CoAccess::roVariable, (uint32_t)(& data)}

#define CONST_BOOL(index, subIndex, data) \
	{index, subIndex, eos::CoType::boolean, eos::CoAccess::constant, data}
#define CONST_U8(index, subIndex, data) \
	{index, subIndex, eos::CoType::unsigned8, eos::CoAccess::constant, data}
#define CONST_U16(index, subIndex, data) \
	{index, subIndex, eos::CoType::unsigned16, eos::CoAccess::constant, data}
#define CONST_U32(index, subIndex, data) \
	{index, subIndex, eos::CoType::unsigned32, eos::CoAccess::constant, data}

#define EV_RW_U8(index, subIndex) \
	{index, subIndex, eos::CoType::unsigned8, eos::CoAccess::rwEvent, 0}
#define EV_RW_U16(index, subIndex) \
	{index, subIndex, eos::CoType::unsigned16, eos::CoAccess::rwEvent, 0}
#define EV_RW_U32(index, subIndex) \
	{index, subIndex, eos::CoType::unsigned32, eos::CoAccess::rwEvent, 0}

#define EV_RO_U8(index, subIndex) \
	{index, subIndex, eos::CoType::unsigned8, eos::CoAccess::roEvent, 0}
#define EV_RO_U16(index, subIndex) \
	{index, subIndex, eos::CoType::unsigned16, eos::CoAccess::roEvent, 0}
#define EV_RO_U32(index, subIndex) \
	{index, subIndex, eos::CoType::unsigned32, eos::CoAccess::roEvent, 0}

#define ARRAY(index, elements) \
		{index, 0, eos::CoType::unsigned8, eos::CoAccess::constant, elements}


#endif // __eosCanOpenDictionary__
