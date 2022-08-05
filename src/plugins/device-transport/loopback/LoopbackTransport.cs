﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using Microsoft.Windows.Midi.Messages;
using Microsoft.Windows.Midi.PluginModel;

namespace LoopbackPlugin
{
    public class LoopbackTransport : IMidiPlugin, IMidiTransport
    {
        public MidiPluginType PluginType => throw new NotImplementedException();

        public string PluginAuthor => throw new NotImplementedException();

        public string PluginIconFileName => throw new NotImplementedException();

        public string PluginDescription => throw new NotImplementedException();

        public Version PluginVersion => throw new NotImplementedException();

        public Guid Id { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        public string ShortName => throw new NotImplementedException();

        public string FullName => throw new NotImplementedException();

        public string IconFileName => throw new NotImplementedException();

        public string Description => throw new NotImplementedException();



        // TODO: These need to use a type that C++ plugin devs will ahve access
        // to, like an IBuffer or something. .NET Streams aren't likely the
        // best choice here. Also need to eval how the USB driver will work before
        // settling on this interface. Don't want to use C++/CLI, but WinRT types
        // and other COM-known types are an option.
        // Also consider Span<T> and how that could be used here.

        ///// <summary>
        ///// MIDI Out (from apps, to device)
        ///// </summary>
        //public void WriteDataFromStream(Stream sourceStream, Guid endpointId)
        //{
        //    throw new NotImplementedException();
        //}

        ///// <summary>
        ///// MIDI In (from device, to apps)
        ///// </summary>
        //public void ReadDataFromStream(Stream sourceStream, Guid endpointId)
        //{
        //    throw new NotImplementedException();
        //}


        // TODO: Test performance and move to one of a number of shared memory approaches
        // if performance here isn't what it needs to be
        public void WriteToDevice(Guid endpointId, IList<Ump> messageBufferToWrite)
        {
            throw new NotImplementedException();
        }

        public void ReadFromDevice(Guid endpointId, IList<Ump> messageBufferToFill)
        {
            throw new NotImplementedException();
        }


        //public void WriteToDevice(Guid endpointId, Ump messageToWrite)
        //{
        //    throw new NotImplementedException();
        //}

        //public void ReadFromDevice(Guid endpointId, out Ump messageToWrite)
        //{
        //    throw new NotImplementedException();
        //}


    }
}