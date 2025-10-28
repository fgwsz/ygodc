$root_path=Split-Path -Parent $MyInvocation.MyCommand.Definition
&"$root_path/clean.ps1"
&"$root_path/build.ps1"
