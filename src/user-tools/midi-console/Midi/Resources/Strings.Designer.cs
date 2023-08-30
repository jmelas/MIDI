﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace Microsoft.Devices.Midi2.ConsoleApp.Resources {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "17.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class Strings {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Strings() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("Microsoft.Devices.Midi2.ConsoleApp.Resources.Strings", typeof(Strings).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Utility application for interacting with Windows MIDI Services from the command line. Requires that Windows MIDI Services is installed and enabled on the PC..
        /// </summary>
        internal static string AppDescription {
            get {
                return ResourceManager.GetString("AppDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to [fuchsia on black]Microsoft Windows MIDI Services Console[/].
        /// </summary>
        internal static string AppTitle {
            get {
                return ResourceManager.GetString("AppTitle", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Basic testing for Windows MIDI Services.
        /// </summary>
        internal static string CommandCheckHealthDescription {
            get {
                return ResourceManager.GetString("CommandCheckHealthDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Generate a report, typically for a support request, or for use when filing a bug.
        /// </summary>
        internal static string CommandDiagnosticsReportDescription {
            get {
                return ResourceManager.GetString("CommandDiagnosticsReportDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to List MIDI UMP endpoints visible to Windows MIDI Services-aware applications.
        /// </summary>
        internal static string CommandEnumerateEndpointsDescription {
            get {
                return ResourceManager.GetString("CommandEnumerateEndpointsDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to List MIDI 1.0 endpoints as seen in apps using older MIDI APIs.
        /// </summary>
        internal static string CommandEnumerateLegacyEndpointsDescription {
            get {
                return ResourceManager.GetString("CommandEnumerateLegacyEndpointsDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Monitors a UMP endpoint for incoming messages.
        /// </summary>
        internal static string CommandMonitorEndpointDescription {
            get {
                return ResourceManager.GetString("CommandMonitorEndpointDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Send a single message to a UMP endpoint as a list of up to four 32 bit MIDI words.
        /// </summary>
        internal static string CommandSendMessageDescription {
            get {
                return ResourceManager.GetString("CommandSendMessageDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Sends a text file of UMP MIDI words to the specified endpoint. Each line in the file is a single message of 1-4 words delimited by spaces.
        /// </summary>
        internal static string CommandSendMessagesFileDescription {
            get {
                return ResourceManager.GetString("CommandSendMessagesFileDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to [darkred]Unable to create session.[/].
        /// </summary>
        internal static string ErrorUnableToCreateSession {
            get {
                return ResourceManager.GetString("ErrorUnableToCreateSession", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to [darkred]Unable to open specified endpoint.[/].
        /// </summary>
        internal static string ErrorUnableToOpenEndpoint {
            get {
                return ResourceManager.GetString("ErrorUnableToOpenEndpoint", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Perform a loopback test.
        /// </summary>
        internal static string ParameterCheckHealthLoopback {
            get {
                return ResourceManager.GetString("ParameterCheckHealthLoopback", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Instance Id of the endpoint.
        /// </summary>
        internal static string ParameterCommonInstanceIdDescription {
            get {
                return ResourceManager.GetString("ParameterCommonInstanceIdDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The direction of data flow for the endpoints to list.
        /// </summary>
        internal static string ParameterEnumEndpointsDirection {
            get {
                return ResourceManager.GetString("ParameterEnumEndpointsDirection", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Include the UMP device instance id in the output.
        /// </summary>
        internal static string ParameterEnumEndpointsIncludeInstanceId {
            get {
                return ResourceManager.GetString("ParameterEnumEndpointsIncludeInstanceId", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The direction of data flow for the endpoints to list.
        /// </summary>
        internal static string ParameterEnumLegacyEndpointsDirection {
            get {
                return ResourceManager.GetString("ParameterEnumLegacyEndpointsDirection", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Include the MIDI 1.0 device instance id in the output.
        /// </summary>
        internal static string ParameterEnumLegacyEndpointsIncludeInstanceId {
            get {
                return ResourceManager.GetString("ParameterEnumLegacyEndpointsIncludeInstanceId", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The direction of the endpoint referenced by the Id. If this doesn&apos;t match the endpoint type, the connection will fail..
        /// </summary>
        internal static string ParameterMonitorEndpointDirectionDescription {
            get {
                return ResourceManager.GetString("ParameterMonitorEndpointDirectionDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Wait for a single incoming message only.
        /// </summary>
        internal static string ParameterMonitorEndpointSingleMessage {
            get {
                return ResourceManager.GetString("ParameterMonitorEndpointSingleMessage", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Number of times to send this message.
        /// </summary>
        internal static string ParameterSendMessageCount {
            get {
                return ResourceManager.GetString("ParameterSendMessageCount", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Delay, in milliseconds, between messages. This is an approximate delay. Specify 0 for no delay..
        /// </summary>
        internal static string ParameterSendMessageDelayBetweenMessages {
            get {
                return ResourceManager.GetString("ParameterSendMessageDelayBetweenMessages", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The direction of the endpoint referenced by the Id. If this doesn&apos;t match the endpoint type, the connection will fail..
        /// </summary>
        internal static string ParameterSendMessageEndpointDirectionDescription {
            get {
                return ResourceManager.GetString("ParameterSendMessageEndpointDirectionDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Path and filename of the text file to send.
        /// </summary>
        internal static string ParameterSendMessagesFileCommandFile {
            get {
                return ResourceManager.GetString("ParameterSendMessagesFileCommandFile", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to 32-bit MIDI words, typically in hexadecimal 0x00000000 format. Use the parameter name in front of each word sent..
        /// </summary>
        internal static string ParameterSendMessageWords {
            get {
                return ResourceManager.GetString("ParameterSendMessageWords", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Creating session and opening endpoint....
        /// </summary>
        internal static string StatusCreatingSessionAndOpeningEndpoint {
            get {
                return ResourceManager.GetString("StatusCreatingSessionAndOpeningEndpoint", resourceCulture);
            }
        }
    }
}
