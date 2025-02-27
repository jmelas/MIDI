---
layout: api_page
title: MidiDeclaredStreamConfiguration
parent: Endpoint Enumeration
grand_parent: Midi2 core
has_children: false
---

# MidiDeclaredStreamConfiguration

This information is populated by the Windows Service during the MIDI 2.0 endpoint protocol negotiation process.

## Location

| Namespace | Microsoft.Windows.Devices.Midi2 |
| Library | Microsoft.Windows.Devices.Midi2 |

## Struct Fields

| Field | Description |
| --------------- | ----------- |
| `Protocol` | The agreed upon [MIDI protocol](MidiProtocolEnum.md) |
| `ReceiveJitterReductionTimestamps` | True if the endpoint is configured to receive JR timestamps |
| `SendJitterReductionTimestamps` | True if the endpoint is configured to send JR timestamps |

## IDL

[MidiDeclaredStreamConfiguration IDL](https://github.com/microsoft/MIDI/blob/main/src/app-sdk/winrt/MidiDeclaredStreamConfiguration.idl)

