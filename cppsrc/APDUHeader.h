/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#ifndef OPENDNP3_APDUHEADER_H
#define OPENDNP3_APDUHEADER_H

#include "opendnp3/gen/FunctionCode.h"
#include "opendnp3/app/AppControlField.h"
#include "opendnp3/app/IINField.h"

namespace opendnp3
{

struct APDUHeader
{
	static const uint32_t REQUEST_SIZE = 2;
	static const uint32_t RESPONSE_SIZE = 4;

	static APDUHeader SolicitedConfirm(uint8_t seq);
	static APDUHeader UnsolicitedConfirm(uint8_t seq);
	static APDUHeader Confirm(uint8_t seq, bool unsolicited);

	APDUHeader() = default;

	APDUHeader(
	    const AppControlField& control,
	    FunctionCode function
	) :
		control(control),
		function(function)
	{}

	bool Equals(const APDUHeader& header) const
	{
		return (header.function == function) && (header.control.ToByte() == control.ToByte());
	}

	AppControlField control;
	FunctionCode function = FunctionCode::UNKNOWN;
};

struct APDUResponseHeader : public APDUHeader
{
	APDUResponseHeader() = default;

	APDUResponseHeader(
	    const AppControlField& control,
	    FunctionCode function,
	    const IINField& IIN
	) :
		APDUHeader(control, function),
		IIN(IIN)
	{}

	IINField IIN;
};

}

#endif
