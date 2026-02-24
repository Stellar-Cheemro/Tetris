; =====================================================================
; Tetris 游戏打包脚本
; =====================================================================

; 定义基本信息
#define MyAppName "Tetris"
#define MyAppVersion "1.0"
#define MyAppExeName "Tetris.exe" ; <--- 这里填刚才编译出的新名字
#define MyAppPublisher "Stellar"
#define ProjectRoot "D:/Code/Project/cpp/Game/Tetris_by_Gyro_Cheemse_exeTest/release_build"      ; 指向当前脚本所在的目录

[Setup]
; --- 核心配置 ---
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}

; --- 允许用户选择安装路径 (关键点) ---
; DisableDirPage=no 代表“不禁用目录选择页”，即“显示选择页”
DisableDirPage=no
; 默认安装路径 (推荐放在 Program Files 下)
DefaultDirName={autopf}\{#MyAppName}

; --- 安装包外观 ---
; 这里的 game.ico 用于“安装程序本身”的图标
SetupIconFile={#ProjectRoot}\res\icon\rain.ico
; 生成的安装包名字
OutputBaseFilename=Tetris_Setup
; 生成位置
OutputDir={#ProjectRoot}\build_setup

; --- 压缩配置 ---
Compression=lzma2
SolidCompression=yes
; 安装后是否需要重启 (游戏通常不需要)
RestartIfNeededByRun=no

[Languages]
; 设置安装向导为中文 (如果你的 Inno Setup 没有中文包，默认用 English 即可)
Name: "chinesesimp"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Files]
; 1. 打包主程序
; 注意：Source 这里要对应你 bin 目录下的真实文件名
Source: "{#ProjectRoot}\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion

; 2. 打包资源文件夹 (包含所有子文件夹)
Source: "{#ProjectRoot}\res\*"; DestDir: "{app}\res"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#ProjectRoot}\Document\*"; DestDir: "{app}\Document"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
; --- 桌面快捷方式 ---
; WorkingDir: "{app}\bin" 是为了保证 "../res" 相对路径生效的关键
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; IconFilename: "{app}\{#MyAppExeName}"

; --- 开始菜单快捷方式 ---
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"
Name: "{group}\卸载 {#MyAppName}"; Filename: "{uninstallexe}"

[Run]
; 安装完成后提示运行
Filename: "{app}\{#MyAppExeName}"; Description: "启动游戏"; Flags: nowait postinstall skipifsilent; WorkingDir: "{app}"