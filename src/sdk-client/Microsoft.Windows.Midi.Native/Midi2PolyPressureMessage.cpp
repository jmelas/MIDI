// ------------------------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the GitHub project root for license information.
// ------------------------------------------------------------------------------------------------

#define WINDOWSMIDISERVICES_EXPORTS

#include "WindowsMidiServicesUtility.h"
#include "WindowsMidiServicesMessages.h"

namespace Microsoft::Windows::Midi::Messages
{

	const uint8_t Midi2PolyPressureMessage::getNoteNumber()
	{
		return 0;
	}

	void Midi2PolyPressureMessage::setNoteNumber(const uint8_t value)
	{
	}

	const uint32_t Midi2PolyPressureMessage::getData()
	{
		return 0;
	}

	void Midi2PolyPressureMessage::setData(const uint32_t value)
	{
	}

	Midi2PolyPressureMessage Midi2PolyPressureMessage::FromValues(const MidiGroup group, const MidiChannel channel, const uint8_t noteNumber, const uint32_t data)
	{
		Midi2PolyPressureMessage msg;
		return msg;
	}


}