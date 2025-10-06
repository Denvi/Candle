param(
    [Parameter(Mandatory)][string]$SourceDir,
    [Parameter(Mandatory)][string]$WxsOut,
    [string]$ProductName    = "Candle",
    [string]$Manufacturer   = "Denvi",
    [string]$UpgradeCode    = "A53DFAC8-5BB4-40C0-9C29-BB5D640D9968",
    [string]$StartMenuName  = "Candle",
    [string]$IconFile       = "..\..\doc\candle.ico"
)

$SourceDir = $SourceDir.TrimEnd('\','/')

function Get-Relative([System.IO.FileSystemInfo]$item) {
    $full = $item.FullName
    $base = (Resolve-Path $SourceDir).Path
    return $full.Substring($base.Length).TrimStart('\','/').Replace('\','/')
}

function New-Guid() { [guid]::NewGuid().ToString("D").ToUpper() }

function Format-Xml($xml) {
    $stringWriter = New-Object System.IO.StringWriter
    $settings     = New-Object System.Xml.XmlWriterSettings
    $settings.Indent = $true
    $settings.IndentChars = "  "
    $settings.NewLineChars = "`n"
    $writer = [System.Xml.XmlWriter]::Create($stringWriter, $settings)
    $xml.Save($writer)
    $writer.Close()
    return $stringWriter.ToString()
}

$dirs  = @{}
$comps = @()

$dirs[""] = "INSTALLFOLDER"

# Components
$files = Get-ChildItem -LiteralPath $SourceDir -File -Recurse
foreach ($file in $files) {
    $relFile = Get-Relative $file
    $relDir  = [System.IO.Path]::GetDirectoryName($relFile).Replace('\','/')

    $parts = $relDir -split '/'
    $path = ""
    foreach ($part in $parts) {
        if ($part -eq "") { continue }
        $parent = $path
        $path   = if ($path -eq "") { $part } else { "$path/$part" }
        if (-not $dirs.ContainsKey($path)) {
            $id = "dir_" + ($path -replace '/','_')
            $dirs[$path] = $id
        }
    }

    $compId = "cmp_" + ($relFile -replace '[\-\\/\.]','_')
    $fileId = "fil_" + ($relFile -replace '[\-\\/\.]','_')
    $guid   = New-Guid

    $comps += @"
      <Component Id="$compId" Directory="$($dirs[$relDir])" Guid="$guid">
        <File Id="$fileId" Source="$($file.FullName)" KeyPath="yes" />
      </Component>
"@
}

# Directories
$dirXml = @"
    <StandardDirectory Id="ProgramFiles64Folder">

"@

$dirNodes = @{}
$rootXml = [xml]@"
        <Directory Id="INSTALLFOLDER" Name="$ProductName" />
"@
$dirNodes[""] = $rootXml.DocumentElement

foreach ($key in ($dirs.Keys | Sort-Object { $_.Split('/').Count })) {
    if ($key -eq "") { continue }
    $name      = [System.IO.Path]::GetFileName($key)
    $parentKey = [System.IO.Path]::GetDirectoryName($key).Replace('\','/')
    $parentNode= $dirNodes[$parentKey]
    $id        = $dirs[$key]

    $childXml = $parentNode.OwnerDocument.CreateElement("Directory")
    $childXml.SetAttribute("Id", $id)
    $childXml.SetAttribute("Name", $name)
    [void]$parentNode.AppendChild($childXml)
    $dirNodes[$key] = $childXml
}

$dirFragment = (Format-Xml $rootXml) -replace '^<\?xml[^>]*>\s*' -split "`n" |
               ForEach-Object { '      ' + $_ } |
               Out-String

$dirXml += $dirFragment

$dirXml += @"
    </StandardDirectory>
"@

$shortcutGuid = New-Guid

# Root
$wxs = @"
<Wix xmlns="http://wixtoolset.org/schemas/v4/wxs">
  <Package Name="$ProductName" Manufacturer="$Manufacturer" Version="`$(var.ProductVersion)"
           UpgradeCode="$UpgradeCode">

    <MediaTemplate EmbedCab="yes" />

$dirXml

    <StandardDirectory Id="ProgramMenuFolder">
      <Directory Id="AppMenuFolder" Name="$ProductName"/>
    </StandardDirectory>

    <Icon Id="AppIcon" SourceFile="$IconFile" />

    <Component Id="StartMenuShortcut" Guid="$shortcutGuid">
      <Shortcut Id="StartMenuCandle"
                Directory="AppMenuFolder"
                Name="Candle"
                Description="Candle - G-code sender"
                Target="[INSTALLFOLDER]candle.exe"
                WorkingDirectory="INSTALLFOLDER"
                Icon="AppIcon" />
    
      <RemoveFolder Id="RemoveAppMenuFolder" Directory="AppMenuFolder" On="uninstall" />
    
      <RegistryValue Root="HKCU"
                     Key="Software\Denvi\Candle"
                     Name="StartMenuShortcut"
                     Type="integer"
                     Value="1"
                     KeyPath="yes" />
    </Component>

    <Feature Id="MainFeature">
      <ComponentRef Id="StartMenuShortcut" />
$( $comps -join "`n" )
    </Feature>

  </Package>
</Wix>
"@

$wxs | Out-File -Encoding UTF8 -LiteralPath $WxsOut