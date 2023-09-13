﻿using Spectre.Console.Cli;
using Spectre.Console;
using System.Runtime.Versioning;

using Microsoft.Devices.Midi2.ConsoleApp;
using Microsoft.Devices.Midi2.ConsoleApp.Resources;
using Windows.Gaming.Input.ForceFeedback;
using Windows.Devices.Midi2;
using Microsoft.Devices.Midi2.ConsoleApp;

var app = new CommandApp();

app.Configure(config =>
{
    config.SetApplicationName("midi");
    config.ValidateExamples();
    config.CaseSensitivity(CaseSensitivity.None);


    config.AddBranch("enumerate", enumerate =>
    {
        enumerate.SetDescription(Strings.CommandEnumerateDescription);

        enumerate.AddCommand<EnumEndpointsCommand>("endpoints")
            .WithDescription(Strings.CommandEnumerateEndpointsDescription)
            .WithExample("enumerate", "endpoints", "--direction", "all")
            ;

        enumerate.AddCommand<EnumLegacyEndpointsCommand>("legacy-endpoints")
            .WithAlias("legacy")
            .WithDescription(Strings.CommandEnumerateLegacyEndpointsDescription)
            .WithExample("enumerate", "legacy-endpoints", "--direction", "all")
            ;

        // TODO: may want to change this to just "plugins" and offer a switch
        // for the type of plugins to show
        enumerate.AddCommand<EnumTransportsCommand>("transport-plugins")
            .WithAlias("transports")
            .WithDescription(Strings.CommandEnumerateTransportPluginsDescription)
            .WithExample("enumerate", "transport-plugins")
            ;
    }).WithAlias("list")
    .WithAlias("enum");


    
    config.AddBranch("service", service =>
    {
        service.SetDescription(Strings.CommandServiceDescription);

        service.AddCommand<ServiceStatusCommand>("status")
            .WithDescription(Strings.CommandServiceStatusDescription)
            .WithExample("service", "status")
            ;

        service.AddCommand<ServicePingCommand>("ping")
            .WithDescription(Strings.CommandServicePingDescription)
            .WithExample("service", "ping", "--count", "10", "--timeout", "5000", "--verbose")
            ;
    }).WithAlias("svc");



    config.AddBranch<EndpointCommandSettings>("endpoint", endpoint =>
    {
        endpoint.SetDescription(Strings.CommandEndpointDescription);

        endpoint.AddCommand<MonitorEndpointCommand>("monitor")
            .WithAlias("monitor")
            .WithAlias("listen")
            .WithExample("endpoint", "\\\\?\\SWD#MIDISRV#MIDIU_DEFAULT_LOOPBACK_BIDI_A#{e7cce071-3c03-423f-88d3-f1045d02552b}", "monitor")
            .WithDescription(Strings.CommandMonitorEndpointDescription)
            ;

        endpoint.AddCommand<SendMessageCommand>("send-message")
            .WithAlias("send-ump")
            .WithExample("endpoint", "\\\\?\\SWD#MIDISRV...}", "send-message", "0x405F3AB7", "0x12345789", "--count", "10", "--delay", "20")
            .WithDescription(Strings.CommandSendMessageDescription)
            ;

        endpoint.AddCommand<SendMessagesFileCommand>("send-message-file")
            .WithAlias("send-ump-file")
            .WithAlias("send-file")
            .WithExample("endpoint", "\\\\?\\SWD#MIDISRV...}", "send-message-file", "%USERPROFILE%\\Documents\\messages.txt")
            .WithDescription(Strings.CommandSendMessagesFileDescription)
            ;


        endpoint.AddCommand<CaptureMessagesCommand>("capture")
            .WithAlias("record")
            .WithExample("endpoint", "\\\\?\\SWD#MIDISRV...}", "capture", "%USERPROFILE%\\Documents\\capture.txt", "--echo", "--annotate")
            .WithExample("endpoint", "\\\\?\\SWD#MIDISRV...}", "capture", "capture.csv", "--delimiter", "Comma")
            .WithExample("endpoint", "\\\\?\\SWD#MIDISRV...}", "capture", "capture.txt", "--format", "HexWithPrefix", "--filter", "SysEx8")
            .WithDescription(Strings.CommandMonitorEndpointDescription)
            ;


    }).WithAlias("ep");



    config.AddCommand<DiagnosticsReportCommand>("diagnostics-report")
        .WithAlias("report")
        .WithDescription(Strings.CommandDiagnosticsReportDescription)
        .WithExample("diagnostics-report", "%USERPROFILE%\\Documents\\report.txt")
        ;
});

// app title
AnsiConsole.WriteLine();
AnsiConsole.MarkupLine(AnsiMarkupFormatter.FormatAppTitle(Strings.AppTitle));
AnsiConsole.WriteLine();

if (args.Length == 0)
{
    // show app description only when no arguments supplied

    AnsiConsole.MarkupLine(AnsiMarkupFormatter.FormatAppDescription(Strings.AppDescription));
    AnsiConsole.WriteLine();
}

return app.Run(args);
