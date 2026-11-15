; PaperNote Windows installer (Inno Setup 6)
; Built in CI after build_windows.bat has produced sioyek-release-windows\

#define MyAppName "PaperNote"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "PaperNote (Sioyek fork)"
#define MyAppExeName "sioyek.exe"

[Setup]
AppId={{9C1F4A52-7E8B-4C3D-9A21-5B0D8F3E6A11}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppVerName={#MyAppName} {#MyAppVersion}
DefaultDirName={localappdata}\Programs\PaperNote
DefaultGroupName=PaperNote
DisableProgramGroupPage=yes
OutputDir=..\..\dist
OutputBaseFilename=PaperNote-Setup-{#MyAppVersion}
Compression=lzma2/max
SolidCompression=yes
WizardStyle=modern
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
; install per-user so settings/config files next to the exe stay writable
PrivilegesRequired=lowest
UninstallDisplayIcon={app}\{#MyAppExeName}

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\..\sioyek-release-windows\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent
