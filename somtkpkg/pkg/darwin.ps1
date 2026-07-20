#!/usr/bin/env pwsh

param(
	[Parameter(Mandatory)]$distribution,
	[Parameter(Mandatory)]$title
)

$ErrorActionPreference = 'Stop'

trap
{
	throw $_
}

[xml]$xml = Get-Content $distribution

$text = $xml.CreateTextNode($title)
$title = $xml.CreateElement('title')
$null = $title.AppendChild($text)
$null = $xml.documentElement.AppendChild($title)

$xml.Save($distribution)
