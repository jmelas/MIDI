// ------------------------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the GitHub project root for license information.
// ------------------------------------------------------------------------------------------------

#define WINDOWSMIDISERVICES_EXPORTS

#include "WindowsMidiServicesUtility.h"
#include "WindowsMidiServicesMessages.h"

namespace Microsoft::Windows::Midi::Messages
{
	const uint8_t Midi1PolyPressureMessage::getData()
	{
		return 0;
	}

	void Midi1PolyPressureMessage::setData(const uint8_t value)
	{
	}

	const uint8_t Midi1PolyPressureMessage::getNoteNumber()
	{
		return 0;
	}

	void Midi1PolyPressureMessage::setNoteNumber(const uint8_t value)
	{
	}

	Midi1PolyPressureMessage Midi1PolyPressureMessage::FromMidi1Bytes(const MidiGroup group, const uint8_t statusByte, const uint8_t noteNumberByte, const uint8_t dataByte)
	{
		Midi1PolyPressureMessage msg;
		return msg;

	}

	Midi1PolyPressureMessage Midi1PolyPressureMessage::FromValues(const MidiGroup group, const MidiChannel channel, const uint8_t noteNumber, const uint8_t data)
	{
		Midi1PolyPressureMessage msg;
		return msg;
	}

}