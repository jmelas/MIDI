﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Microsoft.Windows.Midi.Internal.Config.Schema
{
    public class Locations
    {
        public string MainAppFolder { get; set; }

        public string SetupsFolder { get; set; }

        public string PluginsFolder { get; set; }

        public string IconsFolder { get; set; }
    }
}
