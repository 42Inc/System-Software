Function generateName ($Length=5) {
 $Result = -join (1..$Length | % { [char[]]'afgtdUHS45B-7634kLqO' | Get-Random })
 return $Result
}

Function generateText ($Length=100) {
 #Write-Host "Length : " + $Length
 $CharBegin = 0
 $CharEnd = 127
 $Result = -join (1..$Length | % {  $CharBegin..$CharEnd | Get-Random | % {[char]$_}})
 return $Result
}

Function printFileList ($Sym='-') {
  $List = (Get-ChildItem -Path ".\result" -File -Name -Include ('*'+$Sym+'*'))
  foreach ($Element in $List) {
    Write-Host ($Element)
  }
}

Function renameFiles {
  $iter = 1
  $List = (Get-ChildItem -Path ".\result" -File -Name).GetEnumerator() | %  {$_ | Sort-Object} | % {("result\\" + $_) |
    Rename-Item -NewName ($iter.ToString()+"_"+$_); $iter++;}
}

$Begin = 1
$End = 1535

($Begin..$End) | % {
  $Text = ""
  $Filename = generateName(Get-Random -max 17 -min 5)
  #Write-Host ("Name : " + $Filename)
  $Size = Get-Random -max 1024 -min 100
  #  Write-Host ("Size : " + $Size)
  $Text = generateText($Size)
  #Write-Host ("Text : " + $Text)
  $Text | Out-File ("result\\"+$Filename)
}

Write-Host "Creating complete"
printFileList('-')
renameFiles
Write-Host "Rename complete"
